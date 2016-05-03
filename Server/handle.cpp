#include "handle.h"
#include <QThread>
#include <QDebug>

void Handle::start()
{
	bytesAvailable = 0;
	timerID = 0;
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
	qDebug() << "[HANDLE]" << QThread::currentThread() << "New connection";
}

void Handle::timerEvent(QTimerEvent *)
{
	qint64 bytes = bytesAvailable;
	bytesAvailable = socket->bytesAvailable();
	if (bytesAvailable != bytes) {
		bytesAvailable = bytes;
		return;
	}
	killTimer(timerID);
	timerID = 0;

	QJsonDocument doc = QJsonDocument::fromBinaryData(socket->readAll());
	if (doc.isNull()) {
		qDebug() << "[HANDLE]" << QThread::currentThread() << "Invalid JSON received!";
		return;
	}
	qDebug() << "[DEBUG]" << QThread::currentThread() << "JSON received:" << doc;
	emit JSONReceived(doc);
}

void Handle::disconnected()
{
	qDebug() << "[HANDLE]" << QThread::currentThread() << "Disconnected";
	delete socket;
	emit finished(QThread::currentThread());
}

void Handle::read()
{
	if (!timerID)
		timerID = startTimer(10);
}
