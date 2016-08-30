#include "karta.h"

Karta::Karta(QString r, int n, int s, QString m, int b)
{
    rodzaj = r;
    numer = n;
    sila = s;
    moc = m;
    bohater = b;
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

int Karta::getOrginalnaSila()
{
    return orginalnaSila;
}

void Karta::setOrginalnaSila(int s) {
    orginalnaSila = s;
}

QString Karta::getMoc()
{
    return moc;
}

int Karta::getBohater()
{
    return bohater;
}
