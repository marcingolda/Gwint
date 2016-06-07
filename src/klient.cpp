#include "klient.h"

Klient::Klient(QString _nick, QString _ip, int _port, QWidget *parent) :
	QMainWindow(parent)
{
	setupUi(this);
	nick = _nick;
	ip = _ip;
    port = _port;

    inicjuj();

    QDesktopWidget *widget = QApplication::desktop();
    QRect dim = widget->screenGeometry();
    setGeometry((dim.width() - width()) / 2, (dim.height() - height()) / 2, width(), height());



	socket = new QTcpSocket(this);
	buffer = new QBuffer(this);
	buffer->open(QIODevice::ReadWrite);

    connect(socket, SIGNAL(readyRead()), this, SLOT(odbierzWiadomosc()));
    connect(pushButtonG1C1, SIGNAL(clicked()), this, SLOT(klikKarta1()));
    connect(pushButtonG1C2, SIGNAL(clicked()), this, SLOT(klikKarta2()));
    connect(pushButtonG1C3, SIGNAL(clicked()), this, SLOT(klikKarta3()));
    connect(pushButtonG1C4, SIGNAL(clicked()), this, SLOT(klikKarta4()));
    connect(pushButtonG1C5, SIGNAL(clicked()), this, SLOT(klikKarta5()));
    connect(pushButtonG1C6, SIGNAL(clicked()), this, SLOT(klikKarta6()));
    connect(pushButtonG1C7, SIGNAL(clicked()), this, SLOT(klikKarta7()));
    connect(pushButtonG1C8, SIGNAL(clicked()), this, SLOT(klikKarta8()));
    connect(pushButtonG1C9, SIGNAL(clicked()), this, SLOT(klikKarta9()));
    connect(pushButtonG1C10, SIGNAL(clicked()), this, SLOT(klikKarta10()));
    connect(pushButtonPasG1, SIGNAL(clicked()), this, SLOT(klikPas()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(blad(QAbstractSocket::SocketError)));

    socket->connectToHost(ip, port);
    wyslijWiadomosc("03" + rodzajTalii + "|");
    wyslijWiadomosc("00" + nick + "|");


    metoda[0] = &Klient::ustawNickSerwera;
    metoda[1] = &Klient::ustawKarty;
    metoda[2] = &Klient::ustawLiczbeKartG2;
    metoda[3] = &Klient::ustawTure;
    metoda[4] = &Klient::ustawKartySerwera;
    metoda[5] = &Klient::aktualizujPunkty;
    metoda[6] = &Klient::aktualizujPunktySerwera;
    metoda[7] = &Klient::serwerOdlaczony;
    metoda[8] = &Klient::ustawLiczbeKartG1;
    metoda[9] = &Klient::ustawLiczbeRund;
    metoda[10] = &Klient::przeciwnikPas;
    metoda[11] = &Klient::klikKarta;
    metoda[12] = &Klient::ktoraKartaSerwera;

}

void Klient::blad(QAbstractSocket::SocketError se)
{
	if (se == QAbstractSocket::ConnectionRefusedError) {
		delete socket;
		delete buffer;

        QMessageBox::critical(this, tr("Error"), tr("Serwer nie odpowiada"));

		socket = new QTcpSocket(this);
		buffer = new QBuffer(this);
		buffer->open(QIODevice::ReadWrite);
	}
}

Klient::~Klient()
{
	buffer->close();
}

void Klient::inicjuj()
{


	groupBoxG1->setTitle(nick);
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    lineEditRundyG1->setText("0");
    lineEditRundyG2->setText("0");
    niewidoczneG2();
    rywalPas = false;
    Pas = false;



}

void Klient::niewidoczneG2()
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

void Klient::wyslijWiadomosc(QString message)
{
	socket->write(message.toLatin1());
}

void Klient::odbierzWiadomosc()
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

void Klient::serwerOdlaczony(QString)
{
    QMessageBox::critical(this, tr("Information"), tr("Utracono polaczenie z serwerem"));
    wrocDoMenu();
}


void Klient::wrocDoMenu()
{
	socket->close();
	buffer->close();
	setVisible(false);
    Start *a = new Start();
	a->show();
	a->setVisible(true);
	destroy();
}



void Klient::aktualizujPunkty(QString p)
{
    lineEditPktG1->setText(p);
}

void Klient::aktualizujPunktySerwera(QString p)
{
    lineEditPktG2->setText(p);
}


void Klient::ktoraKartaSerwera(QString c)
{
        QString pos = c.mid(0, 1);


    if (pos == "0")
        pushButtonG2C1->setHidden(true);
    else if (pos == "1")
        pushButtonG2C2->setHidden(true);
    else if (pos == "2")
        pushButtonG2C3->setHidden(true);
    else if (pos == "3")
        pushButtonG2C4->setHidden(true);
    else if (pos == "4")
        pushButtonG2C5->setHidden(true);
    else if (pos == "5")
        pushButtonG2C6->setHidden(true);
    else if (pos == "6")
        pushButtonG2C7->setHidden(true);
    else if (pos == "7")
        pushButtonG2C8->setHidden(true);
    else if (pos == "8")
        pushButtonG2C9->setHidden(true);
    else
        pushButtonG2C10->setHidden(true);
}



void Klient::ustawKartySerwera(QString c)
{
    QString r = c.mid(0,1);
    QString poz = c.mid(1,1);
    int tmp = c.mid(2).toInt();
    QString numer;
    numer.setNum(tmp);
    QString iconaG2 = ":talie2/" + rodzajTaliiG2 + "/" + numer + ".png";





    if (r == "k")
    {
    if (poz == "0") {
        kata1G2->setEnabled(true);
        kata1G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "1") {
        kata2G2->setEnabled(true);
        kata2G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "2") {
        kata3G2->setEnabled(true);
        kata3G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "3") {
        kata4G2->setEnabled(true);
        kata4G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "4") {
        kata5G2->setEnabled(true);
        kata5G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "5") {
        kata6G2->setEnabled(true);
        kata6G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "6") {
        kata7G2->setEnabled(true);
        kata7G2->setPixmap(QPixmap(iconaG2));
    }
    else{
        kata8G2->setEnabled(true);
        kata8G2->setPixmap(QPixmap(iconaG2));
}
}
    else if (r=="l")
    {
        if (poz == "0") {
            luk1G2->setEnabled(true);
            luk1G2->setPixmap(iconaG2);
        }
        else if (poz == "1") {
            luk2G2->setEnabled(true);
            luk2G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "2") {
            luk3G2->setEnabled(true);
            luk3G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "3") {
            luk4G2->setEnabled(true);
            luk4G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "4") {
            luk5G2->setEnabled(true);
            luk5G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "5") {
            luk6G2->setEnabled(true);
            luk6G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "6") {
            luk7G2->setEnabled(true);
            luk7G2->setPixmap(QPixmap(iconaG2));
        }
        else{
            luk8G2->setEnabled(true);
            luk8G2->setPixmap(QPixmap(iconaG2));
    }
    }
    else if (r=="m")
    {
        if (poz == "0") {
            miecz1G2->setEnabled(true);
            miecz1G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "1") {
            miecz2G2->setEnabled(true);
            miecz2G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "2") {
            miecz3G2->setEnabled(true);
            miecz3G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "3") {
            miecz4G2->setEnabled(true);
            miecz4G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "4") {
            miecz5G2->setEnabled(true);
            miecz5G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "5") {
            miecz6G2->setEnabled(true);
            miecz6G2->setPixmap(QPixmap(iconaG2));
        }
        else if (poz == "6") {
            miecz7G2->setEnabled(true);
            miecz7G2->setPixmap(QPixmap(iconaG2));
        }
        else {
            miecz8G2->setEnabled(true);
            miecz8G2->setPixmap(QPixmap(iconaG2));
    }
        }
    else
    {
        specG2->setPixmap(QPixmap(iconaG2));
        specG2->setEnabled(true);
    }




}

void Klient::ustawTure(QString)
{
	pushButtonG1C1->setEnabled(true);
	pushButtonG1C2->setEnabled(true);
	pushButtonG1C3->setEnabled(true);
    pushButtonG1C4->setEnabled(true);
    pushButtonG1C5->setEnabled(true);
    pushButtonG1C6->setEnabled(true);
    pushButtonG1C7->setEnabled(true);
    pushButtonG1C8->setEnabled(true);
    pushButtonG1C9->setEnabled(true);
    pushButtonG1C10->setEnabled(true);
    pushButtonPasG1->setEnabled(true);

}

void Klient::ustawLiczbeKartG2(QString c)
{
    lineEditCardsG2->setText(c);

}

void Klient::ustawLiczbeKartG1(QString c)
{
    lineEditCardsG1->setText(c);

}



void Klient::ustawKarty(QString c)
{


    if (c[0] == QChar('0')) {
        QString icona10 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C1->setIcon(QIcon(icona10));
    } else if (c[0] == QChar('1')) {
        QString icona11 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C2->setIcon(QIcon(icona11));
    } else if (c[0] == QChar('2')) {
        QString icona12 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C3->setIcon(QIcon(icona12));
    } else if (c[0] == QChar('3')) {
        QString icona13 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C4->setIcon(QIcon(icona13));
    } else if (c[0] == QChar('4')) {
        QString icona14 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C5->setIcon(QIcon(icona14));
    } else if (c[0] == QChar('5')) {
        QString icona15 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C6->setIcon(QIcon(icona15));
    } else if (c[0] == QChar('6')) {
        QString icona16 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C7->setIcon(QIcon(icona16));
    } else if (c[0] == QChar('7')) {
        QString icona17 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C8->setIcon(QIcon(icona17));
    } else if (c[0] == QChar('8')) {
        QString icona18 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C9->setIcon(QIcon(icona18));
    } else if (c[0] == QChar('9')) {
        QString icona19 = ":talie/" + rodzajTalii + "/" + c.mid(1) + ".png";
        pushButtonG1C10->setIcon(QIcon(icona19));
    }
}

void Klient::ustawNickSerwera(QString c)
{
    QString rT = c.mid(0,4);

    rodzajTaliiG2 = rT;
    QString nickServer = c.mid(4);
    groupBoxG2->setTitle(nickServer);
    setWindowTitle("Gwint - " + nick + " vs " + nickServer);
}



void Klient::niewidoczneG1()
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

void Klient::klikKarta(QString c)
{

QString tmp2 = c.mid(0,1);
QString numer;
numer.setNum(c.mid(1).toInt());

QString pixmap = ":talie2/" + rodzajTalii + "/" + numer + ".png";
QString null = ":ikony/null.png";


    if (tmp2 == "k")
    {
    if (kata1G1->isEnabled() == false) {
    kata1G1->setPixmap(pixmap);
    kata1G1->setEnabled("TRUE");
     wyslijWiadomosc("010|");
    }
    else if (kata2G1->isEnabled() == false) {
        kata2G1->setPixmap(pixmap);
        kata2G1->setEnabled(true);
         wyslijWiadomosc("011|");
    }
    else if (kata3G1->isEnabled() == false) {
        kata3G1->setPixmap(pixmap);
        kata3G1->setEnabled(true);
         wyslijWiadomosc("012|");
    }
    else if (kata4G1->isEnabled() == false) {
        kata4G1->setPixmap(pixmap);
        kata4G1->setEnabled(true);
         wyslijWiadomosc("013|");
    }
    else if (kata5G1->isEnabled() == false) {
        kata5G1->setPixmap(pixmap);
        kata5G1->setEnabled(true);
         wyslijWiadomosc("014|");
    }
    else if (kata6G1->isEnabled() == false) {
        kata6G1->setPixmap(pixmap);
        kata6G1->setEnabled(true);
        wyslijWiadomosc("015|");
    }
    else if (kata7G1->isEnabled() == false) {
        kata7G1->setPixmap(pixmap);
        kata7G1->setEnabled(true);
        wyslijWiadomosc("016|");
    }
    else {
        kata8G1->setPixmap(pixmap);
        kata8G1->setEnabled(true);
         wyslijWiadomosc("017|");
    }
}
    else if (tmp2 == "l")
    {
        if (luk1G1->isEnabled() == false) {
        luk1G1->setPixmap(pixmap);
        luk1G1->setEnabled(true);
         wyslijWiadomosc("010|");
        }
        else if (luk1G1->isEnabled() == false) {
            luk2G1->setPixmap(pixmap);
            luk2G1->setEnabled(true);
             wyslijWiadomosc("011|");
        }
        else if (luk3G1->isEnabled() == false) {
            luk3G1->setPixmap(pixmap);
            luk3G1->setEnabled(true);
             wyslijWiadomosc("012|");
        }
        else if (luk4G1->isEnabled() == false) {
            luk4G1->setPixmap(pixmap);
            luk4G1->setEnabled(true);
             wyslijWiadomosc("013|");
        }
        else if (luk5G1->isEnabled() == false) {
            luk5G1->setPixmap(pixmap);
            luk5G1->setEnabled(true);
             wyslijWiadomosc("014|");
        }
        else if (luk6G1->isEnabled() == false) {
            luk6G1->setPixmap(pixmap);
            luk6G1->setEnabled(true);
            wyslijWiadomosc("015|");
        }
        else if (luk7G1->isEnabled() == false) {
            luk7G1->setPixmap(pixmap);
            luk7G1->setEnabled(true);
            wyslijWiadomosc("016|");
        }
        else {
            luk8G1->setPixmap(pixmap);
            luk8G1->setEnabled(true);
             wyslijWiadomosc("017|");
        }
    }
    else if (tmp2 == "m" || tmp2 == "h")
    {
        if (miecz1G1->pixmap() == 0) {
        miecz1G1->setPixmap(pixmap);
         wyslijWiadomosc("010|");
        }
        else if (miecz2G1->pixmap() == 0) {
            miecz2G1->setPixmap(pixmap);
             wyslijWiadomosc("011|");
        }
        else if (miecz3G1->isEnabled() == false) {
            miecz3G1->setPixmap(pixmap);
            miecz3G1->setEnabled(true);
             wyslijWiadomosc("012|");
        }
        else if (miecz4G1->isEnabled() == false) {
            miecz4G1->setPixmap(pixmap);
            miecz4G1->setEnabled(true);
             wyslijWiadomosc("013|");
        }
        else if (miecz5G1->isEnabled() == false) {
            miecz5G1->setPixmap(pixmap);
            miecz5G1->setEnabled(true);
             wyslijWiadomosc("014|");
        }
        else if (miecz6G1->isEnabled() == false) {
            miecz6G1->setPixmap(pixmap);
            miecz6G1->setEnabled(true);
            wyslijWiadomosc("015|");
        }
        else if (miecz7G1->isEnabled() == false) {
            miecz7G1->setPixmap(pixmap);
            miecz7G1->setEnabled(true);
            wyslijWiadomosc("016|");
        }
        else {
            miecz8G1->setPixmap(pixmap);
            miecz8G1->setEnabled(true);
             wyslijWiadomosc("017|");
        }
    }
    else
    {
        specG1->setPixmap(pixmap);
        specG1->setEnabled(true);
        wyslijWiadomosc("018|");
    }
}

void Klient::klikKarta1()
{

    wyslijWiadomosc("060|");
    niewidoczneG1();


    pushButtonG1C1->setHidden(true);

}

void Klient::klikKarta2()
{
    wyslijWiadomosc("061|");
    niewidoczneG1();
    pushButtonG1C2->setHidden(true);

}

void Klient::klikKarta3()
{
    wyslijWiadomosc("062|");
    niewidoczneG1();
    pushButtonG1C3->setHidden(true);

}

void Klient::klikKarta4()
{
    wyslijWiadomosc("063|");
    niewidoczneG1();
    pushButtonG1C4->setHidden(true);

}

void Klient::klikKarta5()
{
    wyslijWiadomosc("064|");
     niewidoczneG1();
    pushButtonG1C5->setHidden(true);


}

void Klient::klikKarta6()
{
    wyslijWiadomosc("065|");
    niewidoczneG1();
    pushButtonG1C6->setHidden(true);

}

void Klient::klikKarta7()
{
    wyslijWiadomosc("066|");
    niewidoczneG1();
    pushButtonG1C7->setHidden(true);

}

void Klient::klikKarta8()
{
    wyslijWiadomosc("067|");
    niewidoczneG1();
    pushButtonG1C8->setHidden(true);

}

void Klient::klikKarta9()
{
    wyslijWiadomosc("068|");
    niewidoczneG1();
    pushButtonG1C9->setHidden(true);

}

void Klient::klikKarta10()
{
    wyslijWiadomosc("069|");
    niewidoczneG1();
    pushButtonG1C10->setHidden(true);

}



void Klient::wydajWerdykt()
{
    if(rywalPas == true && Pas == true)
    {
    int pkt1 = lineEditPktG1->text().toInt();
    int pkt2 = lineEditPktG2->text().toInt();
    int rnd1 = lineEditRundyG1->text().toInt();
    int rnd2 = lineEditRundyG2->text().toInt();
    QString r1, r2;

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

    wyslijWiadomosc("04" +r1+r2 +"|");


        if(rnd1==2 || rnd2==2)
        {
            if(rnd1==2)
                werdykt = Koniec::Zwyciestwo;
            else
                werdykt = Koniec::Porazka;


            Koniec *koniec = new Koniec(werdykt, rnd1, rnd2, nick, groupBoxG2->title());
            koniec->exec();


            wrocDoMenu();
        }
}
}

void Klient::inicjujKolejnaPartie()
{
    Pas = false;
    rywalPas = false;
    pushButtonPasG2->setMinimumWidth(70);
    pushButtonPasG2->setMaximumWidth(70);
    pushButtonPasG2->setText("Pas");
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    pushButtonPasG1->setEnabled(true);


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

    QPixmap pm4(50,80);
    pm4.fill(Qt::transparent); //


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

void Klient::klikPas()
{
    Pas = true;

    if(rywalPas == true)
    wydajWerdykt();
    else
    {
            wyslijWiadomosc("05SPASOWAL|");
            niewidoczneG1();
    }
}

void Klient::ustawLiczbeRund(QString c)
{
    int werdykt;


    lineEditRundyG1->setText(c.mid(0,1));
    lineEditRundyG2->setText(c.mid(1,1));

    int rnd1 = c.mid(0,1).toInt();
    int rnd2 = c.mid (1,1).toInt();

    if (rnd1 == 2 || rnd2 == 2)
    {
        if(rnd2==2)
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

void Klient::przeciwnikPas(QString c)
{
    rywalPas = true;
    if(Pas == true)
    wydajWerdykt();
    else
    {
    pushButtonPasG2->setMinimumWidth(70);
    pushButtonPasG2->setMaximumWidth(70);
    pushButtonPasG2->setText(c);
}
    }


void Klient::closeEvent(QCloseEvent *event)
{
	event->ignore();
    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy chcesz opuscic gre?"), QMessageBox::No | QMessageBox::Yes);
    if (odp == QMessageBox::Yes) {
        wyslijWiadomosc("02|");
        wrocDoMenu();
	}
}

