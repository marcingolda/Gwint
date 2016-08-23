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
    int orginalnaSila;

public:
    Karta(QString, int, int, QString);
    Karta(int);

	QString getRodzaj();
	int getNumer();
	int getSila();
    void setSila(int);
    int getOrginalnaSila();
    void setOrginalnaSila(int);
    QString getMoc();

};

#endif
