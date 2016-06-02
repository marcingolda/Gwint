#include "gracz.h"

Gracz::Gracz(Karta *c1, Karta *c2, Karta *c3, Karta *c4, Karta *c5, Karta *c6, Karta *c7, Karta *c8, Karta *c9, Karta *c10)
{
    karta = new Karta*[10];
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
    rzucona = NULL;
}

Gracz::~Gracz()
{
    delete[] karta;
}


Karta* Gracz::getKarta(int i)
{
    return karta[i];
}

void Gracz::rzuconaKarta(int i)
{
    rzucona = karta[i];
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

void Gracz::zwiekszPunkty(int p)
{
    punkty += p;
}
