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

public slots:
	void start(void);
	void finish(void);

private:
	QFile *fin, *fout;
	QTextStream sin, sout;
	Network *network;
};

#endif // INPUTHANDLE_H
