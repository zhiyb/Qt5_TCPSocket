#include "inputhandle.h"
#include <QtDebug>
#include <QtCore>
#include <QHostAddress>

InputHandle::InputHandle(Network *n, QObject *parent) :
	QObject(parent), network(n)
{
	fin = new QFile(this);
	fin->open(stdin, QIODevice::ReadOnly);
	sin.setDevice(fin);
	fout = new QFile(this);
	fout->open(stdout, QIODevice::WriteOnly);
	sout.setDevice(fout);
	connect(this, SIGNAL(connectTo(QString,QString)), network, SLOT(connectTo(QString,QString)));
	connect(this, SIGNAL(send(QString)), network, SLOT(send(QString)));
}

void InputHandle::start(void)
{
loop:
	sout.flush();
	QStringList input(sin.readLine().split(" "));
	if (input.size() == 0)
		return;
	QString cmd = input.at(0);
	if (cmd == "stop") {
		QThread::currentThread()->quit();
		qApp->quit();
		return;
	} else if (cmd == "connect") {
		if (input.size() != 3) {
			sout << "[CMD] You need to specify host address and port!\n";
			goto loop;
		}
		QString host = input.at(1), port = input.at(2);
		if (host.isEmpty())
			sout << "[INFO] You need to specify host address and port!\n";
		else if (network->socket->state() != QTcpSocket::UnconnectedState)
			sout << "[INFO] Already connected!\n";
		else
			emit connectTo(host, port);
	} else if (cmd == "disconnect") {
		network->socket->disconnectFromHost();
	} else if (cmd == "send") {
		if (input.size() != 2) {
			sout << "[CMD] You need to specify the data!\n";
			goto loop;
		}
		if (network->socket->state() != QTcpSocket::ConnectedState) {
			sout << "[CMD] Not yet connected!\n";
			goto loop;
		}
		emit send(input.at(1));
	} else if (cmd == "state")
		sout << (network->socket->state()) << '\n';
	goto loop;
}

void InputHandle::finish(void) {}
