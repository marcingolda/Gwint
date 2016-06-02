#ifndef CONFIGURA_H_
#define CONFIGURA_H_

#include <QtGui>

#include "ui_configura.h"

class Konfiguracja : public QWidget, public Ui::Configura
{
Q_OBJECT

public:
	Konfiguracja(QWidget *parent = 0);

signals:
	void segnaleAggiornaThread(int);

public slots:
	void aggiornaText(int);
	void applica();
	void annulla();
};

#endif
