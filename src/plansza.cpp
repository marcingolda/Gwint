//#include "plansza.h"
//#include <ctime>

//Plansza::Plansza(QString _nick, QWidget *parent) :
//	QMainWindow(parent)
//{
//	setupUi(this);
//	nick = _nick;


//	th = new Thread();

//    connect(pushButtonG1C1, SIGNAL(clicked()), this, SLOT(klikKarta1()));
//    connect(pushButtonG1C2, SIGNAL(clicked()), this, SLOT(klikKarta2()));
//    connect(pushButtonG1C3, SIGNAL(clicked()), this, SLOT(klikKarta3()));
//    connect(pushButtonG1C4, SIGNAL(clicked()), this, SLOT(klikKarta4()));
//    connect(pushButtonG1C5, SIGNAL(clicked()), this, SLOT(klikKarta5()));
//    connect(pushButtonG1C6, SIGNAL(clicked()), this, SLOT(klikKarta6()));
//    connect(pushButtonG1C7, SIGNAL(clicked()), this, SLOT(klikKarta7()));
//    connect(pushButtonG1C8, SIGNAL(clicked()), this, SLOT(klikKarta8()));
//    connect(pushButtonG1C9, SIGNAL(clicked()), this, SLOT(klikKarta9()));
//    connect(pushButtonG1C10, SIGNAL(clicked()), this, SLOT(klikKarta10()));
//    connect(actionEsci, SIGNAL(triggered()), this, SLOT(wyjdzZgry()));
//    connect(actionAbout, SIGNAL(triggered()), this, SLOT(oGrze()));
//    connect(th, SIGNAL(sygnalG1()), this, SLOT(odbierzSygnalG1()), Qt::QueuedConnection);
//    connect(th, SIGNAL(sygnalG2()), this, SLOT(odbierzSygnalG2()), Qt::QueuedConnection);

//	QDesktopWidget *widget = QApplication::desktop();
//	QRect dim = widget->screenGeometry();
//	setGeometry((dim.width()-width())/2, (dim.height()-height())/2, width(), height());
//    setWindowTitle("Gwint - " + nick + " vs Computer");
//	groupBoxG1->setTitle(nick);
//	labelG1->setPixmap(QPixmap(""));
//	labelG2->setPixmap(QPixmap(""));


//	QString home = QDir::homePath();
//    QFile file(home + "/.gwint/pr");
//	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        th->setSleepMs(500);
//	} else {
//		QTextStream in(&file);
//		int val = in.readLine().toInt();
//		th->setSleepMs(val);
//	}


//    losujTure = new Random(time(0));
//    losujKarte = new Random(time(0));

//    inicjujPartie();
//}



//void Plansza::inicjujPartie()
//{
//    talia = new Talia();
//    tura = 0;
//	pos1 = -1;
//	pos2 = -1;

//    g1 = new Gracz(talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte());
//    g2 = new Gracz(talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte(), talia->dajKarte(), talia->dajKarte(),talia->dajKarte());


//    ustawIkony();
//    ustawLiczbeKart();

//    tura = ktoZaczyna();
//    ustawTure(tura);
//}


//void Plansza::ustawLiczbeKart()
//{
//	QString tmp;
//    tmp.setNum(talia->getMax()+1);
//    lineEditCardsG2->setText(tmp);

//}

//int Plansza::ktoZaczyna()
//{
//    int r = static_cast<int>(losujTure->rand()*(2));

//	if (r > 0.5)
//		return 2;
//	else
//		return 1;
//}

//void Plansza::ustawTure(int giocatore)
//{
//	int g = giocatore;
//	if (g == 1) {
//        if (g1->getKarta(0) != NULL)
//			pushButtonG1C1->setEnabled(true);
//        if (g1->getKarta(1) != NULL)
//			pushButtonG1C2->setEnabled(true);
//        if (g1->getKarta(2) != NULL)
//			pushButtonG1C3->setEnabled(true);
//        if (g1->getKarta(3) != NULL)
//            pushButtonG1C4->setEnabled(true);
//        if (g1->getKarta(4) != NULL)
//            pushButtonG1C5->setEnabled(true);
//        if (g1->getKarta(5) != NULL)
//            pushButtonG1C6->setEnabled(true);
//        if (g1->getKarta(6) != NULL)
//            pushButtonG1C7->setEnabled(true);
//        if (g1->getKarta(7) != NULL)
//            pushButtonG1C8->setEnabled(true);
//        if (g1->getKarta(8) != NULL)
//            pushButtonG1C9->setEnabled(true);
//        if (g1->getKarta(9) != NULL)
//            pushButtonG1C10->setEnabled(true);
//	} else {
//        if (g1->getKarta(0) != NULL)
//			pushButtonG1C1->setEnabled(false);
//        if (g1->getKarta(1) != NULL)
//			pushButtonG1C2->setEnabled(false);
//        if (g1->getKarta(2) != NULL)
//			pushButtonG1C3->setEnabled(false);
//        if (g1->getKarta(3) != NULL)
//            pushButtonG1C4->setEnabled(false);
//        if (g1->getKarta(4) != NULL)
//            pushButtonG1C5->setEnabled(false);
//        if (g1->getKarta(5) != NULL)
//            pushButtonG1C6->setEnabled(false);
//        if (g1->getKarta(6) != NULL)
//            pushButtonG1C7->setEnabled(false);
//        if (g1->getKarta(7) != NULL)
//            pushButtonG1C8->setEnabled(false);
//        if (g1->getKarta(8) != NULL)
//            pushButtonG1C9->setEnabled(false);
//        if (g1->getKarta(9) != NULL)
//            pushButtonG1C10->setEnabled(false);


//	}
//}

//void Plansza::kontroluj(int i)
//{
//    if (i == 2) {
//        g2->zwiekszPunkty(g2->getRzucona()->getPunteggio());
//        QString punktyG2;
//        punktyG2.setNum(g2->getPunkty());
//        lineEditPktG2->setText(punktyG2);

//        if (g1->getRzucona() == NULL) {
//            ustawTure(1);
//        } else {
//            aktywnyGracz(1);
//        }
//    } else {
//        g1->zwiekszPunkty(g1->getRzucona()->getPunteggio());
//        QString punktyG1;
//        punktyG1.setNum(g1->getPunkty());
//        lineEditPktG1->setText(punktyG1);
//        if (g2->getRzucona() == NULL) {
//            ustawTure(2);
//        } else {
//            aktywnyGracz(2);
//        }
//    }
//}


//void Plansza::aktywnyGracz(int g)
//{
//	if (g == 1) {
//		th->setGiocatore(1);
//		th->start();
//	} else {
//		th->setGiocatore(2);
//		th->start();
//	}
//}

//void Plansza::ustawIkony()
//{
//	QString tmp;

//    tmp.setNum(talia->getMax()+1);
//    if (talia->getMax() == 0)
//        labelKupkaG2->setPixmap(QPixmap(":/icons/null2.png"));
//	else
//        labelKupkaG2->setPixmap(QPixmap(":mazzi/" + rodzajTalii + "/mazzo.png"));

//    if (g1->getKarta(0) != NULL) {
//        tmp.setNum(g1->getKarta(0)->getNumero());
//        QString icona10 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(0)->getSeme() + ".png";
//		pushButtonG1C1->setIcon(QIcon(icona10));
//	} else {
//		pushButtonG1C1->setIcon(QIcon(":icons/null.png"));
//		pushButtonG1C1->setEnabled(false);
//	}

//    if (g1->getKarta(1) != NULL) {
//        tmp.setNum(g1->getKarta(1)->getNumero());
//        QString icona11 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(1)->getSeme() + ".png";
//		pushButtonG1C2->setIcon(QIcon(icona11));
//	} else {
//		pushButtonG1C2->setIcon(QIcon(":icons/null.png"));
//		pushButtonG1C2->setEnabled(false);
//	}

//    if (g1->getKarta(2) != NULL) {
//        tmp.setNum(g1->getKarta(2)->getNumero());
//        QString icona12 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(2)->getSeme() + ".png";
//		pushButtonG1C3->setIcon(QIcon(icona12));
//	} else {
//		pushButtonG1C3->setIcon(QIcon(":icons/null.png"));
//		pushButtonG1C3->setEnabled(false);
//	}
//    if (g1->getKarta(3) != NULL) {
//        tmp.setNum(g1->getKarta(3)->getNumero());
//        QString icona13 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(3)->getSeme() + ".png";
//        pushButtonG1C4->setIcon(QIcon(icona13));
//    } else {
//        pushButtonG1C4->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C4->setEnabled(false);
//    }

//    if (g1->getKarta(4) != NULL) {
//        tmp.setNum(g1->getKarta(4)->getNumero());
//        QString icona14 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(4)->getSeme() + ".png";
//        pushButtonG1C5->setIcon(QIcon(icona14));
//    } else {
//        pushButtonG1C5->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C5->setEnabled(false);
//    }

//    if (g1->getKarta(5) != NULL) {
//        tmp.setNum(g1->getKarta(5)->getNumero());
//        QString icona15 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(5)->getSeme() + ".png";
//        pushButtonG1C6->setIcon(QIcon(icona15));
//    } else {
//        pushButtonG1C6->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C6->setEnabled(false);
//    }
//    if (g1->getKarta(6) != NULL) {
//        tmp.setNum(g1->getKarta(6)->getNumero());
//        QString icona16 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(6)->getSeme() + ".png";
//        pushButtonG1C7->setIcon(QIcon(icona16));
//    } else {
//        pushButtonG1C7->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C7->setEnabled(false);
//    }

//    if (g1->getKarta(8) != NULL) {
//        tmp.setNum(g1->getKarta(8)->getNumero());
//        QString icona18 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(8)->getSeme() + ".png";
//        pushButtonG1C9->setIcon(QIcon(icona18));
//    } else {
//        pushButtonG1C9->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C9->setEnabled(false);
//    }

//    if (g1->getKarta(7) != NULL) {
//        tmp.setNum(g1->getKarta(7)->getNumero());
//        QString icona17 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(7)->getSeme() + ".png";
//        pushButtonG1C8->setIcon(QIcon(icona17));
//    } else {
//        pushButtonG1C8->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C8->setEnabled(false);
//    }if (g1->getKarta(9) != NULL) {
//        tmp.setNum(g1->getKarta(9)->getNumero());
//        QString icona19 = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getKarta(9)->getSeme() + ".png";
//        pushButtonG1C10->setIcon(QIcon(icona19));
//    } else {
//        pushButtonG1C10->setIcon(QIcon(":icons/null.png"));
//        pushButtonG1C10->setEnabled(false);
//    }


//    if (g2->getKarta(0) != NULL) {
//        pushButtonG2C1->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//	} else
//		pushButtonG2C1->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(1) != NULL) {
//        pushButtonG2C2->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//	} else
//		pushButtonG2C2->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(2) != NULL) {
//        pushButtonG2C3->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//	} else
//        pushButtonG2C3->setIcon(QIcon(":icons/null.png"));
//    if (g2->getKarta(3) != NULL) {
//        pushButtonG2C4->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C4->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(4) != NULL) {
//        pushButtonG2C5->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C5->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(5) != NULL) {
//        pushButtonG2C6->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C6->setIcon(QIcon(":icons/null.png"));
//    if (g2->getKarta(6) != NULL) {
//        pushButtonG2C7->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C7->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(7) != NULL) {
//        pushButtonG2C8->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C8->setIcon(QIcon(":icons/null.png"));

//    if (g2->getKarta(8) != NULL) {
//        pushButtonG2C9->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C9->setIcon(QIcon(":icons/null.png"));
//    if (g2->getKarta(9) != NULL) {
//        pushButtonG2C10->setIcon(QIcon(":mazzi/" + rodzajTalii + "/dietro.png"));
//    } else
//        pushButtonG2C10->setIcon(QIcon(":icons/null.png"));


//}


//void Plansza::wrocDoMenu()
//{
//	setVisible(false);
//    Start *a = new Start();
//	a->show();
//	a->setVisible(true);
//	destroy();
//}


////pamietaj grane karty
//void Plansza::pamietajGraneKarty()
//{
//    zagrane.append(g1->getRzucona());
//    zagrane.append(g2->getRzucona());

//}

//// eventi
//void Plansza::klikKarta1()
//{
//	g1->rzuconaKarta(0);
//	pushButtonG1C1->setEnabled(false);
//	pushButtonG1C2->setEnabled(false);
//	pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);


//	pushButtonG1C1->setIcon(QIcon(":icons/null.png"));

//	QString tmp;
//	tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//	pos1 = 0;
//    kontroluj(1);
//}

//void Plansza::klikKarta2()
//{
//	g1->rzuconaKarta(1);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//	pushButtonG1C2->setIcon(QIcon(":icons/null.png"));

//	QString tmp;
//	tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//	pos1 = 1;
//    kontroluj(1);
//}

//void Plansza::klikKarta3()
//{
//	g1->rzuconaKarta(2);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//	pushButtonG1C3->setIcon(QIcon(":icons/null.png"));

//	QString tmp;
//	tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//	pos1 = 2;
//    kontroluj(1);
//}

//void Plansza::klikKarta4()
//{
//    g1->rzuconaKarta(3);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C4->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 3;
//    kontroluj(1);
//}

//void Plansza::klikKarta5()
//{
//    g1->rzuconaKarta(4);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C5->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 4;
//    kontroluj(1);
//}

//void Plansza::klikKarta6()
//{
//    g1->rzuconaKarta(5);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C6->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 5;
//    kontroluj(1);
//}

//void Plansza::klikKarta7()
//{
//    g1->rzuconaKarta(6);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C7->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 6;
//    kontroluj(1);
//}

//void Plansza::klikKarta8()
//{
//    g1->rzuconaKarta(7);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C8->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 7;
//    kontroluj(1);
//}

//void Plansza::klikKarta9()
//{
//    g1->rzuconaKarta(8);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C9->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 8;
//    kontroluj(1);
//}

//void Plansza::klikKarta10()
//{
//    g1->rzuconaKarta(9);
//    pushButtonG1C1->setEnabled(false);
//    pushButtonG1C2->setEnabled(false);
//    pushButtonG1C3->setEnabled(false);
//    pushButtonG1C4->setEnabled(false);
//    pushButtonG1C5->setEnabled(false);
//    pushButtonG1C6->setEnabled(false);
//    pushButtonG1C7->setEnabled(false);
//    pushButtonG1C8->setEnabled(false);
//    pushButtonG1C9->setEnabled(false);
//    pushButtonG1C10->setEnabled(false);

//    pushButtonG1C10->setIcon(QIcon(":icons/null.png"));

//    QString tmp;
//    tmp.setNum(g1->getRzucona()->getNumero());
//    QString carta = ":mazzi/" + rodzajTalii + "/" + tmp + g1->getRzucona()->getSeme() + ".png";
//    if (labelG1->isEnabled() == false) {
//    labelG1->setPixmap(carta);
//    labelG1->setEnabled(true);
//    }
//    else if (label1G1->isEnabled() == false) {
//        label1G1->setPixmap(carta);
//        label1G1->setEnabled(true);
//    }
//    else if (label2G1->isEnabled() == false) {
//        label2G1->setPixmap(carta);
//        label2G1->setEnabled(true);
//    }
//    else if (label3G1->isEnabled() == false) {
//        label3G1->setPixmap(carta);
//        label3G1->setEnabled(true);
//    }
//    else if (label4G1->isEnabled() == false) {
//        label4G1->setPixmap(carta);
//        label4G1->setEnabled(true);
//    }
//    else if (label5G1->isEnabled() == false) {
//        label5G1->setPixmap(carta);
//        label5G1->setEnabled(true);
//    }
//    else {
//        label6G1->setPixmap(carta);
//        label6G1->setEnabled(true);
//    }

//    pos1 = 9;
//    kontroluj(1);
//}


//void Plansza::odbierzSygnalG1()
//{
//    pamietajGraneKarty();
//	g1->setNullRzucona();
//    g2->setNullRzucona();


//    tura = 1;


//        g1->dodajKarte(pos1, talia->dajKarte());
//        g2->dodajKarte(pos2, talia->dajKarte());
//        ustawLiczbeKart();


//    ustawIkony();
//    ustawTure(1);
//}

//void Plansza::odbierzSygnalG2()
//{

//    pamietajGraneKarty();
//    g1->setNullRzucona();
//	g2->setNullRzucona();


//    tura = 2;

//        g2->dodajKarte(pos2, talia->dajKarte());
//        g1->dodajKarte(pos1, talia->dajKarte());
//        ustawLiczbeKart();


//    ustawIkony();
//    ustawTure(2);
//}

//void Plansza::wyjdzZgry()
//{
//    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy na pewno chcesz wyjsc?"), QMessageBox::No | QMessageBox::Yes);
//    if (odp == QMessageBox::Yes) {
//        wrocDoMenu();
//	}
//}

//void Plansza::closeEvent(QCloseEvent *event)
//{
//	event->ignore();
//    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy na pewno chcesz wyjsc?"), QMessageBox::No | QMessageBox::Yes);
//    if (odp == QMessageBox::Yes) {
//        wrocDoMenu();
//	}
//}

//void Plansza::oGrze()
//{
//    QString tresc = tr("Gwint - Arkadiusz Junik");
//    QMessageBox::information(this, tr("O grze"), tresc);
//}


//void Plansza::aktualizujWatek(int ms)
//{
//	th->setSleepMs(ms);
//}

