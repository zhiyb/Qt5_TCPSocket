#ifndef HANDLE_H
#define HANDLE_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonDocument>

class Handle : public QObject
{
	Q_OBJECT
public:
	explicit Handle(QTcpSocket *s, QObject *parent = 0);

signals:
	void JSONReceived(QJsonDocument doc);

private slots:
	void disconnected(void);
	void read(void);

private:
	QTcpSocket *socket;
};

#endif // HANDLE_H
