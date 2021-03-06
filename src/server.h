#ifndef H_SERVER
#define H_SERVER

#include <QtNetwork>
#include <QtGui>


#include "talia.h"
#include "thread.h"
#include "karta.h"
#include "gracz.h"
#include "koniec.h"
#include "start.h"
#include "ui/wyborrzedu.h"
#include "ui/wymiana.h"

#include "ui_plansza.h"

extern QString rodzajTalii;

class Server : public QMainWindow, public Ui::Plansza
{
Q_OBJECT

public:
    Server(QString, int, QWidget *parent = 0);

    QString rodzajTaliiG1;

    void inicjujPartie(QString);
    void inicjujKolejnaPartie();
    int ktoZaczyna();
    void przyznajPunkty(int);
    void aktywnyGracz(int);
    void aktualizujPunkty(int);
    int tablicaNumerowSerwer[10];
    bool wymienioneServ;

    void wyslijWiadomosc(QString);
    void inicjuj();

    void ustawNickKlienta(QString);
    void kartyKlienta(QString);
    void klientOdlaczony(QString);
    void rodzajKlienta(QString);

    void ustawLiczbeKartG2();
    void ustawLiczbeKartG1();
    void ustawTure(int);
    void wydajWerdykt();
    void ustawLiczbeRund(QString);
    void przeciwnikPas(QString);
    void niewidoczneG1();
    void niewidoczneG2();
    void klikKarta(QString);
    void wymianaKartKlienta(QString);
    void wymianaKart();

    void wrocDoMenu();
    void ustawIkony();

private slots:
    void dodajPolaczenie();
    void odbierzWiadomosc();

    void klikKarta1();
    void klikKarta2();
    void klikKarta3();
    void klikKarta4();
    void klikKarta5();
    void klikKarta6();
    void klikKarta7();
    void klikKarta8();
    void klikKarta9();
    void klikKarta10();
    void klikPas();

    void odbierzSygnalG1();
    void odbierzSygnalG2();

protected:
    void closeEvent(QCloseEvent *);

private:
    QString nick;
    int port;
    QTcpServer* server;
    QTcpSocket* socket;
    QBuffer* buffer;
    Gracz *g1;
    Gracz *g2;
    Talia *talia;
    Talia *talia1;
    int tura;
    int pos1;
    int pos2;
    int roznica;
    Thread *th;
    bool Pas;
    bool rywalPas;
    int liczbaKart;


    void (Server::*metoda[8])(QString);

};

#endif
