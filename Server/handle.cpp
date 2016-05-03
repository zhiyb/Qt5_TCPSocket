#include "handle.h"
#include <QThread>
#include <QDebug>

void Handle::start()
{
	bytesAvailable = 0;
	timerID = startTimer(10);
	connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
	connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
	qDebug() << "[HANDLE]" << QThread::currentThread() << "New connection";
}

void Handle::timerEvent(QTimerEvent *)
{
	qint64 bytes = bytesAvailable;
	bytesAvailable = socket->bytesAvailable();
	//qDebug() << __func__ << timerID << bytes << bytesAvailable;
	if (bytesAvailable != bytes)
		return;
	killTimer(timerID);
	timerID = 0;
	if (bytesAvailable == 0)
		return;
	bytesAvailable = 0;

	QByteArray data = socket->readAll();
	QJsonDocument doc = QJsonDocument::fromJson(data);
	if (doc.isNull()) {
		qDebug() << "[HANDLE]" << QThread::currentThread() << "Invalid JSON received!" << data;
		return;
	}
	qDebug() << "[DEBUG]" << QThread::currentThread() << "JSON received:" << doc;
	emit JSONReceived(doc);
}

void Handle::disconnected()
{
	qDebug() << "[HANDLE]" << QThread::currentThread() << "Disconnected";
	emit finished(QThread::currentThread());
}

void Handle::read()
{
	if (!timerID)
		timerID = startTimer(10);
}
