#include <QApplication>
#include <QtCore>

#include "start.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    QSplashScreen *splash = new QSplashScreen(QPixmap(":icons/logo.png"));
	splash->show();

	QString home = QDir::homePath();

    QFile file(home + "/.gwint");
    
	QDir dir;
    dir.mkdir(home + "/.gwint");


    Start *start = new Start();
    start->show();

    splash->finish(start);
	delete splash;

	return app.exec();
}
