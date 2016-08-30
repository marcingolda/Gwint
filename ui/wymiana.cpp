#include "wymiana.h"
#include "ui_wymiana.h"

Wymiana::Wymiana(QString t, int numer[],  QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    connect(ok, SIGNAL(clicked()), this, SLOT(wymien()));

    connect(c1, SIGNAL(clicked()), this, SLOT(klikKarta1()));
    connect(c2, SIGNAL(clicked()), this, SLOT(klikKarta2()));
    connect(c3, SIGNAL(clicked()), this, SLOT(klikKarta3()));
    connect(c4, SIGNAL(clicked()), this, SLOT(klikKarta4()));
    connect(c5, SIGNAL(clicked()), this, SLOT(klikKarta5()));
    connect(c6, SIGNAL(clicked()), this, SLOT(klikKarta6()));
    connect(c7, SIGNAL(clicked()), this, SLOT(klikKarta7()));
    connect(c8, SIGNAL(clicked()), this, SLOT(klikKarta8()));
    connect(c9, SIGNAL(clicked()), this, SLOT(klikKarta9()));
    connect(c10, SIGNAL(clicked()), this, SLOT(klikKarta10()));


        num.setNum(numer[0]);
        karta = ":talie/" + t + "/" + num + ".png";
        p1->setPixmap(QPixmap(karta));

        num.setNum(numer[1]);
        karta = ":talie/" + t + "/" + num + ".png";
        p2->setPixmap(QPixmap(karta));

        num.setNum(numer[2]);
        karta = ":talie/" + t + "/" + num + ".png";
        p3->setPixmap(QPixmap(karta));

        num.setNum(numer[3]);
        karta = ":talie/" + t + "/" + num + ".png";
        p4->setPixmap(QPixmap(karta));

        num.setNum(numer[4]);
        karta = ":talie/" + t + "/" + num + ".png";
        p5->setPixmap(QPixmap(karta));

        num.setNum(numer[5]);
        karta = ":talie/" + t + "/" + num + ".png";
        p6->setPixmap(QPixmap(karta));

        num.setNum(numer[6]);
        karta = ":talie/" + t + "/" + num + ".png";
        p7->setPixmap(QPixmap(karta));

        num.setNum(numer[7]);
        karta = ":talie/" + t + "/" + num + ".png";
        p8->setPixmap(QPixmap(karta));

        num.setNum(numer[8]);
        karta = ":talie/" + t + "/" + num + ".png";
        p9->setPixmap(QPixmap(karta));


        num.setNum(numer[9]);
        karta = ":talie/" + t + "/" + num + ".png";
        p10->setPixmap(QPixmap(karta));



}

void Wymiana::wymien()
{
    this->destroyed();
    setVisible(false);
    destroy();
}


void Wymiana::niewidoczne()
{
    c1->setEnabled(false);
    c2->setEnabled(false);
    c3->setEnabled(false);
    c4->setEnabled(false);
    c5->setEnabled(false);
    c6->setEnabled(false);
    c7->setEnabled(false);
    c8->setEnabled(false);
    c9->setEnabled(false);
    c10->setEnabled(false);
}

void Wymiana::klikKarta1()
{
  c1->setEnabled(false);

  if(wym1 == NULL)
      wym1 = "0";
  else if(wym2 == NULL)
  {
      wym2 = "0";
      niewidoczne();
  }

}

void Wymiana::klikKarta2()
{
    c2->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "1";
    else if(wym2 == NULL)
    {
        wym2 = "1";
        niewidoczne();
    }
}

void Wymiana::klikKarta3()
{
    c3->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "2";
    else if(wym2 == NULL)
    {
        wym2 = "2";
        niewidoczne();
    }

}

void Wymiana::klikKarta4()
{
    c4->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "3";
    else if(wym2 == NULL)
    {
        wym2 = "3";
        niewidoczne();
    }
}

void Wymiana::klikKarta5()
{
    c5->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "4";
    else if(wym2 == NULL)
    {
        wym2 = "4";
        niewidoczne();
    }
}

void Wymiana::klikKarta6()
{
    c6->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "5";
    else if(wym2 == NULL)
    {
        wym2 = "5";
        niewidoczne();
    }
}

void Wymiana::klikKarta7()
{
    c7->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "6";
    else if(wym2 == NULL)
    {
        wym2 = "6";
        niewidoczne();
    }
}

void Wymiana::klikKarta8()
{
    c8->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "7";
    else if(wym2 == NULL)
    {
        wym2 = "7";
        niewidoczne();
    }

}

void Wymiana::klikKarta9()
{
    c9->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "8";
    else if(wym2 == NULL)
    {
        wym2 = "8";
        niewidoczne();
    }
}

void Wymiana::klikKarta10()
{
    c10->setEnabled(false);

    if(wym1 == NULL)
        wym1 = "9";
    else if(wym2 == NULL)
    {
        wym2 = "9";
        niewidoczne();
    }
}

QString Wymiana::getWym1()
{
    return wym1;
}

QString Wymiana::getWym2()
{
    return wym2;
}

void Wymiana::closeEvent(QCloseEvent *event)
{
    event->ignore();
    setVisible(false);
    destroy();

}

