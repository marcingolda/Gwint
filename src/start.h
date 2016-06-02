#ifndef H_START
#define H_START

#include <QtGui>


#include "ui_start.h"

class Start : public QDialog, private Ui::Start
{
Q_OBJECT

public:
    Start(QWidget *parent = 0);

    void ustawienia();
	void zapiszDane();

protected:
	virtual void closeEvent(QCloseEvent *);

public slots:
	void polacz();
	void wyjdz();
	void widocznySerwer();
	void widocznyKlient();

};

#endif
