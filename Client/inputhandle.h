#ifndef INPUTHANDLE_H
#define INPUTHANDLE_H

#include <QObject>
#include "network.h"

class InputHandle : public QObject
{
	Q_OBJECT
public:
	explicit InputHandle(Network *n, QObject *parent = 0);

signals:
	void connectTo(QString ip, QString port);
	void disconnect();
	void send(QString string);

public slots:
	void start(void);

private:
	QFile *fin, *fout;
	QTextStream sin, sout;
	Network *network;
};

#endif // INPUTHANDLE_H
