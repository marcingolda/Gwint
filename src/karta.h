#ifndef KARTA_H_
#define KARTA_H_

#include <QString>

class Karta
{
private:
	QString rodzaj;
	int numer;
    QString moc;
    int bohater;
	int sila;

public:
    Karta(QString, int, int, QString, int);

	QString getRodzaj();
	int getNumer();
	int getSila();
    QString getMoc();
    int getBohater();

};

#endif
