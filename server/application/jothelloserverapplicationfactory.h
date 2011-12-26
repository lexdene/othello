#ifndef JOTHELLOSERVERAPPLICATIONFACTORY_H
#define JOTHELLOSERVERAPPLICATIONFACTORY_H

#include <JServerApplicationFactoryBase>

class JOthelloServerApplicationFactory : public JServerApplicationFactoryBase
{
    Q_OBJECT
public:
    explicit JOthelloServerApplicationFactory(QObject *parent = 0);
	JServerApplicationBase* createApplication(int roomId);
};

#endif // JOTHELLOSERVERAPPLICATIONFACTORY_H
