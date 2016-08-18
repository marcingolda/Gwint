#include "wyborrzedu.h"
#include "ui_wyborrzedu.h"


QString ktoryRzad = "null";


WyborRzedu::WyborRzedu(QString c, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(walczace, SIGNAL(clicked()), this, SLOT(jednWalczace()));
    connect(obleznicze, SIGNAL(clicked()), this, SLOT(jednObleznicze()));
    connect(strzeleckie, SIGNAL(clicked()), this, SLOT(jednStrzeleckie()));

    if (c == "podwojnyZasieg")
    {
        obleznicze->setVisible(false);
    }

}



void WyborRzedu::jednWalczace()
{
    setRzad("walczace");
    this->destroyed();
    setVisible(false);
    destroy();
}

void WyborRzedu::jednObleznicze()
{
    setRzad("obleznicze");
    this->destroyed();
    setVisible(false);
    destroy();
}

void WyborRzedu::jednStrzeleckie()
{
    setRzad("strzeleckie");
    this->destroyed();
    setVisible(false);
    destroy();
}

void WyborRzedu::setRzad(QString c)
{
    ktoryRzad = c;
}

QString WyborRzedu::getRzad()
{
    return ktoryRzad;
}

void WyborRzedu::closeEvent(QCloseEvent *event)
{
    event->ignore();
    setVisible(false);
    destroy();

}


