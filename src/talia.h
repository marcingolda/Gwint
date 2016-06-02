#ifndef TALIA_H_
#define TALIA_H_

#include "karta.h"
#include "random.h"
#include "start.h"

extern QString rodzajTalii;

class Talia
{
private:
    Karta** kartaWtalii;
	int max;
    Random *losowaKarta;

public:
    Talia(QString);
    virtual ~Talia();


    void inicjalizuj(QString);
	void setMax(int);
	int getMax();
    QString jakaTalia;
    Karta* zwrocKarte(int);
	Karta* dajKarte();
};

#endif
