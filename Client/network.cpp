#include "network.h"
#include <QtDebug>
#include <QtCore>
#include <QHostAddress>

Network::Network(QObject *parent) :
	QObject(parent)
{
	socket = new QTcpSocket;
	connect(socket, SIGNAL(connected()), this, SLOT(connected()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	qDebug() << "[INFO] Client started";
}

Network::~Network(void)
{
	qDebug() << "[INFO] Stopping the client...";
}

void Network::connected(void)
{
	qDebug() << "[INFO] Connected";
}

void Network::disconnected(void)
{
	qDebug() << "[INFO] Disonnected";
}

void Network::connectTo(QString ip, QString port)
{
	//socket->connectToHost(QHostAddress(ip), port.toInt());
	socket->connectToHost(ip, port.toInt());
}

void Network::disconnect()
{
	socket->disconnectFromHost();
}

void Network::send(QString string)
{
	QJsonDocument doc;
	QJsonArray array;
	array.append(QJsonValue(string));
	doc.setArray(array);
	send(doc);
}

void Network::send(QJsonDocument doc)
{
	socket->write(doc.toJson());
}
