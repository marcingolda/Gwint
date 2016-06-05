#include "thread.h"

Thread::Thread(QObject *parent) :
	QThread(parent)
{
    gracz = -1;
}

void Thread::ustawGracza(int _gracz)
{
    gracz = _gracz;
}

void Thread::setSleepMs(int ms)
{
	sleepMs = ms;
}

void Thread::run()
{
	msleep(sleepMs);
	
    if (gracz == 1)
        emit sygnalG1();
    else if (gracz == 2)
        emit sygnalG2();
}
