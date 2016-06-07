#include "server.h"
#include <ctime>




Server::Server(QString _nick, int _p_port, QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
    nick = _nick;
    port = _p_port;


    inicjuj();

    QDesktopWidget *widget = QApplication::desktop();
    QRect dim = widget->screenGeometry();
    setGeometry((dim.width() - width()) / 2, (dim.height() - height()) / 2, width(), height());



    th = new Thread();
    th->setSleepMs(1700);

    metoda[0] = &Server::ustawNickKlienta;
    metoda[1] = &Server::kartyKlienta;
    metoda[2] = &Server::klientOdlaczony;
    metoda[3] = &Server::inicjujPartie;
    metoda[4] = &Server::ustawLiczbeRund;
    metoda[5] = &Server::przeciwnikPas;
    metoda[6] = &Server::rodzajKlienta;

    server = new QTcpServer();
    server->listen(QHostAddress::Any, port);

    socket = new QTcpSocket(this);
    buffer = new QBuffer(this);
    buffer->open(QIODevice::ReadWrite);

    connect(server, SIGNAL(newConnection()), this, SLOT(dodajPolaczenie()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(odbierzWiadomosc()));
    connect(th, SIGNAL(sygnalG1()), this, SLOT(odbierzSygnalG1()), Qt::QueuedConnection);
    connect(th, SIGNAL(sygnalG2()), this, SLOT(odbierzSygnalG2()), Qt::QueuedConnection);

    connect(pushButtonG2C1, SIGNAL(clicked()), this, SLOT(klikKarta1()));
    connect(pushButtonG2C2, SIGNAL(clicked()), this, SLOT(klikKarta2()));
    connect(pushButtonG2C3, SIGNAL(clicked()), this, SLOT(klikKarta3()));
    connect(pushButtonG2C4, SIGNAL(clicked()), this, SLOT(klikKarta4()));
    connect(pushButtonG2C5, SIGNAL(clicked()), this, SLOT(klikKarta5()));
    connect(pushButtonG2C6, SIGNAL(clicked()), this, SLOT(klikKarta6()));
    connect(pushButtonG2C7, SIGNAL(clicked()), this, SLOT(klikKarta7()));
    connect(pushButtonG2C8, SIGNAL(clicked()), this, SLOT(klikKarta8()));
    connect(pushButtonG2C9, SIGNAL(clicked()), this, SLOT(klikKarta9()));
    connect(pushButtonG2C10, SIGNAL(clicked()), this, SLOT(klikKarta10()));

    connect(pushButtonPasG2, SIGNAL(clicked()), this, SLOT(klikPas()));




}


void Server::inicjuj()
{
    groupBoxG2->setTitle(nick);
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    lineEditRundyG1->setText("0");
    lineEditRundyG2->setText("0");
    niewidoczneG1();
    rywalPas = false;
    Pas = false;


}

void Server::niewidoczneG1()
{
    pushButtonG1C1->setEnabled(false);
    pushButtonG1C2->setEnabled(false);
    pushButtonG1C3->setEnabled(false);
    pushButtonG1C4->setEnabled(false);
    pushButtonG1C5->setEnabled(false);
    pushButtonG1C6->setEnabled(false);
    pushButtonG1C7->setEnabled(false);
    pushButtonG1C8->setEnabled(false);
    pushButtonG1C9->setEnabled(false);
    pushButtonG1C10->setEnabled(false);
    pushButtonPasG1->setEnabled(false);
}

void Server::dodajPolaczenie()
{
    socket = server->nextPendingConnection();
    buffer = new QBuffer(this);
    buffer->open(QIODevice::ReadWrite);

    wyslijWiadomosc("00" + rodzajTalii + nick + "|");

    connect(socket, SIGNAL(readyRead()), SLOT(odbierzWiadomosc()));

}

void Server::inicjujPartie(QString c)
{

    rodzajTaliiG1 = c;


    talia = new Talia(rodzajTalii);
    talia1 = new Talia(rodzajTaliiG1);


    losujTure = new Random(time(0));

    tura = 0;
    pos1 = -1;
    pos2 = -1;


    g1 = new Gracz(talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte());
    g2 = new Gracz(talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte());


    QString tmp, num;

    tmp.setNum(g2->getKarta(0)->getNumer());
    QString icona20 = ":talie/" + rodzajTalii + "/" + tmp  + ".png";
    pushButtonG2C1->setIcon(QIcon(icona20));
    num.setNum(g1->getKarta(0)->getNumer());
    wyslijWiadomosc("010" + num + "|");

    tmp.setNum(g2->getKarta(1)->getNumer());
    QString icona21 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C2->setIcon(QIcon(icona21));
    num.setNum(g1->getKarta(1)->getNumer());
    wyslijWiadomosc("011" + num + "|");

    tmp.setNum(g2->getKarta(2)->getNumer());
    QString icona22 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C3->setIcon(QIcon(icona22));
    num.setNum(g1->getKarta(2)->getNumer());
    wyslijWiadomosc("012" + num + "|");

    tmp.setNum(g2->getKarta(3)->getNumer());
    QString icona23 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C4->setIcon(QIcon(icona23));
    num.setNum(g1->getKarta(3)->getNumer());
    wyslijWiadomosc("013" + num + "|");

    tmp.setNum(g2->getKarta(4)->getNumer());
    QString icona24 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C5->setIcon(QIcon(icona24));
    num.setNum(g1->getKarta(1)->getNumer());
    wyslijWiadomosc("014" + num + "|");

    tmp.setNum(g2->getKarta(5)->getNumer());
    QString icona25 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C6->setIcon(QIcon(icona25));
    num.setNum(g1->getKarta(5)->getNumer());
    wyslijWiadomosc("015" + num + "|");

    tmp.setNum(g2->getKarta(6)->getNumer());
    QString icona26 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C7->setIcon(QIcon(icona26));
    num.setNum(g1->getKarta(6)->getNumer());
    wyslijWiadomosc("016" + num + "|");

    tmp.setNum(g2->getKarta(7)->getNumer());
    QString icona27 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C8->setIcon(QIcon(icona27));
    num.setNum(g1->getKarta(7)->getNumer());
    wyslijWiadomosc("017" + num + "|");

    tmp.setNum(g2->getKarta(8)->getNumer());
    QString icona28 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C9->setIcon(QIcon(icona28));
    num.setNum(g1->getKarta(8)->getNumer());
    wyslijWiadomosc("018" + num + "|");

    tmp.setNum(g2->getKarta(9)->getNumer());
    QString icona29 = ":talie/" + rodzajTalii + "/" + tmp +  ".png";
    pushButtonG2C10->setIcon(QIcon(icona29));
    num.setNum(g1->getKarta(9)->getNumer());
    wyslijWiadomosc("019" + num + "|");


    ustawLiczbeKartG2();
    ustawLiczbeKartG1();
    tura = ktoZaczyna();
    ustawTure(tura);
}


int Server::ktoZaczyna()
{
    int r = static_cast<int> (losujTure->rand() * (2));

    if (r > 0.5)
        return 2;
    else
        return 1;
}

void Server::ustawTure(int g)
{
    if (g == 2) {
        pushButtonG2C1->setEnabled(true);
        pushButtonG2C2->setEnabled(true);
        pushButtonG2C3->setEnabled(true);
        pushButtonG2C4->setEnabled(true);
        pushButtonG2C5->setEnabled(true);
        pushButtonG2C6->setEnabled(true);
        pushButtonG2C7->setEnabled(true);
        pushButtonG2C8->setEnabled(true);
        pushButtonG2C9->setEnabled(true);
        pushButtonG2C10->setEnabled(true);
        pushButtonPasG2->setEnabled(true);
    } else {
        wyslijWiadomosc("03Tura|");
    }
}

void Server::wyslijWiadomosc(QString message)
{
    socket->write(message.toLatin1());
}

void Server::odbierzWiadomosc()
{
    qint64 bytes = buffer->write(socket->readAll());
    buffer->seek(buffer->pos() - bytes);
    QString wiadomosc = buffer->readAll();
    QStringList list;
    list = wiadomosc.split("|");

    for (QList<QString>::iterator i = list.begin(); i != list.end(); i++) {
        QString split = *i;
        if (split != "") {
            int i = split.mid(0, 2).toInt();
            QString argument = split.mid(2);
            (*this.*metoda[i])(argument);
        }
    }
}

void Server::klientOdlaczony(QString)
{
    QMessageBox::critical(this, tr("Uwaga"), tr("Utracono polaczenie z klientem"));
    wrocDoMenu();
}

void Server::ustawNickKlienta(QString nickClient)
{
    groupBoxG1->setTitle(nickClient);
    setWindowTitle("Gwint - " + nick + " vs " + nickClient);
}

void Server::rodzajKlienta(QString c)
{
    int karta = c.mid(0,1).toInt();
    pos1 = karta;
    g1->rzuconaKarta(pos1);

    QString tmp1;
    tmp1.setNum(g1->getRzucona()->getNumer());

    QString r = g1->getRzucona()->getRodzaj();

    wyslijWiadomosc("11"+r+tmp1+"|");

    if (karta == 0) {
        pushButtonG1C1->setHidden(true);
    } else if (karta == 1) {
        pushButtonG1C2->setHidden(true);
    } else if (karta == 2) {
       pushButtonG1C3->setHidden(true);
    }  else if (karta == 3) {
        pushButtonG1C4->setHidden(true);
    } else if (karta == 4) {
        pushButtonG1C5->setHidden(true);
    } else if (karta == 5) {
        pushButtonG1C6->setHidden(true);
    } else if (karta == 6) {
        pushButtonG1C7->setHidden(true);
    } else if (karta == 7) {
        pushButtonG1C8->setHidden(true);
    } else if (karta == 8) {
       pushButtonG1C9->setHidden(true);
    } else if (karta == 9) {
        pushButtonG1C10->setHidden(true);
    }

}

void Server::kartyKlienta(QString c)
{
    QString poz = c.mid(0, 1);

        QString tmp1;
        tmp1.setNum(g1->getRzucona()->getNumer());
        QString carta1 = ":talie2/" + rodzajTaliiG1 + "/" + tmp1 + ".png";
        QString r = g1->getRzucona()->getRodzaj();

        if (r == "k")
        {
        if (poz == "0") {
            kata1G1->setEnabled(true);
            kata1G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "1") {
            kata2G1->setEnabled(true);
            kata2G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "2") {
            kata3G1->setEnabled(true);
            kata3G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "3") {
            kata4G1->setEnabled(true);
            kata4G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "4") {
            kata5G1->setEnabled(true);
            kata5G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "5") {
            kata6G1->setEnabled(true);
            kata6G1->setPixmap(QPixmap(carta1));
        }
        else if (poz == "6") {
            kata7G1->setEnabled(true);
            kata7G1->setPixmap(QPixmap(carta1));
        }
        else{
            kata8G1->setEnabled(true);
            kata8G1->setPixmap(QPixmap(carta1));
    }
    }
        else if (r=="l")
        {
            if (poz == "0") {
                luk1G1->setEnabled(true);
                luk1G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "1") {
                luk2G1->setEnabled(true);
                luk2G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "2") {
                luk3G1->setEnabled(true);
                luk3G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "3") {
                luk4G1->setEnabled(true);
                luk4G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "4") {
                luk5G1->setEnabled(true);
                luk5G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "5") {
                luk6G1->setEnabled(true);
                luk6G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "6") {
                luk7G1->setEnabled(true);
                luk7G1->setPixmap(QPixmap(carta1));
            }
            else{
                luk8G1->setEnabled(true);
                luk8G1->setPixmap(QPixmap(carta1));
        }
        }
        else if (r=="m" || r == "h")
        {
            if (poz == "0") {
                miecz1G1->setPixmap(QPixmap(carta1));
                miecz1G1->setEnabled(true);
            }
            else if (poz == "1") {
                miecz2G1->setEnabled(true);
                miecz2G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "2") {
                miecz3G1->setEnabled(true);
                miecz3G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "3") {
                miecz4G1->setEnabled(true);
                miecz4G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "4") {
                miecz5G1->setEnabled(true);
                miecz5G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "5") {
                miecz6G1->setEnabled(true);
                miecz6G1->setPixmap(QPixmap(carta1));
            }
            else if (poz == "6") {
                miecz7G1->setEnabled(true);
                miecz7G1->setPixmap(QPixmap(carta1));
            }
            else{
                miecz8G1->setEnabled(true);
                miecz8G1->setPixmap(QPixmap(carta1));
        }
            }
        else
        {
            specG1->setPixmap(QPixmap(carta1));
            specG1->setEnabled(true);
        }

    przyznajPunkty(1);
}

void Server::ustawLiczbeKartG2()
{
    QString num;
    num.setNum(talia->getMax());
    lineEditCardsG2->setText(num);

    wyslijWiadomosc("02" + num + "|");
}

void Server::ustawLiczbeKartG1()
{
    QString num;
    num.setNum(talia1->getMax());
    lineEditCardsG1->setText(num);

    wyslijWiadomosc("08" + num + "|");
}

void Server::aktywnyGracz(int g)
{
    if (g == 1) {
        th->ustawGracza(1);
        th->start();
    } else if (g == 2) {
        th->ustawGracza(2);
        th->start();
    }
}


void Server::przyznajPunkty(int i)
{


    if (i == 2) {
        g2->zwiekszPunkty(g2->getRzucona()->getSila());
        QString punkty2;
        punkty2.setNum(g2->getPunkty());
        lineEditPktG2->setText(punkty2);
        wyslijWiadomosc("06" + punkty2 + "|");
        if (rywalPas==false)
        {
        if (g1->getRzucona() == NULL) {
            ustawTure(1);
        } else {
            aktywnyGracz(1);
        }
        }
        else
        {
            ustawTure(2);
        }
    } else {
        g1->zwiekszPunkty(g1->getRzucona()->getSila());
        QString punkty1;
        punkty1.setNum(g1->getPunkty());
        lineEditPktG1->setText(punkty1);
        wyslijWiadomosc("05" + punkty1 + "|");
        if(Pas==false)
        {
        if (g2->getRzucona() == NULL) {
            ustawTure(2);
        } else {
            aktywnyGracz(2);
        }
        }
        else
        {
            ustawTure(1);
        }
    }
}


void Server::wrocDoMenu()
{
    server->close();
    socket->close();
    buffer->close();
    setVisible(false);
    Start *a = new Start();
    a->show();
    a->setVisible(true);
}

void Server::ustawIkony()
{
    QString tmp;



    if (g1->getKarta(0) != NULL) {
        pushButtonG1C1->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C1->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(1) != NULL) {
        pushButtonG1C2->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C2->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(3) != NULL) {
        pushButtonG1C4->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C4->setIcon(QIcon(":ikony/null.png"));
    if (g1->getKarta(4) != NULL) {
        pushButtonG1C5->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C5->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(5) != NULL) {
        pushButtonG1C6->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C6->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(6) != NULL) {
        pushButtonG1C7->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C7->setIcon(QIcon(":ikony/null.png"));
    if (g1->getKarta(7) != NULL) {
        pushButtonG1C8->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C8->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(8) != NULL) {
        pushButtonG1C9->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C9->setIcon(QIcon(":ikony/null.png"));

    if (g1->getKarta(9) != NULL) {
        pushButtonG1C10->setIcon(QIcon(":ikony/pion.png"));
    } else
        pushButtonG1C10->setIcon(QIcon(":ikony/null.png"));



    if (g2->getKarta(0) != NULL) {
        tmp.setNum(g2->getKarta(0)->getNumer());
        QString icona20 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C1->setIcon(QIcon(icona20));
    } else
        pushButtonG2C1->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(1) != NULL) {
        tmp.setNum(g2->getKarta(1)->getNumer());
        QString icona21 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C2->setIcon(QIcon(icona21));
    } else
        pushButtonG2C2->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(2) != NULL) {
        tmp.setNum(g2->getKarta(2)->getNumer());
        QString icona22 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C3->setIcon(QIcon(icona22));
    } else
        pushButtonG2C3->setIcon(QIcon(":ikony/null.png"));
    if (g2->getKarta(3) != NULL) {
        tmp.setNum(g2->getKarta(3)->getNumer());
        QString icona23 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C4->setIcon(QIcon(icona23));
    } else
        pushButtonG2C4->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(4) != NULL) {
        tmp.setNum(g2->getKarta(4)->getNumer());
        QString icona24 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C5->setIcon(QIcon(icona24));
    } else
        pushButtonG2C5->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(5) != NULL) {
        tmp.setNum(g2->getKarta(5)->getNumer());
        QString icona25 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C6->setIcon(QIcon(icona25));
    } else
        pushButtonG2C6->setIcon(QIcon(":ikony/null.png"));
    if (g2->getKarta(6) != NULL) {
        tmp.setNum(g2->getKarta(6)->getNumer());
        QString icona26 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C7->setIcon(QIcon(icona26));
    } else
        pushButtonG2C7->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(7) != NULL) {
        tmp.setNum(g2->getKarta(7)->getNumer());
        QString icona27 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C8->setIcon(QIcon(icona27));
    } else
        pushButtonG2C8->setIcon(QIcon(":ikony/null.png"));

    if (g2->getKarta(8) != NULL) {
        tmp.setNum(g2->getKarta(8)->getNumer());
        QString icona28 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C9->setIcon(QIcon(icona28));
    } else
        pushButtonG2C9->setIcon(QIcon(":ikony/null.png"));
    if (g2->getKarta(9) != NULL) {
        tmp.setNum(g2->getKarta(9)->getNumer());
        QString icona29 = ":talie/" + rodzajTalii + "/" + tmp + ".png";
        pushButtonG2C10->setIcon(QIcon(icona29));
    } else
        pushButtonG2C10->setIcon(QIcon(":ikony/null.png"));
}

void Server::klikKarta()
{

    QString tmp1;
    tmp1.setNum(g2->getRzucona()->getNumer());
    QString carta1 = ":talie2/" + rodzajTalii + "/" + tmp1 + ".png";

    QString tmp2 = g2->getRzucona()->getRodzaj();

    if(tmp2=="k")
    {
    if (kata1G2->isEnabled() == false) {
    kata1G2->setPixmap(carta1);
    kata1G2->setEnabled(true);
     wyslijWiadomosc("04k0" + tmp1 + "|");
    }
    else if (kata2G2->isEnabled() == false) {
        kata2G2->setPixmap(carta1);
        kata2G2->setEnabled(true);
         wyslijWiadomosc("04k1" + tmp1 + "|");
    }
    else if (kata3G2->isEnabled() == false) {
        kata3G2->setPixmap(carta1);
        kata3G2->setEnabled(true);
         wyslijWiadomosc("04k2" + tmp1 + "|");
    }
    else if (kata4G2->isEnabled() == false) {
        kata4G2->setPixmap(carta1);
        kata4G2->setEnabled(true);
         wyslijWiadomosc("04k3" + tmp1 + "|");
    }
    else if (kata5G2->isEnabled() == false) {
        kata5G2->setPixmap(carta1);
        kata5G2->setEnabled(true);
         wyslijWiadomosc("04k4" + tmp1 + "|");
    }
    else if (kata6G2->isEnabled() == false) {
        kata6G2->setPixmap(carta1);
        kata6G2->setEnabled(true);
         wyslijWiadomosc("04k5" + tmp1 + "|");
    }
    else if (kata7G2->isEnabled() == false) {
        kata7G2->setPixmap(carta1);
        kata7G2->setEnabled(true);
         wyslijWiadomosc("04k6" + tmp1 + "|");
    }
    else {
        kata8G2->setPixmap(carta1);
        kata8G2->setEnabled(true);
         wyslijWiadomosc("04k7" + tmp1 + "|");
    }
}
    else if(tmp2 == "l")
    {
        if (luk1G2->isEnabled() == false) {
        luk1G2->setPixmap(carta1);
        luk1G2->setEnabled(true);
         wyslijWiadomosc("04l0" + tmp1 + "|");
        }
        else if (luk2G2->isEnabled() == false) {
            luk2G2->setPixmap(carta1);
            luk2G2->setEnabled(true);
             wyslijWiadomosc("04l1" + tmp1 + "|");
        }
        else if (luk3G2->isEnabled() == false) {
            luk3G2->setPixmap(carta1);
            luk3G2->setEnabled(true);
             wyslijWiadomosc("04l2" + tmp1 + "|");
        }
        else if (luk4G2->isEnabled() == false) {
            luk4G2->setPixmap(carta1);
            luk4G2->setEnabled(true);
             wyslijWiadomosc("04l3" + tmp1 + "|");
        }
        else if (luk5G2->isEnabled() == false) {
            luk5G2->setPixmap(carta1);
            luk5G2->setEnabled(true);
             wyslijWiadomosc("04l4" + tmp1 + "|");
        }
        else if (luk6G2->isEnabled() == false) {
            luk6G2->setPixmap(carta1);
            luk6G2->setEnabled(true);
             wyslijWiadomosc("04l5" + tmp1 + "|");
        }
        else if (luk7G2->isEnabled() == false) {
            luk7G2->setPixmap(carta1);
            luk7G2->setEnabled(true);
             wyslijWiadomosc("04l6" + tmp1 + "|");
        }
        else {
            luk8G2->setPixmap(carta1);
            luk8G2->setEnabled(true);
             wyslijWiadomosc("04l7" + tmp1 + "|");
        }
    }
    else if (tmp2 == "m" || tmp2 == "h")
    {
        if (miecz1G2->isEnabled() == false) {
        miecz1G2->setPixmap(carta1);
        miecz1G2->setEnabled(true);
         wyslijWiadomosc("04m0" + tmp1 + "|");
        }
        else if (miecz2G2->isEnabled() == false) {
            miecz2G2->setPixmap(carta1);
            miecz2G2->setEnabled(true);
             wyslijWiadomosc("04m1" + tmp1 + "|");
        }
        else if (miecz3G2->isEnabled() == false) {
            miecz3G2->setPixmap(carta1);
            miecz3G2->setEnabled(true);
             wyslijWiadomosc("04m2" + tmp1 + "|");
        }
        else if (miecz4G2->isEnabled() == false) {
            miecz4G2->setPixmap(carta1);
            miecz4G2->setEnabled(true);
             wyslijWiadomosc("04m3" + tmp1 + "|");
        }
        else if (miecz5G2->isEnabled() == false) {
            miecz5G2->setPixmap(carta1);
            miecz5G2->setEnabled(true);
             wyslijWiadomosc("04m4" + tmp1 + "|");
        }
        else if (miecz6G2->isEnabled() == false) {
            miecz6G2->setPixmap(carta1);
            miecz6G2->setEnabled(true);
             wyslijWiadomosc("04m5" + tmp1 + "|");
        }
        else if (miecz7G2->isEnabled() == false) {
            miecz7G2->setPixmap(carta1);
            miecz7G2->setEnabled(true);
             wyslijWiadomosc("04m6" + tmp1 + "|");
        }
        else {
            miecz8G2->setPixmap(carta1);
            miecz8G2->setEnabled(true);
             wyslijWiadomosc("04m7" + tmp1 + "|");
        }
    }
    else
    {
        specG2->setPixmap(carta1);
        specG2->setEnabled(true);
        wyslijWiadomosc("0430" + tmp1 + "|");
    }

    przyznajPunkty(2);

}

void Server::klikKarta1()
{
    g2->rzuconaKarta(0);
    pushButtonG2C1->setHidden(true);
    niewidoczneG2();


    wyslijWiadomosc("120|");
    klikKarta();

    pos2 = 0;

}

void Server::klikKarta2()
{
    g2->rzuconaKarta(1);
    pushButtonG2C2->setHidden(true);
    niewidoczneG2();




    wyslijWiadomosc("121|");
    klikKarta();

    pos2 = 1;
}

void Server::klikKarta3()
{
    g2->rzuconaKarta(2);
    pushButtonG2C3->setHidden(true);
    niewidoczneG2();



    wyslijWiadomosc("122|");
    klikKarta();

    pos2 = 2;
}

void Server::klikKarta4()
{
    g2->rzuconaKarta(3);
    pushButtonG2C4->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("123|");
    klikKarta();

    pos2 = 3;
}

void Server::klikKarta5()
{
    g2->rzuconaKarta(4);
    pushButtonG2C5->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("124|");
    klikKarta();
    pos2 = 4;
}

void Server::klikKarta6()
{
    g2->rzuconaKarta(5);
    pushButtonG2C6->setHidden(true);
   niewidoczneG2();
   wyslijWiadomosc("125|");
   klikKarta();
    pos2 = 5;
}

void Server::klikKarta7()
{
    g2->rzuconaKarta(6);
    pushButtonG2C7->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("126|");
    klikKarta();

    pos2 = 6;
}

void Server::klikKarta8()
{
    g2->rzuconaKarta(7);
    pushButtonG2C8->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("127|");
    klikKarta();
    pos2 = 7;

}

void Server::klikKarta9()
{
    g2->rzuconaKarta(8);
    pushButtonG2C9->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("128|");
    klikKarta();
    pos2 = 8;
}

void Server::klikKarta10()
{
    g2->rzuconaKarta(9);
    pushButtonG2C10->setHidden(true);

    niewidoczneG2();

    wyslijWiadomosc("129|");
    klikKarta();

    pos2 = 9;
}

void Server::niewidoczneG2()
{
    pushButtonG2C1->setEnabled(false);
    pushButtonG2C2->setEnabled(false);
    pushButtonG2C3->setEnabled(false);
    pushButtonG2C4->setEnabled(false);
    pushButtonG2C5->setEnabled(false);
    pushButtonG2C6->setEnabled(false);
    pushButtonG2C7->setEnabled(false);
    pushButtonG2C8->setEnabled(false);
    pushButtonG2C9->setEnabled(false);
    pushButtonG2C10->setEnabled(false);
    pushButtonPasG2->setEnabled(false);
}

void Server::wydajWerdykt()
{
    if(rywalPas == true && Pas == true)
    {
    int pkt1 = lineEditPktG1->text().toInt();
    int pkt2 = lineEditPktG2->text().toInt();
    int rnd1 = lineEditRundyG1->text().toInt();
    int rnd2 = lineEditRundyG2->text().toInt();
    QString r1,r2;

    int werdykt;

    if (pkt1 < pkt2)
    {
        rnd2++;
        r1.setNum(rnd1);
        r2.setNum(rnd2);
        lineEditRundyG2->setText(r2);
        inicjujKolejnaPartie();
    }
    else if (pkt1 > pkt2)
    {
        rnd1++;
        r1.setNum(rnd1);
        r2.setNum(rnd2);
        lineEditRundyG1->setText(r1);
        inicjujKolejnaPartie();
    }
    else
    {
        rnd1++;
        rnd2++;
        r1.setNum(rnd1);
        r2.setNum(rnd2);
        lineEditRundyG1->setText(r1);
        lineEditRundyG2->setText(r2);
        inicjujKolejnaPartie();
    }

        wyslijWiadomosc("09"+r1+r2+"|");

        if(rnd1==2 || rnd2==2)
        {
            if(rnd1==2)
                werdykt = Koniec::Porazka;
            else
                werdykt = Koniec::Zwyciestwo;


            Koniec *koniec = new Koniec(werdykt, rnd1, rnd2, nick, groupBoxG2->title());
            koniec->exec();


            wrocDoMenu();
        }

}
}


void Server::klikPas()
{
    Pas = true;

    if(rywalPas == true)
    wydajWerdykt();
    else
    {
            wyslijWiadomosc("10SPASOWAL|");
            aktywnyGracz(1);
            niewidoczneG2();
}
}



void Server::przeciwnikPas(QString c)
{
    rywalPas = true;

    if (Pas == true)
        wydajWerdykt();
    else
    {
    aktywnyGracz(2);
    pushButtonPasG1->setMinimumWidth(70);
    pushButtonPasG1->setMaximumWidth(70);
    pushButtonPasG1->setText(c);
    }

}

void Server::ustawLiczbeRund(QString c)
{
    int werdykt;


    lineEditRundyG1->setText(c.mid(0,1));
    lineEditRundyG2->setText(c.mid(1,1));

    int rnd1 = c.mid(0,1).toInt();
    int rnd2 = c.mid (1,1).toInt();

    if (rnd1 == 2 || rnd2 == 2)
    {
        if(rnd1==2)
            werdykt = Koniec::Porazka;
        else
            werdykt = Koniec::Zwyciestwo;

        Koniec *koniec = new Koniec(werdykt, rnd1, rnd2, nick, groupBoxG2->title());
        koniec->exec();


        wrocDoMenu();
    }
    else
    inicjujKolejnaPartie();
}



void Server::inicjujKolejnaPartie()
{
    Pas = false;
    rywalPas = false;
    pushButtonPasG1->setMinimumWidth(50);
    pushButtonPasG1->setMaximumWidth(50);
    pushButtonPasG1->setText("Pas");
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    pushButtonPasG2->setEnabled(true);


    QString pixmap = ":ikony/null.png";


    kata1G1->setPixmap(pixmap);
    kata1G1->setEnabled(false);
    kata2G1->setPixmap(pixmap);
    kata2G1->setEnabled(false);
    kata3G1->setPixmap(pixmap);
    kata3G1->setEnabled(false);
    kata4G1->setPixmap(pixmap);
    kata4G1->setEnabled(false);
    kata5G1->setPixmap(pixmap);
    kata5G1->setEnabled(false);
    kata6G1->setPixmap(pixmap);
    kata6G1->setEnabled(false);
    kata7G1->setPixmap(pixmap);
    kata7G1->setEnabled(false);
    kata8G1->setPixmap(pixmap);
    kata8G1->setEnabled(false);

    luk1G1->setPixmap(pixmap);
    luk1G1->setEnabled(false);
    luk2G1->setPixmap(pixmap);
    luk2G1->setEnabled(false);
    luk3G1->setPixmap(pixmap);
    luk3G1->setEnabled(false);
    luk4G1->setPixmap(pixmap);
    luk4G1->setEnabled(false);
    luk5G1->setPixmap(pixmap);
    luk5G1->setEnabled(false);
    luk6G1->setPixmap(pixmap);
    luk6G1->setEnabled(false);
    luk7G1->setPixmap(pixmap);
    luk7G1->setEnabled(false);
    luk8G1->setPixmap(pixmap);
    luk8G1->setEnabled(false);

    miecz1G1->setPixmap(pixmap);
    miecz1G1->setEnabled(false);
    miecz2G1->setPixmap(pixmap);
    miecz2G1->setEnabled(false);
    miecz3G1->setPixmap(pixmap);
    miecz3G1->setEnabled(false);
    miecz4G1->setPixmap(pixmap);
    miecz4G1->setEnabled(false);
    miecz5G1->setPixmap(pixmap);
    miecz5G1->setEnabled(false);
    miecz6G1->setPixmap(pixmap);
    miecz6G1->setEnabled(false);
    miecz7G1->setPixmap(pixmap);
    miecz7G1->setEnabled(false);
    miecz8G1->setPixmap(pixmap);
    miecz8G1->setEnabled(false);

    kata1G2->setPixmap(pixmap);
    kata1G2->setEnabled(false);
    kata2G2->setPixmap(pixmap);
    kata2G2->setEnabled(false);
    kata3G2->setPixmap(pixmap);
    kata3G2->setEnabled(false);
    kata4G2->setPixmap(pixmap);
    kata4G2->setEnabled(false);
    kata5G2->setPixmap(pixmap);
    kata5G2->setEnabled(false);
    kata6G2->setPixmap(pixmap);
    kata6G2->setEnabled(false);
    kata7G2->setPixmap(pixmap);
    kata7G2->setEnabled(false);
    kata8G2->setPixmap(pixmap);
    kata8G2->setEnabled(false);

    luk1G2->setPixmap(pixmap);
    luk1G2->setEnabled(false);
    luk2G2->setPixmap(pixmap);
    luk2G2->setEnabled(false);
    luk3G2->setPixmap(pixmap);
    luk3G2->setEnabled(false);
    luk4G2->setPixmap(pixmap);
    luk4G2->setEnabled(false);
    luk5G2->setPixmap(pixmap);
    luk5G2->setEnabled(false);
    luk6G2->setPixmap(pixmap);
    luk6G2->setEnabled(false);
    luk7G2->setPixmap(pixmap);
    luk7G2->setEnabled(false);
    luk8G2->setPixmap(pixmap);
    luk8G2->setEnabled(false);

    miecz1G2->setPixmap(pixmap);
    miecz1G2->setEnabled(false);
    miecz2G2->setPixmap(pixmap);
    miecz2G2->setEnabled(false);
    miecz3G2->setPixmap(pixmap);
    miecz3G2->setEnabled(false);
    miecz4G2->setPixmap(pixmap);
    miecz4G2->setEnabled(false);
    miecz5G2->setPixmap(pixmap);
    miecz5G2->setEnabled(false);
    miecz6G2->setPixmap(pixmap);
    miecz6G2->setEnabled(false);
    miecz7G2->setPixmap(pixmap);
    miecz7G2->setEnabled(false);
    miecz8G2->setPixmap(pixmap);
    miecz8G2->setEnabled(false);

    specG1->setPixmap(pixmap);
    specG1->setEnabled(false);

    specG2->setPixmap(pixmap);
    specG2->setEnabled(false);


}

void Server::odbierzSygnalG1()
{
    g1->setNullRzucona();
    g2->setNullRzucona();



//        g1->dodajKarte(pos1, talia1->dajKarte());
//        g2->dodajKarte(pos2, talia->dajKarte());
//        ustawLiczbeKartG1();
//        ustawLiczbeKartG2();
//        QString num, pos;
//        num.setNum(g1->getKarta(pos1)->getNumer());
//        pos.setNum(pos1);
//        wyslijWiadomosc("01" + pos + num + "|");



      ustawTure(1);


}

void Server::odbierzSygnalG2()
{
    g1->setNullRzucona();
    g2->setNullRzucona();


//        g2->dodajKarte(pos2, talia->dajKarte());
//        g1->dodajKarte(pos1, talia1->dajKarte());
//        ustawLiczbeKartG1();
//        ustawLiczbeKartG2();
//        QString num, pos;
//        num.setNum(g1->getKarta(pos1)->getNumer());
//        pos.setNum(pos1);
//        wyslijWiadomosc("01" + pos + num  + "|");




    ustawTure(2);
}



void Server::closeEvent(QCloseEvent *event)
{
    event->ignore();
    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy na pewno chcesz wyjsc?"), QMessageBox::No | QMessageBox::Yes);
    if (odp == QMessageBox::Yes) {
        wrocDoMenu();
        wyslijWiadomosc("07|");
    }
}

