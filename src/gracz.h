#ifndef GRACZ_H_
#define GRACZ_H_

#include "karta.h"


class Gracz
{
private:
	Karta** karta;
	Karta *rzucona;
	int punkty;

public:
    Gracz(Karta*, Karta*, Karta*,Karta*, Karta*, Karta*,Karta*, Karta*, Karta*, Karta*);
	~Gracz();


	Karta* getKarta(int);
	void rzuconaKarta(int);
    void setNullKarta(int);
	void dodajKarte(int, Karta*);
	Karta* getRzucona();
	void setNullRzucona();
	int getPunkty();
	void zwiekszPunkty(int);
};

#endif
