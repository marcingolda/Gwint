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
    metoda[7] = &Server::wymianaKartKlienta;

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
    wymienioneServ = false;

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

void Server::wymianaKart()
{


    Wymiana*wym = new Wymiana(rodzajTalii, tablicaNumerowSerwer);
    wym->exec();

    QString numer, karta;

    if (wym->getWym1() == "0" || wym->getWym2() == "0")
    {
        g2->setKarta(0,talia->dajKarte());
        numer.setNum(g2->getKarta(0)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C1->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "1" || wym->getWym2() == "1")
    {
        g2->setKarta(1,talia->dajKarte());
        numer.setNum(g2->getKarta(1)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C2->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "2" || wym->getWym2() == "2")
    {
        g2->setKarta(2,talia->dajKarte());
        numer.setNum(g2->getKarta(2)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C3->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "3" || wym->getWym2() == "3")
    {
        g2->setKarta(3,talia->dajKarte());
        numer.setNum(g2->getKarta(3)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C4->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "4" || wym->getWym2() == "4")
    {
        g2->setKarta(4,talia->dajKarte());
        numer.setNum(g2->getKarta(4)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C5->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "5" || wym->getWym2() == "5")
    {
        g2->setKarta(5,talia->dajKarte());
        numer.setNum(g2->getKarta(5)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C6->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "6" || wym->getWym2() == "6")
    {
        g2->setKarta(6,talia->dajKarte());
        numer.setNum(g2->getKarta(6)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C7->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "7" || wym->getWym2() == "7")
    {
        g2->setKarta(7,talia->dajKarte());
        numer.setNum(g2->getKarta(7)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C8->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "8" || wym->getWym2() == "8")
    {
        g2->setKarta(8,talia->dajKarte());
        numer.setNum(g2->getKarta(8)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C9->setIcon(QIcon(karta));
    }
    if(wym->getWym1() == "9" || wym->getWym2() == "9")
    {
        g2->setKarta(9,talia->dajKarte());
        numer.setNum(g2->getKarta(9)->getNumer());
        karta = ":talie/" + rodzajTalii + "/" + numer + ".png";
        pushButtonG2C10->setIcon(QIcon(karta));
    }

    ustawLiczbeKartG2();

}


void Server::wymianaKartKlienta(QString c)
{
    QString num;
    QString a = c.mid(0,1);
    QString b = c.mid(1,1);

        if (a == "0" || b == "0")
        {
            g1->setKarta(0,talia1->dajKarte());
            num.setNum(g1->getKarta(0)->getNumer());
            wyslijWiadomosc("010" + num + "|");
        }
        if(a == "1" || b == "1")
        {
            g1->setKarta(1,talia1->dajKarte());
            num.setNum(g1->getKarta(1)->getNumer());
            wyslijWiadomosc("011" + num + "|");
        }
        if(a == "2" || b == "2")
        {
            g1->setKarta(2,talia1->dajKarte());
            num.setNum(g1->getKarta(2)->getNumer());
            wyslijWiadomosc("012" + num + "|");
        }
        if(a == "3" || b == "3")
        {
            g1->setKarta(3,talia1->dajKarte());
            num.setNum(g1->getKarta(3)->getNumer());
            wyslijWiadomosc("013" + num + "|");
        }
        if(a == "4" || b == "4")
        {
            g1->setKarta(4,talia1->dajKarte());
            num.setNum(g1->getKarta(4)->getNumer());
            wyslijWiadomosc("014" + num + "|");
        }
        if(a == "5" || b == "5")
        {
            g1->setKarta(5,talia1->dajKarte());
            num.setNum(g1->getKarta(5)->getNumer());
            wyslijWiadomosc("015" + num + "|");
        }
        if(a == "6" || b == "6")
        {
            g1->setKarta(6,talia1->dajKarte());
            num.setNum(g1->getKarta(6)->getNumer());
            wyslijWiadomosc("016" + num + "|");
        }
        if(a == "7" || b == "7")
        {
            g1->setKarta(7,talia1->dajKarte());
            num.setNum(g1->getKarta(7)->getNumer());
            wyslijWiadomosc("017" + num + "|");
        }
        if(a == "8" || b == "8")
        {
            g1->setKarta(8,talia1->dajKarte());
            num.setNum(g1->getKarta(8)->getNumer());
            wyslijWiadomosc("018" + num + "|");
        }
        if(a == "9" || b == "9")
        {
            g1->setKarta(9,talia1->dajKarte());
            num.setNum(g1->getKarta(9)->getNumer());
            wyslijWiadomosc("019" + num + "|");
        }

        ustawLiczbeKartG1();
        ustawTure(2);
}
void Server::inicjujPartie(QString c)
{

    rodzajTaliiG1 = c;


    talia = new Talia(rodzajTalii);
    talia1 = new Talia(rodzajTaliiG1);


    tura = 0;
    pos1 = -1;
    pos2 = -1;


    g1 = new Gracz(talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte(), talia1->dajKarte());
    g2 = new Gracz(talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte(), talia->dajKarte());


    for(int i=0;i<10;i++)
        tablicaNumerowSerwer[i] = g2->getKarta(i)->getNumer();



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
    num.setNum(g1->getKarta(4)->getNumer());
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
    int r = qrand() % 2;

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

        if(wymienioneServ == false)
        {
            wymienioneServ = true;
            wymianaKart();
            niewidoczneG2();
            ustawTure(1);
        }
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
    QString poz = c.mid(1, 1);
    QString rzad = c.mid(0,1);
        QString tmp1;
        tmp1.setNum(g1->getRzucona()->getNumer());
        QString karta = ":talie2/" + rodzajTaliiG1 + "/" + tmp1 + ".png";
        QString r = c.mid(2,1);


        if (r == "k")
        {
        g1->rodzajRzuconejKarty(r);
        if (poz == "0") {
            kata1G1->setAccessibleName("zajete");
            kata1G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "1") {
            kata2G1->setAccessibleName("zajete");
            kata2G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "2") {
            kata3G1->setAccessibleName("zajete");
            kata3G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "3") {
            kata4G1->setAccessibleName("zajete");
            kata4G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "4") {
            kata5G1->setAccessibleName("zajete");
            kata5G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "5") {
            kata6G1->setAccessibleName("zajete");
            kata6G1->setPixmap(QPixmap(karta));
        }
        else if (poz == "6") {
            kata7G1->setAccessibleName("zajete");
            kata7G1->setPixmap(QPixmap(karta));
        }
        else{
            kata8G1->setAccessibleName("zajete");
            kata8G1->setPixmap(QPixmap(karta));
    }
    }
        else if (r=="l")
        {
            g1->rodzajRzuconejKarty(r);
            if (poz == "0") {
                luk1G1->setAccessibleName("zajete");
                luk1G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "1") {
                luk2G1->setAccessibleName("zajete");
                luk2G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "2") {
                luk3G1->setAccessibleName("zajete");
                luk3G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "3") {
                luk4G1->setAccessibleName("zajete");
                luk4G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "4") {
                luk5G1->setAccessibleName("zajete");
                luk5G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "5") {
                luk6G1->setAccessibleName("zajete");
                luk6G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "6") {
                luk7G1->setAccessibleName("zajete");
                luk7G1->setPixmap(QPixmap(karta));
            }
            else{
                luk8G1->setAccessibleName("zajete");
                luk8G1->setPixmap(QPixmap(karta));
        }
        }
        else if (r=="m")
        {
            g1->rodzajRzuconejKarty(r);
            if (poz == "0") {
                miecz1G1->setPixmap(QPixmap(karta));
                miecz1G1->setAccessibleName("zajete");
            }
            else if (poz == "1") {
                miecz2G1->setAccessibleName("zajete");
                miecz2G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "2") {
                miecz3G1->setAccessibleName("zajete");
                miecz3G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "3") {
                miecz4G1->setAccessibleName("zajete");
                miecz4G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "4") {
                miecz5G1->setAccessibleName("zajete");
                miecz5G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "5") {
                miecz6G1->setAccessibleName("zajete");
                miecz6G1->setPixmap(QPixmap(karta));
            }
            else if (poz == "6") {
                miecz7G1->setAccessibleName("zajete");
                miecz7G1->setPixmap(QPixmap(karta));
            }
            else{
                miecz8G1->setAccessibleName("zajete");
                miecz8G1->setPixmap(QPixmap(karta));
        }
            }
        else
        {

            liczbaKart = g1->getLiczbaKart();

         if(r == "r")
         {
             specG1->setPixmap(QPixmap(karta));
             specG1->setAccessibleName("zajete");
            if(rzad == "w")
            {

                for(int i=0;i<liczbaKart;i++)
                {
                   if(g1->rzuconeKartyMiecz[i]->getBohater() == 0)
                   {
                        g1->zwiekszPunkty(g1->rzuconeKartyMiecz[i]->getSila());
                        g1->rzuconeKartyMiecz[i]->setOrginalnaSila(g1->rzuconeKartyMiecz[i]->getSila());
                        g1->rzuconeKartyMiecz[i]->setSila(2*(g1->rzuconeKartyMiecz[i]->getSila()));
                   }
                }
            }
            else if(rzad == "s")
            {
                for(int i=0;i<liczbaKart;i++)
                {
                    if(g1->rzuconeKartyLuk[i]->getBohater() == 0)
                    {
                        g1->zwiekszPunkty(g1->rzuconeKartyLuk[i]->getSila());
                        g1->rzuconeKartyLuk[i]->setOrginalnaSila(g1->rzuconeKartyLuk[i]->getSila());
                        g1->rzuconeKartyLuk[i]->setSila(2*(g1->rzuconeKartyLuk[i]->getSila()));
                    }
                }
            }
            else
            {
                for(int i=0;i<liczbaKart;i++)
                {
                    if(g1->rzuconeKartyKata[i]->getBohater() == 0)
                    {
                        g1->zwiekszPunkty(g1->rzuconeKartyKata[i]->getSila());
                        g1->rzuconeKartyKata[i]->setOrginalnaSila(g1->rzuconeKartyKata[i]->getSila());
                        g1->rzuconeKartyKata[i]->setSila(2*(g1->rzuconeKartyKata[i]->getSila()));
                    }
                }
            }
}
         else
         {
             pogodaG1->setPixmap(QPixmap(karta));
             pogodaG1->setAccessibleName("zajete");

             if(r == "t")
             {
             for(int i=0;i<liczbaKart;i++)
             {
                 if (g1->rzuconeKartyMiecz[i]->getRodzaj() != NULL && g1->rzuconeKartyMiecz[i]->getBohater() == 0)
                 {
                roznica = g1->rzuconeKartyMiecz[i]->getSila()-1;
                g1->rzuconeKartyMiecz[i]->setOrginalnaSila(g1->rzuconeKartyMiecz[i]->getSila());
                g1->zmniejszPunkty(roznica);
                g1->rzuconeKartyMiecz[i]->setSila(1);
                g1->setZmienioneMiecz(i+1);
                 }
                 if (g2->rzuconeKartyMiecz[i]->getRodzaj() != NULL && g2->rzuconeKartyMiecz[i]->getBohater() == 0)
                 {
                roznica = g2->rzuconeKartyMiecz[i]->getSila() - 1;
                g2->rzuconeKartyMiecz[i]->setOrginalnaSila(g2->rzuconeKartyMiecz[i]->getSila());
                g2->zmniejszPunkty(roznica);
                g2->rzuconeKartyMiecz[i]->setSila(1);
                g2->setZmienioneMiecz(i+1);
                aktualizujPunkty(2);
                 }
             }
         }
         else if (r == "g")
         {
             for(int i=0;i<liczbaKart;i++)
             {
                 if (g1->rzuconeKartyLuk[i]->getRodzaj() != NULL && g1->rzuconeKartyLuk[i]->getBohater() == 0)
                 {
                roznica = g1->rzuconeKartyLuk[i]->getSila() - 1;
                g1->rzuconeKartyLuk[i]->setOrginalnaSila(g1->rzuconeKartyLuk[i]->getSila());
                g1->zmniejszPunkty(roznica);
                g1->rzuconeKartyLuk[i]->setSila(1);
                g1->setZmienioneLuk(i+1);
                 }
                 if (g2->rzuconeKartyLuk[i]->getRodzaj() != NULL && g2->rzuconeKartyLuk[i]->getBohater() == 0)
                 {
                roznica = g2->rzuconeKartyLuk[i]->getSila() - 1;
                g2->rzuconeKartyLuk[i]->setOrginalnaSila(g2->rzuconeKartyLuk[i]->getSila());
                g2->zmniejszPunkty(roznica);
                g2->rzuconeKartyLuk[i]->setSila(1);
                g2->setZmienioneLuk(i+1);
                aktualizujPunkty(2);
                 }
             }

         }
         else if (r == "u")
         {
             for(int i=0;i<liczbaKart;i++)
             {
                 if (g1->rzuconeKartyKata[i]->getRodzaj() != NULL && g1->rzuconeKartyKata[i]->getBohater() == 0)
                 {
                roznica = g1->rzuconeKartyKata[i]->getSila() - 1;
                g1->rzuconeKartyKata[i]->setOrginalnaSila(g1->rzuconeKartyKata[i]->getSila());
                g1->zmniejszPunkty(roznica);
                g1->rzuconeKartyKata[i]->setSila(1);
                g1->setZmienioneKata(i+1);
                 }
                 if (g2->rzuconeKartyKata[i]->getRodzaj() != NULL && g2->rzuconeKartyKata[i]->getBohater() == 0)
                 {
                roznica = g2->rzuconeKartyKata[i]->getSila() - 1;
                g2->rzuconeKartyKata[i]->setOrginalnaSila(g2->rzuconeKartyKata[i]->getSila());
                g2->zmniejszPunkty(roznica);
                g2->rzuconeKartyKata[i]->setSila(1);
                g2->setZmienioneKata(i+1);
                aktualizujPunkty(2);
                 }
             }
         }
         else
         {
                 for (int i=0;i<g1->getZmienioneMiecz();i++)
                 {
                     if(g1->rzuconeKartyMiecz[i]->getBohater() == 0) {
                     g1->rzuconeKartyMiecz[i]->setSila(g1->rzuconeKartyMiecz[i]->getOrginalnaSila());
                     roznica = g1->rzuconeKartyMiecz[i]->getSila() - 1;
                     g1->zwiekszPunkty(roznica);
                     }
                 }

                 for (int i=0;i<g1->getZmienioneLuk();i++)
                 {
                     if(g1->rzuconeKartyLuk[i]->getBohater() == 0) {
                     g1->rzuconeKartyLuk[i]->setSila(g1->rzuconeKartyLuk[i]->getOrginalnaSila());
                     roznica = g1->rzuconeKartyLuk[i]->getSila() - 1;
                     g1->zwiekszPunkty(roznica);
                     }
                }
                 for (int i=0;i<g1->getZmienioneKata();i++)
                 {
                     if(g1->rzuconeKartyKata[i]->getBohater() == 0) {
                     g1->rzuconeKartyKata[i]->setSila(g1->rzuconeKartyKata[i]->getOrginalnaSila());
                     roznica = g1->rzuconeKartyKata[i]->getSila() - 1;
                     g1->zwiekszPunkty(roznica);
                     }
                }
                 for (int i=0;i<g2->getZmienioneMiecz();i++)
                 {
                     if(g2->rzuconeKartyMiecz[i]->getBohater() == 0) {
                     g2->rzuconeKartyMiecz[i]->setSila(g2->rzuconeKartyMiecz[i]->getOrginalnaSila());
                     roznica = g2->rzuconeKartyMiecz[i]->getSila() - 1;
                     g2->zwiekszPunkty(roznica);
                     aktualizujPunkty(2);
                     }
                 }

                 for (int i=0;i<g2->getZmienioneLuk();i++)
                 {
                     if(g2->rzuconeKartyLuk[i]->getBohater() == 0) {
                     g2->rzuconeKartyLuk[i]->setSila(g2->rzuconeKartyLuk[i]->getOrginalnaSila());
                     roznica = g2->rzuconeKartyLuk[i]->getSila() - 1;
                     g2->zwiekszPunkty(roznica);
                     aktualizujPunkty(2);
                     }
                 }

                 for (int i=0;i<g2->getZmienioneKata();i++)
                 {
                     if(g2->rzuconeKartyKata[i]->getBohater() == 0) {
                     g2->rzuconeKartyKata[i]->setSila(g2->rzuconeKartyKata[i]->getOrginalnaSila());
                     roznica = g2->rzuconeKartyKata[i]->getSila() - 1;
                     g2->zwiekszPunkty(roznica);
                     aktualizujPunkty(2);
                     }
                 }

                 g1->setZmienioneKata(0);
                 g1->setZmienioneLuk(0);
                 g1->setZmienioneMiecz(0);
                 g2->setZmienioneKata(0);
                 g2->setZmienioneLuk(0);
                 g2->setZmienioneMiecz(0);

         }


        }


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
        aktualizujPunkty(2);
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
        aktualizujPunkty(1);
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







void Server::klikKarta(QString c)
{

    QString tmp1;
    tmp1.setNum(g2->getRzucona()->getNumer());
    QString karta = ":talie2/" + rodzajTalii + "/" + tmp1 + ".png";
    QString tmp2;

    if(c != "")
        tmp2 = c;
    else
        tmp2 = g2->getRzucona()->getRodzaj();


    if(tmp2=="k")
    {
    g2->rodzajRzuconejKarty(tmp2);
    if (kata1G2->accessibleName()=="wolne") {
    kata1G2->setPixmap(karta);
    kata1G2->setAccessibleName("zajete");
     wyslijWiadomosc("04k0" + tmp1 + "|");
    }
    else if (kata2G2->accessibleName()=="wolne") {
        kata2G2->setPixmap(karta);
        kata2G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k1" + tmp1 + "|");
    }
    else if (kata3G2->accessibleName()=="wolne") {
        kata3G2->setPixmap(karta);
        kata3G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k2" + tmp1 + "|");
    }
    else if (kata4G2->accessibleName()=="wolne") {
        kata4G2->setPixmap(karta);
        kata4G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k3" + tmp1 + "|");
    }
    else if (kata5G2->accessibleName()=="wolne") {
        kata5G2->setPixmap(karta);
        kata5G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k4" + tmp1 + "|");
    }
    else if (kata6G2->accessibleName()=="wolne") {
        kata6G2->setPixmap(karta);
        kata6G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k5" + tmp1 + "|");
    }
    else if (kata7G2->accessibleName()=="wolne") {
        kata7G2->setPixmap(karta);
        kata7G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k6" + tmp1 + "|");
    }
    else {
        kata8G2->setPixmap(karta);
        kata8G2->setAccessibleName("zajete");
         wyslijWiadomosc("04k7" + tmp1 + "|");
    }
    przyznajPunkty(2);
}
    else if(tmp2 == "l")
    {
        g2->rodzajRzuconejKarty(tmp2);
        if (luk1G2->accessibleName()=="wolne") {
        luk1G2->setPixmap(karta);
        luk1G2->setAccessibleName("zajete");
         wyslijWiadomosc("04l0" + tmp1 + "|");
        }
        else if (luk2G2->accessibleName()=="wolne") {
            luk2G2->setPixmap(karta);
            luk2G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l1" + tmp1 + "|");
        }
        else if (luk3G2->accessibleName()=="wolne") {
            luk3G2->setPixmap(karta);
            luk3G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l2" + tmp1 + "|");
        }
        else if (luk4G2->accessibleName()=="wolne") {
            luk4G2->setPixmap(karta);
            luk4G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l3" + tmp1 + "|");
        }
        else if (luk5G2->accessibleName()=="wolne") {
            luk5G2->setPixmap(karta);
            luk5G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l4" + tmp1 + "|");
        }
        else if (luk6G2->accessibleName()=="wolne") {
            luk6G2->setPixmap(karta);
            luk6G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l5" + tmp1 + "|");
        }
        else if (luk7G2->accessibleName()=="wolne") {
            luk7G2->setPixmap(karta);
            luk7G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l6" + tmp1 + "|");
        }
        else {
            luk8G2->setPixmap(karta);
            luk8G2->setAccessibleName("zajete");
             wyslijWiadomosc("04l7" + tmp1 + "|");
        }
        przyznajPunkty(2);
    }
    else if (tmp2 == "m")
    {

        g2->rodzajRzuconejKarty(tmp2);
        if (miecz1G2->accessibleName()=="wolne") {
        miecz1G2->setPixmap(karta);
        miecz1G2->setAccessibleName("zajete");
         wyslijWiadomosc("04m0" + tmp1 + "|");
        }
        else if (miecz2G2->accessibleName()=="wolne") {
            miecz2G2->setPixmap(karta);
            miecz2G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m1" + tmp1 + "|");
        }
        else if (miecz3G2->accessibleName()=="wolne") {
            miecz3G2->setPixmap(karta);
            miecz3G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m2" + tmp1 + "|");
        }
        else if (miecz4G2->accessibleName()=="wolne") {
            miecz4G2->setPixmap(karta);
            miecz4G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m3" + tmp1 + "|");
        }
        else if (miecz5G2->accessibleName()=="wolne") {
            miecz5G2->setPixmap(karta);
            miecz5G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m4" + tmp1 + "|");
        }
        else if (miecz6G2->accessibleName()=="wolne") {
            miecz6G2->setPixmap(karta);
            miecz6G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m5" + tmp1 + "|");
        }
        else if (miecz7G2->accessibleName()=="wolne") {
            miecz7G2->setPixmap(karta);
            miecz7G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m6" + tmp1 + "|");
        }
        else {
            miecz8G2->setPixmap(karta);
            miecz8G2->setAccessibleName("zajete");
             wyslijWiadomosc("04m7" + tmp1 + "|");
        }
        przyznajPunkty(2);
    }
    else if (tmp2 == "h")
    {
        WyborRzedu *wyborRzedu = new WyborRzedu("podwojnyZasieg");
        wyborRzedu->exec();

        if(wyborRzedu->getRzad() == "walczace")
        {
            klikKarta("m");
        }
        else if(wyborRzedu->getRzad() == "strzeleckie")
        {
            klikKarta("l");
        }
    }
    else
    {
        wyslijWiadomosc("04"+tmp2+"0" + tmp1 + "|");
        liczbaKart = g2->getLiczbaKart();

        if(tmp2 == "r")
        {
            specG2->setPixmap(karta);
            specG2->setAccessibleName("zajete");

            WyborRzedu *wyborRzedu = new WyborRzedu("");
            wyborRzedu->exec();

           if(wyborRzedu->getRzad() == "walczace")
           {

               for(int i=0;i<liczbaKart;i++)
               {
                   if(g2->rzuconeKartyMiecz[i]->getBohater() == 0)
                   {

                        g2->zwiekszPunkty(g2->rzuconeKartyMiecz[i]->getSila());
                        g2->rzuconeKartyMiecz[i]->setOrginalnaSila(g2->rzuconeKartyMiecz[i]->getSila());
                        g2->rzuconeKartyMiecz[i]->setSila(2*(g2->rzuconeKartyMiecz[i]->getSila()));
                   }
               }
           }
           else if(wyborRzedu->getRzad() == "strzeleckie")
           {
               for(int i=0;i<liczbaKart;i++)
               {
                   if(g2->rzuconeKartyLuk[i]->getBohater() == 0)
                   {
                        g2->zwiekszPunkty(g2->rzuconeKartyLuk[i]->getSila());
                        g2->rzuconeKartyLuk[i]->setOrginalnaSila(g2->rzuconeKartyLuk[i]->getSila());
                        g2->rzuconeKartyLuk[i]->setSila(2*(g2->rzuconeKartyLuk[i]->getSila()));
                   }
               }
           }
           else
           {
               for(int i=0;i<liczbaKart;i++)
               {
                   if(g2->rzuconeKartyKata[i]->getBohater() == 0)
                   {
                        g2->zwiekszPunkty(g2->rzuconeKartyKata[i]->getSila());
                        g2->rzuconeKartyKata[i]->setOrginalnaSila(g2->rzuconeKartyKata[i]->getSila());
                        g2->rzuconeKartyKata[i]->setSila(2*(g2->rzuconeKartyKata[i]->getSila()));
                   }
               }
           }
           przyznajPunkty(2);
}
        else
        {
            pogodaG2->setPixmap(karta);
            pogodaG2->setAccessibleName("zajete");

            if (tmp2 == "t")
            {
            for(int i=0;i<liczbaKart;i++)
            {
                if (g2->rzuconeKartyMiecz[i]->getRodzaj() != NULL && g2->rzuconeKartyMiecz[i]->getBohater() == 0)
                {
               roznica = g2->rzuconeKartyMiecz[i]->getSila() - 1;
               g2->rzuconeKartyMiecz[i]->setOrginalnaSila(g2->rzuconeKartyMiecz[i]->getSila());
               g2->zmniejszPunkty(roznica);
               g2->rzuconeKartyMiecz[i]->setSila(1);
               g2->setZmienioneMiecz(i+1);
                }
                if (g1->rzuconeKartyMiecz[i]->getRodzaj() != NULL && g1->rzuconeKartyMiecz[i]->getBohater() == 0)
                {
               roznica = g1->rzuconeKartyMiecz[i]->getSila() - 1;
               g1->rzuconeKartyMiecz[i]->setOrginalnaSila(g1->rzuconeKartyMiecz[i]->getSila());
               g1->zmniejszPunkty(roznica);
               g1->rzuconeKartyMiecz[i]->setSila(1);
               g1->setZmienioneMiecz(i+1);
               aktualizujPunkty(1);
                }
            }
            przyznajPunkty(2);
        }
        else if (tmp2 == "g")
        {
            for(int i=0;i<liczbaKart;i++)
            {
                if (g2->rzuconeKartyLuk[i]->getRodzaj() != NULL && g2->rzuconeKartyLuk[i]->getBohater() == 0)
                {
               roznica = g2->rzuconeKartyLuk[i]->getSila() - 1;
               g2->rzuconeKartyLuk[i]->setOrginalnaSila(g2->rzuconeKartyLuk[i]->getSila());
               g2->zmniejszPunkty(roznica);
               g2->rzuconeKartyLuk[i]->setSila(1);
               g2->setZmienioneLuk(i+1);
                }
                if (g1->rzuconeKartyLuk[i]->getRodzaj() != NULL && g1->rzuconeKartyLuk[i]->getBohater() == 0)
                {
               roznica = g1->rzuconeKartyLuk[i]->getSila() - 1;
               g1->rzuconeKartyLuk[i]->setOrginalnaSila(g1->rzuconeKartyLuk[i]->getSila());
               g1->zmniejszPunkty(roznica);
               g1->rzuconeKartyLuk[i]->setSila(1);
               g1->setZmienioneLuk(i+1);
               aktualizujPunkty(1);
                }
            }
            przyznajPunkty(2);

        }
        else if (tmp2 == "u")
        {
            for(int i=0;i<liczbaKart;i++)
            {
                if (g2->rzuconeKartyKata[i]->getRodzaj() != NULL && g2->rzuconeKartyKata[i]->getBohater() == 0)
                {
               roznica = g2->rzuconeKartyKata[i]->getSila() - 1;
               g2->rzuconeKartyKata[i]->setOrginalnaSila(g2->rzuconeKartyKata[i]->getSila());
               g2->zmniejszPunkty(roznica);
               g2->rzuconeKartyKata[i]->setSila(1);
               g2->setZmienioneKata(i+1);
                }
                if (g1->rzuconeKartyKata[i]->getRodzaj() != NULL && g1->rzuconeKartyKata[i]->getBohater() == 0)
                {
               roznica = g1->rzuconeKartyKata[i]->getSila() - 1;
               g1->rzuconeKartyKata[i]->setOrginalnaSila(g1->rzuconeKartyKata[i]->getSila());
               g1->zmniejszPunkty(roznica);
               g1->rzuconeKartyKata[i]->setSila(1);
               g1->setZmienioneKata(i+1);
               aktualizujPunkty(1);
                }
            }
            przyznajPunkty(2);
        }
        else
        {
                for (int i=0;i<g1->getZmienioneMiecz();i++)
                {
                    if(g1->rzuconeKartyMiecz[i]->getBohater() == 0) {
                    g1->rzuconeKartyMiecz[i]->setSila(g1->rzuconeKartyMiecz[i]->getOrginalnaSila());
                    roznica = g1->rzuconeKartyMiecz[i]->getSila() - 1;
                    g1->zwiekszPunkty(roznica);
                    aktualizujPunkty(1);
                    }
                }

                for (int i=0;i<g1->getZmienioneLuk();i++)
                {
                    if(g1->rzuconeKartyLuk[i]->getBohater() == 0) {
                    g1->rzuconeKartyLuk[i]->setSila(g1->rzuconeKartyLuk[i]->getOrginalnaSila());
                    roznica = g1->rzuconeKartyLuk[i]->getSila() - 1;
                    g1->zwiekszPunkty(roznica);
                    aktualizujPunkty(1);
                    }
               }
                for (int i=0;i<g1->getZmienioneKata();i++)
                {
                    if(g1->rzuconeKartyKata[i]->getBohater() == 0) {
                    g1->rzuconeKartyKata[i]->setSila(g1->rzuconeKartyKata[i]->getOrginalnaSila());
                    roznica = g1->rzuconeKartyKata[i]->getSila() - 1;
                    g1->zwiekszPunkty(roznica);
                    aktualizujPunkty(1);
                    }
               }
                for (int i=0;i<g2->getZmienioneMiecz();i++)
                {
                    if(g2->rzuconeKartyMiecz[i]->getBohater() == 0) {
                    g2->rzuconeKartyMiecz[i]->setSila(g2->rzuconeKartyMiecz[i]->getOrginalnaSila());
                    roznica = g2->rzuconeKartyMiecz[i]->getSila() - 1;
                    g2->zwiekszPunkty(roznica);
                    }
                }

                for (int i=0;i<g2->getZmienioneLuk();i++)
                {
                    if(g2->rzuconeKartyLuk[i]->getBohater() == 0) {
                    g2->rzuconeKartyLuk[i]->setSila(g2->rzuconeKartyLuk[i]->getOrginalnaSila());
                    roznica = g2->rzuconeKartyLuk[i]->getSila() - 1;
                    g2->zwiekszPunkty(roznica);
                    }
                }

                for (int i=0;i<g2->getZmienioneKata();i++)
                {
                    if(g2->rzuconeKartyKata[i]->getBohater() == 0) {
                    g2->rzuconeKartyKata[i]->setSila(g2->rzuconeKartyKata[i]->getOrginalnaSila());
                    roznica = g2->rzuconeKartyKata[i]->getSila() - 1;
                    g2->zwiekszPunkty(roznica);
                    }
                }

                g1->setZmienioneKata(0);
                g1->setZmienioneLuk(0);
                g1->setZmienioneMiecz(0);
                g2->setZmienioneKata(0);
                g2->setZmienioneLuk(0);
                g2->setZmienioneMiecz(0);

        }

    przyznajPunkty(2);
    }

}
}
void Server::aktualizujPunkty(int p)
{
    if (p == 1)
    {
        QString punkty1;
        punkty1.setNum(g1->getPunkty());
        lineEditPktG1->setText(punkty1);
        wyslijWiadomosc("05" + punkty1 + "|");
    }
    else if(p == 2)
    {
        QString punkty2;
        punkty2.setNum(g2->getPunkty());
        lineEditPktG2->setText(punkty2);
        wyslijWiadomosc("06" + punkty2 + "|");
    }
}

void Server::klikKarta1()
{
    g2->rzuconaKarta(0);
    pushButtonG2C1->setHidden(true);
    niewidoczneG2();


    wyslijWiadomosc("120|");
    klikKarta("");

    pos2 = 0;

}

void Server::klikKarta2()
{
    g2->rzuconaKarta(1);
    pushButtonG2C2->setHidden(true);
    niewidoczneG2();




    wyslijWiadomosc("121|");
    klikKarta("");

    pos2 = 1;
}

void Server::klikKarta3()
{
    g2->rzuconaKarta(2);
    pushButtonG2C3->setHidden(true);
    niewidoczneG2();



    wyslijWiadomosc("122|");
    klikKarta("");

    pos2 = 2;
}

void Server::klikKarta4()
{
    g2->rzuconaKarta(3);
    pushButtonG2C4->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("123|");
    klikKarta("");

    pos2 = 3;
}

void Server::klikKarta5()
{
    g2->rzuconaKarta(4);
    pushButtonG2C5->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("124|");
    klikKarta("");
    pos2 = 4;
}

void Server::klikKarta6()
{
    g2->rzuconaKarta(5);
    pushButtonG2C6->setHidden(true);
   niewidoczneG2();
   wyslijWiadomosc("125|");
   klikKarta("");
    pos2 = 5;
}

void Server::klikKarta7()
{
    g2->rzuconaKarta(6);
    pushButtonG2C7->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("126|");
    klikKarta("");

    pos2 = 6;
}

void Server::klikKarta8()
{
    g2->rzuconaKarta(7);
    pushButtonG2C8->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("127|");
    klikKarta("");
    pos2 = 7;

}

void Server::klikKarta9()
{
    g2->rzuconaKarta(8);
    pushButtonG2C9->setHidden(true);
    niewidoczneG2();

    wyslijWiadomosc("128|");
    klikKarta("");
    pos2 = 8;
}

void Server::klikKarta10()
{
    g2->rzuconaKarta(9);
    pushButtonG2C10->setHidden(true);

    niewidoczneG2();

    wyslijWiadomosc("129|");
    klikKarta("");

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
            if(rnd1==2 && rnd2 == 2)
                werdykt = Koniec::Remis;
            else if (rnd2 == 2)
                werdykt = Koniec::Zwyciestwo;
            else
                werdykt = Koniec::Porazka;


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


    QPixmap pixmap(42,80);
    pixmap.fill(Qt::transparent); //


    kata1G1->setPixmap(pixmap);
    kata1G1->setAccessibleName("wolne");
    kata2G1->setPixmap(pixmap);
    kata2G1->setAccessibleName("wolne");
    kata3G1->setPixmap(pixmap);
    kata3G1->setAccessibleName("wolne");
    kata4G1->setPixmap(pixmap);
    kata4G1->setAccessibleName("wolne");
    kata5G1->setPixmap(pixmap);
    kata5G1->setAccessibleName("wolne");
    kata6G1->setPixmap(pixmap);
    kata6G1->setAccessibleName("wolne");
    kata7G1->setPixmap(pixmap);
    kata7G1->setAccessibleName("wolne");
    kata8G1->setPixmap(pixmap);
    kata8G1->setAccessibleName("wolne");

    luk1G1->setPixmap(pixmap);
    luk1G1->setAccessibleName("wolne");
    luk2G1->setPixmap(pixmap);
    luk2G1->setAccessibleName("wolne");
    luk3G1->setPixmap(pixmap);
    luk3G1->setAccessibleName("wolne");
    luk4G1->setPixmap(pixmap);
    luk4G1->setAccessibleName("wolne");
    luk5G1->setPixmap(pixmap);
    luk5G1->setAccessibleName("wolne");
    luk6G1->setPixmap(pixmap);
    luk6G1->setAccessibleName("wolne");
    luk7G1->setPixmap(pixmap);
    luk7G1->setAccessibleName("wolne");
    luk8G1->setPixmap(pixmap);
    luk8G1->setAccessibleName("wolne");

    miecz1G1->setPixmap(pixmap);
    miecz1G1->setAccessibleName("wolne");
    miecz2G1->setPixmap(pixmap);
    miecz2G1->setAccessibleName("wolne");
    miecz3G1->setPixmap(pixmap);
    miecz3G1->setAccessibleName("wolne");
    miecz4G1->setPixmap(pixmap);
    miecz4G1->setAccessibleName("wolne");
    miecz5G1->setPixmap(pixmap);
    miecz5G1->setAccessibleName("wolne");
    miecz6G1->setPixmap(pixmap);
    miecz6G1->setAccessibleName("wolne");
    miecz7G1->setPixmap(pixmap);
    miecz7G1->setAccessibleName("wolne");
    miecz8G1->setPixmap(pixmap);
    miecz8G1->setAccessibleName("wolne");

    kata1G2->setPixmap(pixmap);
    kata1G2->setAccessibleName("wolne");
    kata2G2->setPixmap(pixmap);
    kata2G2->setAccessibleName("wolne");
    kata3G2->setPixmap(pixmap);
    kata3G2->setAccessibleName("wolne");
    kata4G2->setPixmap(pixmap);
    kata4G2->setAccessibleName("wolne");
    kata5G2->setPixmap(pixmap);
    kata5G2->setAccessibleName("wolne");
    kata6G2->setPixmap(pixmap);
    kata6G2->setAccessibleName("wolne");
    kata7G2->setPixmap(pixmap);
    kata7G2->setAccessibleName("wolne");
    kata8G2->setPixmap(pixmap);
    kata8G2->setAccessibleName("wolne");

    luk1G2->setPixmap(pixmap);
    luk1G2->setAccessibleName("wolne");
    luk2G2->setPixmap(pixmap);
    luk2G2->setAccessibleName("wolne");
    luk3G2->setPixmap(pixmap);
    luk3G2->setAccessibleName("wolne");
    luk4G2->setPixmap(pixmap);
    luk4G2->setAccessibleName("wolne");
    luk5G2->setPixmap(pixmap);
    luk5G2->setAccessibleName("wolne");
    luk6G2->setPixmap(pixmap);
    luk6G2->setAccessibleName("wolne");
    luk7G2->setPixmap(pixmap);
    luk7G2->setAccessibleName("wolne");
    luk8G2->setPixmap(pixmap);
    luk8G2->setAccessibleName("wolne");

    miecz1G2->setPixmap(pixmap);
    miecz1G2->setAccessibleName("wolne");
    miecz2G2->setPixmap(pixmap);
    miecz2G2->setAccessibleName("wolne");
    miecz3G2->setPixmap(pixmap);
    miecz3G2->setAccessibleName("wolne");
    miecz4G2->setPixmap(pixmap);
    miecz4G2->setAccessibleName("wolne");
    miecz5G2->setPixmap(pixmap);
    miecz5G2->setAccessibleName("wolne");
    miecz6G2->setPixmap(pixmap);
    miecz6G2->setAccessibleName("wolne");
    miecz7G2->setPixmap(pixmap);
    miecz7G2->setAccessibleName("wolne");
    miecz8G2->setPixmap(pixmap);
    miecz8G2->setAccessibleName("wolne");

    specG1->setPixmap(pixmap);
    specG1->setAccessibleName("wolne");

    specG2->setPixmap(pixmap);
    specG2->setAccessibleName("wolne");

    g1->wyczyscKarty();
    g2->wyczyscKarty();

}

void Server::odbierzSygnalG1()
{
    g1->setNullRzucona();
    g2->setNullRzucona();


      ustawTure(1);


}

void Server::odbierzSygnalG2()
{
    g1->setNullRzucona();
    g2->setNullRzucona();


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



