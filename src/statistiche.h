#ifndef STATISTICHE_H_
#define STATISTICHE_H_

#include <QtGui>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "ui_statistiche.h"

class Statistiche : public QWidget, public Ui::Statistiche
{
Q_OBJECT

public:
	Statistiche(QSqlDatabase, QWidget *parent = 0);

public slots:
	void stampaQuery();
	void stampaQuery(QString);
	void cancellaStatistiche();

private:
	QSqlDatabase db;
	QSqlTableModel *model;
};

#endif
