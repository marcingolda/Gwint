#include "karta.h"

Karta::Karta(QString r, int n, int s, QString m)
{
    rodzaj = r;
    numer = n;
    sila = s;
    moc = m;
}

Karta::Karta(int s)
{
    sila = s;
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

void Karta::setSila(int s) {
    sila = s;
}

QString Karta::getMoc()
{
    return moc;
}
