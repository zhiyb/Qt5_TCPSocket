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
		qFatal("Cannot listening on port 6000!");
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	qDebug() << "[INFO] Server started";
}

Network::~Network(void)
{
	qDebug() << "[INFO] Stopping the server...";
}

void Network::newConnection(void)
{
	QThread *handleThread = new QThread(this);
	connect(this, SIGNAL(destroyed()), handleThread, SLOT(quit()));
	Handle *handle = new Handle(server->nextPendingConnection());
	handle->moveToThread(handleThread);
	handleThread->start();
}
