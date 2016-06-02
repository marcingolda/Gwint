#ifndef THREAD_H_
#define THREAD_H_

#include <QThread>
#include <QtGui>

class Thread : public QThread
{
Q_OBJECT

public:
	Thread(QObject *parent = 0);

	void setGiocatore(int);
	void setSleepMs(int);

protected:
	virtual void run();

signals:
	void sygnalG1();
	void sygnalG2();

private:
	int gracz;
	int sleepMs;
};

#endif
