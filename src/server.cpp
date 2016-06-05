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


void Server::kartyKlienta(QString c)
{
    int carta = c.mid(1,1).toInt();
    QString poz = c.mid(0, 1);
    pos1 = carta;
    g1->rzuconaKarta(pos1);

    if (carta == 0) {
        pushButtonG1C1->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 1) {
        pushButtonG1C2->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 2) {
        pushButtonG1C3->setIcon(QIcon(":/ikony/null.png"));
    }  else if (carta == 3) {
        pushButtonG1C4->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 4) {
        pushButtonG1C5->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 5) {
        pushButtonG1C6->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 6) {
        pushButtonG1C7->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 7) {
        pushButtonG1C8->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 8) {
        pushButtonG1C9->setIcon(QIcon(":/ikony/null.png"));
    } else if (carta == 9) {
        pushButtonG1C10->setIcon(QIcon(":/ikony/null.png"));
    }


        QString tmp1;
        tmp1.setNum(g1->getRzucona()->getNumer());
        QString carta1 = ":talie/" + rodzajTaliiG1 + "/" + tmp1 + ".png";

    if (poz == "0") {
        labelG1->setEnabled(true);
        labelG1->setPixmap(carta1);
    }
    else if (poz == "1") {
        label1G1->setEnabled(true);
        label1G1->setPixmap(carta1);
    }
    else if (poz == "2") {
        label2G1->setEnabled(true);
        label2G1->setPixmap(carta1);
    }
    else if (poz == "3") {
        label3G1->setEnabled(true);
        label3G1->setPixmap(carta1);
    }
    else if (poz == "4") {
        label4G1->setEnabled(true);
        label4G1->setPixmap(carta1);
    }
    else if (poz == "5") {
        label5G1->setEnabled(true);
        label5G1->setPixmap(carta1);
        }
    else{
        label6G1->setEnabled(true);
        label6G1->setPixmap(carta1);
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


void Server::klikKarta1()
{
    g2->rzuconaKarta(0);
    pushButtonG2C1->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();


    QString tmp1;
    tmp1.setNum(g2->getRzucona()->getNumer());
    QString carta1 = ":talie/" + rodzajTalii + "/" + tmp1 + ".png";

    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta1);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0400" + tmp1 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta1);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0410" + tmp1 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta1);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0420" + tmp1 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta1);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0430" + tmp1 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta1);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0440" + tmp1 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta1);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0450" + tmp1 + "|");
    }
    else {
        label6G2->setPixmap(carta1);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0460" + tmp1 + "|");
    }



    pos2 = 0;
    przyznajPunkty(2);
}

void Server::klikKarta2()
{
    g2->rzuconaKarta(1);
    pushButtonG2C2->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp2;
    tmp2.setNum(g2->getRzucona()->getNumer());
    QString carta2 = ":talie/" + rodzajTalii + "/" + tmp2 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta2);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0401" + tmp2 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta2);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0411" + tmp2 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta2);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0421" + tmp2 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta2);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0431" + tmp2 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta2);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0441" + tmp2 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta2);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0451" + tmp2 + "|");
    }
    else {
        label6G2->setPixmap(carta2);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0461" + tmp2 + "|");
    }

    pos2 = 1;
    przyznajPunkty(2);
}

void Server::klikKarta3()
{
    g2->rzuconaKarta(2);
    pushButtonG2C3->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp3;
    tmp3.setNum(g2->getRzucona()->getNumer());
    QString carta3 = ":talie/" + rodzajTalii + "/" + tmp3 + + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta3);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0402" + tmp3 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta3);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0412" + tmp3 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta3);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0422" + tmp3 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta3);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0432" + tmp3 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta3);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0442" + tmp3 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta3);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0452" + tmp3 + "|");
    }
    else {
        label6G2->setPixmap(carta3);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0462" + tmp3 + "|");
    }

    pos2 = 2;
    przyznajPunkty(2);
}

void Server::klikKarta4()
{
    g2->rzuconaKarta(3);
    pushButtonG2C4->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp4;
    tmp4.setNum(g2->getRzucona()->getNumer());
    QString carta4 = ":talie/" + rodzajTalii + "/" + tmp4 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta4);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0403" + tmp4 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta4);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0413" + tmp4 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta4);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0423" + tmp4 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta4);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0433" + tmp4 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta4);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0443" + tmp4 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta4);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0453" + tmp4 + "|");
    }
    else {
        label6G2->setPixmap(carta4);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0463" + tmp4 + "|");
    }


    pos2 = 3;
    przyznajPunkty(2);
}

void Server::klikKarta5()
{
    g2->rzuconaKarta(4);
    pushButtonG2C5->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp5;
    tmp5.setNum(g2->getRzucona()->getNumer());
    QString carta5 = ":talie/" + rodzajTalii + "/" + tmp5 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta5);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0404" + tmp5 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta5);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0414" + tmp5 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta5);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0424" + tmp5 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta5);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0434" + tmp5 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta5);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0444" + tmp5 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta5);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0454" + tmp5 + "|");
    }
    else {
        label6G2->setPixmap(carta5);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0464" + tmp5 + "|");
    }

    pos2 = 4;
    przyznajPunkty(2);
}

void Server::klikKarta6()
{
    g2->rzuconaKarta(5);
    pushButtonG2C6->setIcon(QIcon(":/ikony/null.png"));
   niewidoczneG2();

    QString tmp6;
    tmp6.setNum(g2->getRzucona()->getNumer());
    QString carta6 = ":talie/" + rodzajTalii + "/" + tmp6 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta6);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0405" + tmp6 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta6);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0415" + tmp6 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta6);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0425" + tmp6 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta6);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0435" + tmp6 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta6);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0445" + tmp6 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta6);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0455" + tmp6 + "|");
    }
    else {
        label6G2->setPixmap(carta6);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0465" + tmp6 + "|");
    }

    pos2 = 5;
    przyznajPunkty(2);
}

void Server::klikKarta7()
{
    g2->rzuconaKarta(6);
    pushButtonG2C7->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp7;
    tmp7.setNum(g2->getRzucona()->getNumer());
    QString carta7 = ":talie/" + rodzajTalii + "/" + tmp7 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta7);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0406" + tmp7 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta7);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0416" + tmp7 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta7);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0426" + tmp7 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta7);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0436" + tmp7 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta7);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0446" + tmp7 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta7);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0456" + tmp7 + "|");
    }
    else {
        label6G2->setPixmap(carta7);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0466" + tmp7 + "|");
    }

    pos2 = 6;
    przyznajPunkty(2);
}

void Server::klikKarta8()
{
    g2->rzuconaKarta(7);
    pushButtonG2C8->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp8;
    tmp8.setNum(g2->getRzucona()->getNumer());
    QString carta8 = ":talie/" + rodzajTalii + "/" + tmp8 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta8);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0407" + tmp8 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta8);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0417" + tmp8 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta8);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0427" + tmp8 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta8);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0437" + tmp8 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta8);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0447" + tmp8 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta8);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0457" + tmp8 + "|");
    }
    else {
        label6G2->setPixmap(carta8);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0467" + tmp8 + "|");
    }

    pos2 = 7;
    przyznajPunkty(2);
}

void Server::klikKarta9()
{
    g2->rzuconaKarta(8);
    pushButtonG2C9->setIcon(QIcon(":/ikony/null.png"));
    niewidoczneG2();

    QString tmp9;
    tmp9.setNum(g2->getRzucona()->getNumer());
    QString carta9 = ":talie/" + rodzajTalii + "/" + tmp9 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta9);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0408" + tmp9 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta9);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0418" + tmp9 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta9);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0428" + tmp9 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta9);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0438" + tmp9 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta9);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0448" + tmp9 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta9);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0458" + tmp9 + "|");
    }
    else {
        label6G2->setPixmap(carta9);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0468" + tmp9 + "|");
    }

    pos2 = 8;
    przyznajPunkty(2);
}

void Server::klikKarta10()
{
    g2->rzuconaKarta(9);
    pushButtonG2C10->setIcon(QIcon(":/ikony/null.png"));

    niewidoczneG2();

    QString tmp10;
    tmp10.setNum(g2->getRzucona()->getNumer());
    QString carta10 = ":talie/" + rodzajTalii + "/" + tmp10 + ".png";
    if (labelG2->isEnabled() == false) {
    labelG2->setPixmap(carta10);
    labelG2->setEnabled(true);
     wyslijWiadomosc("0409" + tmp10 + "|");
    }
    else if (label1G2->isEnabled() == false) {
        label1G2->setPixmap(carta10);
        label1G2->setEnabled(true);
         wyslijWiadomosc("0419" + tmp10 + "|");
    }
    else if (label2G2->isEnabled() == false) {
        label2G2->setPixmap(carta10);
        label2G2->setEnabled(true);
         wyslijWiadomosc("0429" + tmp10 + "|");
    }
    else if (label3G2->isEnabled() == false) {
        label3G2->setPixmap(carta10);
        label3G2->setEnabled(true);
         wyslijWiadomosc("0439" + tmp10 + "|");
    }
    else if (label4G2->isEnabled() == false) {
        label4G2->setPixmap(carta10);
        label4G2->setEnabled(true);
         wyslijWiadomosc("0449" + tmp10 + "|");
    }
    else if (label5G2->isEnabled() == false) {
        label5G2->setPixmap(carta10);
        label5G2->setEnabled(true);
         wyslijWiadomosc("0459" + tmp10 + "|");
    }
    else {
        label6G2->setPixmap(carta10);
        label6G2->setEnabled(true);
         wyslijWiadomosc("0469" + tmp10 + "|");
    }


    pos2 = 9;
    przyznajPunkty(2);
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

        wyslijWiadomosc("09"+r1+r2);

        if(rnd1==2 || rnd2==2)
        {
            if(rnd1==2)
                werdykt = Koniec::Porazka;
            else if (rnd2==2)
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
    niewidoczneG2();
    aktywnyGracz(1);
    pushButtonPasG2->setEnabled(false);
    wydajWerdykt();

    if (rywalPas == false)
            wyslijWiadomosc("10SPASOWAL");

}

void Server::przeciwnikPas(QString c)
{

    rywalPas = true;
    aktywnyGracz(2);
    pushButtonPasG1->setMaximumWidth(70);
    pushButtonPasG1->setText(c);

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
    pushButtonPasG1->setMaximumWidth(50);
    pushButtonPasG1->setText("Pas");
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    pushButtonPasG2->setEnabled(true);

    labelG2->setPixmap(QPixmap(":/ikony/null.png"));
    labelG2->setEnabled(false);
    label1G2->setPixmap(QPixmap(":/ikony/null.png"));
    label1G2->setEnabled(false);
    label2G2->setPixmap(QPixmap(":/ikony/null.png"));
    label2G2->setEnabled(false);
    label3G2->setPixmap(QPixmap(":/ikony/null.png"));
    label3G2->setEnabled(false);
    label4G2->setPixmap(QPixmap(":/ikony/null.png"));
    label4G2->setEnabled(false);
    label5G2->setPixmap(QPixmap(":/ikony/null.png"));
    label5G2->setEnabled(false);
    label6G2->setPixmap(QPixmap(":/ikony/null.png"));
    label6G2->setEnabled(false);

    labelG1->setPixmap(QPixmap(":/ikony/null.png"));
    labelG1->setEnabled(false);
    label1G1->setPixmap(QPixmap(":/ikony/null.png"));
    label1G1->setEnabled(false);
    label2G1->setPixmap(QPixmap(":/ikony/null.png"));
    label2G1->setEnabled(false);
    label3G1->setPixmap(QPixmap(":/ikony/null.png"));
    label3G1->setEnabled(false);
    label4G1->setPixmap(QPixmap(":/ikony/null.png"));
    label4G1->setEnabled(false);
    label5G1->setPixmap(QPixmap(":/ikony/null.png"));
    label5G1->setEnabled(false);
    label6G1->setPixmap(QPixmap(":/ikony/null.png"));
    label6G1->setEnabled(false);


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

