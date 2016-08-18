#ifndef WYBORRZEDU_H
#define WYBORRZEDU_H

#include <QDialog>
#include <QtGui>

#include "ui_wyborrzedu.h"

namespace Ui {
    class WyborRzedu;
}

class WyborRzedu : public QDialog, private Ui::WyborRzedu
{
    Q_OBJECT

public:
    explicit WyborRzedu(QString, QWidget *parent = 0);
    void setRzad(QString);
    QString getRzad();
    QString ktoryRzad;
    virtual void closeEvent(QCloseEvent *);

public slots:
    void jednObleznicze();
    void jednWalczace();
    void jednStrzeleckie();

private:
   Ui::WyborRzedu ui;
};



#endif // WYBORRZEDU_H
