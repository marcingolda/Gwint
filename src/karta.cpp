#include "karta.h"

Karta::Karta(QString r, int n, int s, QString m, int b)
{
    rodzaj = r;
    numer = n;
    sila = s;
    moc = m;
    bohater = b;
}

QString Karta::getRodzaj()
{
    return rodzaj;
}

int Karta::getNumer()
{
    return numer;
}

int Karta::getSila()
{
    return sila;
}

QString Karta::getMoc()
{
    return moc;
}

int Karta::getBohater()
{
    return bohater;
}
