#ifndef KARTA_H_
#define KARTA_H_

#include <QString>

class Karta
{
private:
	QString rodzaj;
	int numer;
    QString moc;
	int sila;

public:
    Karta(QString, int, int, QString);
    Karta(int);

	QString getRodzaj();
	int getNumer();
	int getSila();
    void setSila(int);
    QString getMoc();

};

#endif
