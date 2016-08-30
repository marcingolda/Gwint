#ifndef WYMIANA_H
#define WYMIANA_H

#include <QDialog>
#include <QtGui>

#include "src/gracz.h"
#include "ui_wymiana.h"

namespace Ui {
    class Wymiana;
}

class Wymiana : public QDialog, private Ui::Wymiana
{
    Q_OBJECT

public:
    explicit Wymiana(QString, int[], QWidget *parent = 0);
    void niewidoczne();
    QString wym1, wym2;
    QString getWym1();
    QString getWym2();
    QString karta;
    QString num;
    virtual void closeEvent(QCloseEvent *);

public slots:
    void wymien();
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


private:
    Ui::Wymiana ui;
};

#endif // WYMIANA_H
