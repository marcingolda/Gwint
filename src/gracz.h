#ifndef GRACZ_H_
#define GRACZ_H_

#include "karta.h"

class Gracz
{
private:
	Karta** karta;
	Karta *rzucona;
    int punkty, Mi,Ki,Li;
    int liczbaKart;




public:
    Gracz(Karta*, Karta*, Karta*,Karta*, Karta*, Karta*,Karta*, Karta*, Karta*, Karta*);
	~Gracz();


    int licznikZmienionychMiecz;
    int licznikZmienionychLuk;
    int licznikZmienionychKata;
    Karta** rzuconeKartyMiecz;
    Karta** rzuconeKartyLuk;
    Karta** rzuconeKartyKata;
	Karta* getKarta(int);
    void rzuconaKarta(int);
    void rodzajRzuconejKarty(QString);
    void setNullKarta(int);
	void dodajKarte(int, Karta*);
	Karta* getRzucona();
	void setNullRzucona();
    void setZmienioneMiecz(int);
    void setZmienioneLuk(int);
    void setZmienioneKata(int);
    void wyczyscKarty();
	int getPunkty();
    int getLiczbaKart();
    int getZmienioneMiecz();
    int getZmienioneLuk();
    int getZmienioneKata();
	void zwiekszPunkty(int);
    void zmniejszPunkty(int);

};

#endif
