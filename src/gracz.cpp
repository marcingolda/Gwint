#include "gracz.h"

Gracz::Gracz(Karta *c1, Karta *c2, Karta *c3, Karta *c4, Karta *c5, Karta *c6, Karta *c7, Karta *c8, Karta *c9, Karta *c10)
{
    liczbaKart = 10;
    rzuconeKartyMiecz = new Karta*[10];
    rzuconeKartyKata = new Karta*[10];
    rzuconeKartyLuk = new Karta*[10];
    karta = new Karta*[liczbaKart];
    karta[0] = c1;
    karta[1] = c2;
    karta[2] = c3;
    karta[3] = c4;
    karta[4] = c5;
    karta[5] = c6;
    karta[6] = c7;
    karta[7] = c8;
    karta[8] = c9;
    karta[9] = c10;
    punkty = 0;
    Ki = 0;
    Li = 0;
    Mi = 0;

    wyczyscKarty();

}


Gracz::~Gracz()
{
    delete[] karta;
}


Karta* Gracz::getKarta(int i)
{
    return karta[i];
}

void Gracz::wyczyscKarty()
{

    for(int i=0;i<getLiczbaKart();i++)
    {
        rzuconeKartyMiecz[i]=new Karta(0);
        rzuconeKartyKata[i]=new Karta(0);
        rzuconeKartyLuk[i]=new Karta(0);
    }
}

void Gracz::rzuconaKarta(int i)
{
    rzucona = karta[i];


}

void Gracz::rodzajRzuconejKarty(QString c)
{
    QString rodzaj = c;

    if(rodzaj == "m")
        rzuconeKartyMiecz[Mi++] = getRzucona();
    else if(rodzaj =="l")
        rzuconeKartyLuk[Li++] = getRzucona();
    else
        rzuconeKartyKata[Ki++] = getRzucona();
}

void Gracz::setNullKarta(int i)
{
    karta[i] = NULL;
}

void Gracz::dodajKarte(int pos, Karta *c)
{
    karta[pos] = c;
}

Karta* Gracz::getRzucona()
{
    return rzucona;
}


void Gracz::setNullRzucona()
{
    rzucona = NULL;
}

int Gracz::getPunkty()
{
    return punkty;
}

int Gracz::getLiczbaKart()
{
    return liczbaKart;
}

void Gracz::zwiekszPunkty(int p)
{
    punkty += p;
}

void Gracz::zmniejszPunkty(int p)
{
    punkty -=p;
}
