#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>

class Network : public QObject
{
	Q_OBJECT
	friend class InputHandle;
public:
	explicit Network(QObject *parent = 0);
	~Network(void);

signals:

public slots:
	void connectTo(QString ip, QString port);
	void disconnect();
	void send(QString string);
	void send(QJsonDocument doc);

private slots:
	void connected(void);
	void disconnected(void);

private:
	QTcpSocket *socket;
};

#endif // NETWORK_H
