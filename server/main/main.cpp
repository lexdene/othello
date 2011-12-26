#include <QCoreApplication>
#include <QDebug>

#include <JRoomModelServer>

#include "application/jothelloserverapplicationfactory.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	JOthelloServerApplicationFactory factory;
	factory.setInstance(&factory);
	JRoomModelServer server;
    quint16 port = server.run(61373);
    qDebug()<<port;
	return a.exec();
}
