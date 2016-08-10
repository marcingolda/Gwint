#include "talia.h"
#include <QtGui>
#include <ctime>


Talia::Talia(QString _talia)
{

    max = 36;
    kartaWtalii = new Karta*[max];
    losowaKarta = new Random(time(0));
    inicjalizuj(_talia);
}

Talia::~Talia()
{
    delete[] kartaWtalii;
    delete losowaKarta;
}




void Talia::inicjalizuj(QString c)
{
    QString tmp = c;
    QString dir,dir2,dir3,dir4;
    int count;
    int num = 1;

            if(tmp=="elfy")
            {
                dir=":talie/elfy/rodzaj.txt";
                dir2=":talie/elfy/sila.txt";
                dir3=":talie/elfy/moc.txt";
                dir4=":talie/elfy/bohater.txt";
            }
            else if(tmp=="kpln")
           {
                dir=":talie/kpln/rodzaj.txt";
                dir2=":talie/kpln/sila.txt";
                dir3=":talie/kpln/moc.txt";
                dir4=":talie/kpln/bohater.txt";
           }
            else if(tmp=="ptwr")
                {
                dir=":talie/ptwr/rodzaj.txt";
                dir2=":talie/ptwr/sila.txt";
                dir3=":talie/ptwr/moc.txt";
                dir4=":talie/ptwr/bohater.txt";
                }
            else
                {
                dir=":talie/ngrd/rodzaj.txt";
                dir2=":talie/ngrd/sila.txt";
                dir3=":talie/ngrd/moc.txt";
                dir4=":talie/ngrd/bohater.txt";
                }


            QFile plik(dir);
            QTextStream in( & plik );

            QFile plik2(dir2);
            QTextStream in2( & plik2 );

            QFile plik3(dir3);
            QTextStream in3( & plik3 );

            QFile plik4(dir4);
            QTextStream in4( & plik4 );

            if (!plik.open(QIODevice::ReadOnly | QIODevice::Text) || (!plik2.open(QIODevice::ReadOnly | QIODevice::Text)) || (!plik3.open(QIODevice::ReadOnly | QIODevice::Text) || (!plik4.open(QIODevice::ReadOnly | QIODevice::Text))))
                    return;

                  for (count=0;count<36;count++)
                kartaWtalii[count] = new Karta(in.readLine(), num++, in2.readLine().toInt(), in3.readLine(), in4.readLine().toInt());


}

void Talia::setMax(int v)
{
	max = v;
}

int Talia::getMax()
{
	return max;
}

Karta* Talia::zwrocKarte(int i)
{
    return kartaWtalii[i];
}

Karta* Talia::dajKarte()
{
    int i = static_cast<int>(losowaKarta->rand()*(max-1));

    Karta *temp = kartaWtalii[i];
    kartaWtalii[i] = kartaWtalii[max-1];
	max --;
	return temp;
}
