#include "handle.h"
#include <QThread>
#include <QDebug>

Handle::Handle(QTcpSocket *s, QObject *parent) :
	QObject(parent), socket(s)
{
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
	qDebug() << "[HANDLE]" << QThread::currentThread() << "New connection";
}

void Handle::disconnected(void)
{
	qDebug() << "[HANDLE]" << QThread::currentThread() << "Disconnected";
	QThread::currentThread()->quit();
}

void Handle::read(void)
{
	qint64 size;
	do {
		size = socket->bytesAvailable();
		QThread::currentThread()->msleep(10);
	} while (size != socket->bytesAvailable());
	QJsonDocument doc = QJsonDocument::fromBinaryData(socket->readAll());
	if (doc.isNull()) {
		qDebug() << "[HANDLE]" << QThread::currentThread() << "Invalid JSON received!";
		return;
	}
	qDebug() << "[DEBUG]" << QThread::currentThread() << "JSON received:" << doc;
	emit JSONReceived(doc);
}
