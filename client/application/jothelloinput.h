#ifndef JOTHELLOINPUT_H
#define JOTHELLOINPUT_H

#include <Global/Global>

#include <QObject>

class QPoint;
class JOthelloClientApplication;

class JOthelloInput : public QObject
{
    Q_OBJECT
public:
    explicit JOthelloInput(QObject *parent = 0);
    static JOthelloInput* getInstance();
    void setApplication(JOthelloClientApplication* app);
    void ready();
    void putChess(const QPoint& pt);

    // api
    JID getMyUserId()const;
private:
    JOthelloClientApplication* m_application;
};

#endif // JOTHELLOINPUT_H
