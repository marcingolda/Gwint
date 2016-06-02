#include "konfiguracja.h"

Konfiguracja::Konfiguracja(QWidget *parent) :
	QWidget(parent)
{
	setupUi(this);

	QDesktopWidget *widget = QApplication::desktop();
	QRect dim = widget->screenGeometry();
	setGeometry((dim.width()-width())/2, (dim.height()-height())/2, width(), height());

	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(aggiornaText(int)));
	connect(pushButtonOk, SIGNAL(clicked()), this, SLOT(applica()));
	connect(pushButtonAnnulla, SIGNAL(clicked()), this, SLOT(annulla()));

	// leggo da file
	QString home = QDir::homePath();
	QFile file(home + "/.qbriscola/velocita");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	QTextStream in(&file);

	QString val = in.readLine();
	slider->setValue(val.toInt());
	lineEdit->setText(val);
}

void Konfiguracja::aggiornaText(int val)
{
	QString v;
	v.setNum(val);
	lineEdit->setText(v);
}

void Konfiguracja::applica()
{
	int ms = slider->value();
	emit segnaleAggiornaThread(ms);

	// scrivo su un file a parte
	QString home = QDir::homePath();
	QFile file(home + "/.qbriscola/velocita");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		return;

	QTextStream out(&file);

	out << ms << endl;

	setVisible(false);
}

void Konfiguracja::annulla()
{
	setVisible(false);
}

