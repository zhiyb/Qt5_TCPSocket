#include <QCoreApplication>
#include <QThread>
#include "network.h"
#include "inputhandle.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	Network n;

	QThread inputHandleThread;
	InputHandle ih(&n);
	ih.moveToThread(&inputHandleThread);
	QObject::connect(&inputHandleThread, SIGNAL(started()), &ih, SLOT(start()));
	inputHandleThread.start();

	int ret = a.exec();
	inputHandleThread.quit();
	inputHandleThread.wait();

	return ret;
}
