#include "jothelloserverapplicationfactory.h"

#include "jothelloserverapplication.h"

JOthelloServerApplicationFactory::JOthelloServerApplicationFactory(QObject *parent) :
    JServerApplicationFactoryBase(parent)
{
}

JServerApplicationBase* JOthelloServerApplicationFactory::createApplication(int roomId)
{
	return new JOthelloServerApplication(roomId,this);
}
