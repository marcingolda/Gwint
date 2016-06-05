#include "koniec.h"

Koniec::Koniec(int c, int p1, int p2, QString g1, QString g2, QWidget *parent) :
	QDialog(parent)
{
	setupUi(this);

	connect(pushButtonOk, SIGNAL(clicked()), this, SLOT(ok()));

    if (c == Zwyciestwo) {
        labelKoniec->setPixmap(QString(":/ikony/wygrana.png"));
        labelWiadomosc->setText(tr("Gratulacje, wygrales!"));
    } else if (c == Porazka) {
        labelKoniec->setPixmap(QString(":/ikony/przegrana.png"));
        labelWiadomosc->setText(tr("Niestety, przegrales."));
    }

	labelG1->setText(g1);
	QString tmp1;
	tmp1.setNum(p1);
	lineEditG1->setText(tmp1);
	
	labelG2->setText(g2);
	QString tmp2;
	tmp2.setNum(p2);
	lineEditG2->setText(tmp2);
}

void Koniec::ok()
{
	setVisible(false);
	destroy();
}
