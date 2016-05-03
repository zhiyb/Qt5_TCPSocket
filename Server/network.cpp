#include "network.h"
#include "handle.h"
#include <QtDebug>
#include <QHostAddress>
#include <QThread>

Network::Network(QObject *parent) :
	QObject(parent)
{
	server = new QTcpServer(this);
	if (!server->listen(QHostAddress::Any, 6000))
		qFatal("Cannot listen on port 6000!");
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	qDebug() << "[INFO] Server started";
}

Network::~Network(void)
{
	qDebug() << "[INFO] Stopping the server...";
	foreach (QThread *thread, threadPool) {
		thread->quit();
		thread->wait();
		qDebug() << "[HANDLE]" << thread << "Deleted";
		delete thread;
	}
}

void Network::newConnection(void)
{
	QThread *handleThread = new QThread(this);
	threadPool.append(handleThread);
	QTcpSocket *socket = server->nextPendingConnection();
	connect(handleThread, SIGNAL(finished()), socket, SLOT(deleteLater()));
	Handle *handle = new Handle(socket);
	connect(handleThread, SIGNAL(started()), handle, SLOT(start()));
	connect(handleThread, SIGNAL(finished()), handle, SLOT(deleteLater()));
	connect(handle, SIGNAL(finished(QThread*)), this, SLOT(join(QThread*)));
	handle->moveToThread(handleThread);
	handleThread->start();
}

void Network::join(QThread *thread)
{
	thread->quit();
	thread->wait();
	threadPool.removeAll(thread);
	qDebug() << "[HANDLE]" << thread << "Deleted";
	delete thread;
}
