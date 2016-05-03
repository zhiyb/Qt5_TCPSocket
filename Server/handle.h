#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

class Handle : public QObject
{
	Q_OBJECT
public:
	explicit Handle(QTcpSocket *s, QObject *parent = 0) : QObject(parent), socket(s) {}

public slots:
	void start();

protected:
	void timerEvent(QTimerEvent *);

signals:
	void JSONReceived(QJsonDocument doc);
	void finished(QThread *);

private slots:
	void disconnected();
	void read();

private:
	int timerID;
	qint64 bytesAvailable;
	QTcpSocket *socket;
};

#endif // HANDLE_H
