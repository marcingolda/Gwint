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

public:
    Talia(QString);
    virtual ~Talia();


    void inicjalizuj(QString);
	void setMax(int);
	int getMax();
    Karta* zwrocKarte(int);
	Karta* dajKarte();
};

#endif
