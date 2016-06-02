#ifndef KLIENT_H_
#define KLIENT_H_

#include <QtNetwork>
#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>

#include "koniec.h"
#include "start.h"


#include "ui_plansza.h"

extern QString rodzajTalii;

class Klient : public QMainWindow, public Ui::Plansza
{
Q_OBJECT

public:
    Klient(QString, QString, int, QWidget *parent = 0);
	virtual ~Klient();
    QString rodzajTaliiG2;

	void wyslijWiadomosc(QString);
    void inicjuj();

	void wrocDoMenu();

//    void ustawKolorKupki(QString);
	void ustawNickSerwera(QString);
    void ustawKarty(QString c);
    void ustawLiczbeKartG2(QString);
    void ustawLiczbeKartG1(QString);
	void ustawTure(QString);
	void ustawKarteSerwera(QString);
	void aktualizujPunkty(QString);
    void aktualizujPunktySerwera(QString);
	void niewidoczneKarty(QString);
    void wydajWerdykt();
	void serwerOdlaczony(QString);

protected:
	virtual void closeEvent(QCloseEvent *);

public slots:
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

	
	void blad(QAbstractSocket::SocketError);

private:
	QString nick;
	QString ip;
	int port;
	int posServer;

	QTcpSocket *socket;
	QBuffer *buffer;

    void (Klient::*metoda[10])(QString);

};

#endif