#include "start.h"
#include "plansza.h"
#include "klient.h"
#include "server.h"

QString rodzajTalii = "null";

Start::Start( QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);
    ustawienia();


    connect(pushButtonOk, SIGNAL(clicked()), this, SLOT(polacz()));
    connect(pushButtonEsci, SIGNAL(clicked()), this, SLOT(wyjdz()));
    connect(radioButtonServer, SIGNAL(clicked()), this, SLOT(widocznySerwer()));
    connect(radioButtonClient, SIGNAL(clicked()), this, SLOT(widocznyKlient()));

	pushButtonOk->setFocus();
}

void Start::polacz()
{
	QString ip;
	int port;
	QString nick = lineEditNick->displayText();


    if (comboBoxKarty->currentText() == "Elfy")
        rodzajTalii = "elfy";
    else if (comboBoxKarty->currentText() == "Krolestwo Polnocy")
        rodzajTalii = "kpln";
    else if (comboBoxKarty->currentText() == "Nilfgaard")
        rodzajTalii = "ngrd";
    else if (comboBoxKarty->currentText() == "Potwory")
        rodzajTalii = "ptwr";

	if (nick == "") {
        QMessageBox::warning(this, tr("Uwaga"), tr("Wpisz swoj nick"));
		return;
	}


		if (radioButtonClient->isChecked()) {
			// client
            port = spinBoxClientPort->value();
			ip = lineEditClientIp->displayText();

            Klient *client = new Klient(nick, ip, port);
			client->show();

		} else if (radioButtonServer->isChecked()) {
			// server
            port = spinBoxServerPort->value();

            Server *server = new Server(nick, port);
			server->show();
		} else {
            QString tresc = tr("Wybierz poprawną opcję");
            QMessageBox::critical(this, tr("Error"), tresc);
			return;
		}


    zapiszDane();

	this->setVisible(false);
	this->destroyed();
}

void Start::zapiszDane()
{
	QString home = QDir::homePath();
    QFile file(home + "/.gwint/config");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);

	out << lineEditNick->text() << endl;
    out << spinBoxServerPort->value() << endl;
	out << lineEditClientIp->text() << endl;
    out << spinBoxClientPort->value() << endl;
	out << height() << endl;
	out << width() << endl;
    out << comboBoxKarty->currentIndex() << endl;
}

void Start::ustawienia()
{
	QString home = QDir::homePath();
    QFile file(home + "/.gwint/config");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);

	lineEditNick->setText(in.readLine());
    spinBoxServerPort->setValue(in.readLine().toInt());
	lineEditClientIp->setText(in.readLine());
    spinBoxClientPort->setValue(in.readLine().toInt());
	int h = in.readLine().toInt();
	int w = in.readLine().toInt();
    comboBoxKarty->setCurrentIndex(in.readLine().toInt());

	if ((h == 0) && (w == 0))
		return;

	QDesktopWidget *widget = QApplication::desktop();
	QRect dim = widget->screenGeometry();
	setGeometry((dim.width() - w) / 2, (dim.height() - h) / 2, w, h);

}

void Start::wyjdz()
{
    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy na pewno chcesz wyjsc z gry?"), QMessageBox::No | QMessageBox::Yes);
    if (odp == QMessageBox::Yes)
		exit(1);
}


void Start::widocznySerwer()
{
    spinBoxClientPort->setEnabled(false);
	lineEditClientIp->setEnabled(false);
    spinBoxServerPort->setEnabled(true);

    labelClientPort->setEnabled(false);
	labelClientIp->setEnabled(false);
    labelServerPort->setEnabled(true);

	pushButtonOk->setEnabled(true);

    spinBoxServerPort->setFocus();
}

void Start::widocznyKlient()
{
    spinBoxClientPort->setEnabled(true);
	lineEditClientIp->setEnabled(true);
    spinBoxServerPort->setEnabled(false);

    labelClientPort->setEnabled(true);
	labelClientIp->setEnabled(true);
    labelServerPort->setEnabled(false);

	pushButtonOk->setEnabled(true);

    spinBoxClientPort->setFocus();
}

void Start::closeEvent(QCloseEvent *event)
{
	event->ignore();
    int odp = QMessageBox::question(this, tr("Uwaga"), tr("Czy na pewno chcesz wyjsc z gry?"), QMessageBox::No | QMessageBox::Yes);
    if (odp == QMessageBox::Yes) {
		exit(1);
	}
}

