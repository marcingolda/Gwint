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
    metoda[4] = &Klient::ustawKarteSerwera;
    metoda[5] = &Klient::aktualizujPunkty;
    metoda[6] = &Klient::aktualizujPunktySerwera;
    metoda[7] = &Klient::serwerOdlaczony;
    metoda[8] = &Klient::ustawLiczbeKartG1;
    metoda[9] = &Klient::ustawLiczbeRund;
    metoda[10] = &Klient::przeciwnikPas;

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



void Klient::ustawKarteSerwera(QString c)
{

    QString poz = c.mid(0, 1);
    QString pos = c.mid(1, 1);
    QString numer = c.mid(2);
    QString iconaG2 = ":talie/" + rodzajTaliiG2 + "/" + numer + ".png";


    if (pos == "0")
        pushButtonG2C1->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "1")
        pushButtonG2C2->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "2")
        pushButtonG2C3->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "3")
        pushButtonG2C4->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "4")
        pushButtonG2C5->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "5")
        pushButtonG2C6->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "6")
        pushButtonG2C7->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "7")
        pushButtonG2C8->setIcon(QIcon(":/ikony/null.png"));
    else if (pos == "8")
        pushButtonG2C9->setIcon(QIcon(":/ikony/null.png"));
	else
        pushButtonG2C10->setIcon(QIcon(":/ikony/null.png"));

    posServer = pos.toInt();

    if (poz == "0") {
        labelG2->setEnabled(true);
        labelG2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "1") {
        label1G2->setEnabled(true);
        label1G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "2") {
        label2G2->setEnabled(true);
        label2G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "3") {
        label3G2->setEnabled(true);
        label3G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "4") {
        label4G2->setEnabled(true);
        label4G2->setPixmap(QPixmap(iconaG2));
    }
    else if (poz == "5") {
        label5G2->setEnabled(true);
        label5G2->setPixmap(QPixmap(iconaG2));
    }
    else{
        label6G2->setEnabled(true);
        label6G2->setPixmap(QPixmap(iconaG2));
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

//	if (posServer == 0) {
//        pushButtonG2C1->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//	} else if (posServer == 1) {
//        pushButtonG2C2->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//	} else if (posServer == 2) {
//        pushButtonG2C3->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 3) {
//        pushButtonG2C4->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 4) {
//        pushButtonG2C5->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 5) {
//        pushButtonG2C6->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 6) {
//        pushButtonG2C7->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    }else if (posServer == 7) {
//        pushButtonG2C8->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 8) {
//        pushButtonG2C9->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    } else if (posServer == 9) {
//        pushButtonG2C10->setIcon(QIcon(":talie/" + rodzajTaliiG2 + "/dietro.png"));
//    }
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

void Klient::klikKarta1()
{

    niewidoczneG1();

    QIcon icon = pushButtonG1C1->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0100|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0110|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0120|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0130|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0140|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0150|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0160|");
    }

    pushButtonG1C1->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta2()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C2->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0101|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0111|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0121|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0131|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0141|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0151|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0161|");
    }
    pushButtonG1C2->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta3()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C3->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0102|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0112|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0122|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0132|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0142|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0152|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0162|");
    }
    pushButtonG1C3->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta4()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C4->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0103|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0113|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0123|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0133|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0143|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0153|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0163|");
    }
    pushButtonG1C4->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta5()
{
     niewidoczneG1();

    QIcon icon = pushButtonG1C5->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0104|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0114|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0124|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0134|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0144|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0154|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0164|");
    }
    pushButtonG1C5->setIcon(QIcon(":/ikony/null.png"));


}

void Klient::klikKarta6()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C6->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0105|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0115|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0125|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0135|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0145|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0155|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0165|");
    }
    pushButtonG1C6->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta7()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C7->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0106|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0116|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0126|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0136|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0146|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0156|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0166|");
    }
    pushButtonG1C7->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta8()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C8->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0107|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0117|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0127|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0137|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0147|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0157|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0167|");
    }
    pushButtonG1C8->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta9()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C9->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0108|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0118|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0128|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0138|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0148|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0158|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0168|");
    }
    pushButtonG1C9->setIcon(QIcon(":/ikony/null.png"));

}

void Klient::klikKarta10()
{
    niewidoczneG1();

    QIcon icon = pushButtonG1C10->icon();
    QPixmap pixmap = icon.pixmap(75, 134);
    if (labelG1->isEnabled() == false) {
    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(true);
     wyslijWiadomosc("0109|");
    }
    else if (label1G1->isEnabled() == false) {
        label1G1->setPixmap(pixmap);
        label1G1->setEnabled(true);
         wyslijWiadomosc("0119|");
    }
    else if (label2G1->isEnabled() == false) {
        label2G1->setPixmap(pixmap);
        label2G1->setEnabled(true);
         wyslijWiadomosc("0129|");
    }
    else if (label3G1->isEnabled() == false) {
        label3G1->setPixmap(pixmap);
        label3G1->setEnabled(true);
         wyslijWiadomosc("0139|");
    }
    else if (label4G1->isEnabled() == false) {
        label4G1->setPixmap(pixmap);
        label4G1->setEnabled(true);
         wyslijWiadomosc("0149|");
    }
    else if (label5G1->isEnabled() == false) {
        label5G1->setPixmap(pixmap);
        label5G1->setEnabled(true);
        wyslijWiadomosc("0159|");
    }
    else {
        label6G1->setPixmap(pixmap);
        label6G1->setEnabled(true);
         wyslijWiadomosc("0169|");
    }
    pushButtonG1C10->setIcon(QIcon(":/ikony/null.png"));

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
        r2.setNum(rnd2);
        lineEditRundyG2->setText(r2);
        inicjujKolejnaPartie();
    }
    else if (pkt1 > pkt2)
    {
        rnd1++;
        r1.setNum(rnd1);
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

    wyslijWiadomosc("04" +r1+r2);


        if(rnd1==2 || rnd2==2)
        {
            if(rnd1==2)
                werdykt = Koniec::Zwyciestwo;
            else if (rnd2==2)
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
    pushButtonPasG2->setText("Pas");
    lineEditPktG1->setText("0");
    lineEditPktG2->setText("0");
    pushButtonPasG1->setEnabled(true);


    QString pixmap = ":ikony/null.png";

    labelG2->setPixmap(pixmap);
    labelG2->setEnabled(false);
    label1G2->setPixmap(pixmap);
    label1G2->setEnabled(false);
    label2G2->setPixmap(pixmap);
    label2G2->setEnabled(false);
    label3G2->setPixmap(pixmap);
    label3G2->setEnabled(false);
    label4G2->setPixmap(pixmap);
    label4G2->setEnabled(false);
    label5G2->setPixmap(pixmap);
    label5G2->setEnabled(false);
    label6G2->setPixmap(pixmap);
    label6G2->setEnabled(false);

    labelG1->setPixmap(pixmap);
    labelG1->setEnabled(false);
    label1G1->setPixmap(pixmap);
    label1G1->setEnabled(false);
    label2G1->setPixmap(pixmap);
    label2G1->setEnabled(false);
    label3G1->setPixmap(pixmap);
    label3G1->setEnabled(false);
    label4G1->setPixmap(pixmap);
    label4G1->setEnabled(false);
    label5G1->setPixmap(pixmap);
    label5G1->setEnabled(false);
    label6G1->setPixmap(pixmap);
    label6G1->setEnabled(false);

}

void Klient::klikPas()
{
    Pas = true;
    niewidoczneG1();
    pushButtonPasG1->setEnabled(false);
    wydajWerdykt();

    if (rywalPas == false)
            wyslijWiadomosc("05PAS");
}

void Klient::ustawLiczbeRund(QString c)
{
    int werdykt;


    lineEditRundyG1->setText(c.mid(0,1));
    lineEditRundyG2->setText(c.mid(0,1));

    int rnd1 = c.mid(0,1).toInt();
    int rnd2 = c.mid (1,1).toInt();

    if (rnd1 == 2 || rnd2 == 2)
    {
        if(rnd2==2)
            werdykt = Koniec::Porazka;
        else if (rnd1==2)
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
    niewidoczneG2();
    pushButtonPasG2->setText(c);
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

