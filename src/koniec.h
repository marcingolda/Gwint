#ifndef H_KONIEC
#define H_KONIEC

#include <QtGui>

#include "ui_koniec.h"

class Koniec : public QDialog, private Ui::Koniec
{
	Q_OBJECT

public:
	Koniec(int, int, int, QString, QString, QWidget *parent = 0);

    enum Werdykt
	{
		Zwyciestwo,
        Porazka
	};

public slots:
	void ok();
};

#endif
