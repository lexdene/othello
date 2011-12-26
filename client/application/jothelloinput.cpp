#include "jothelloinput.h"

#include "jothelloclientapplication.h"

#include <QDebug>
#include <QPoint>

JOthelloInput::JOthelloInput(QObject *parent) :
    QObject(parent)
{
    m_application = NULL;
}

JOthelloInput* JOthelloInput::getInstance()
{
    static JOthelloInput instance;
    return &instance;
}

void JOthelloInput::setApplication(JOthelloClientApplication* app)
{
    m_application = app;
}

void JOthelloInput::putChess(const QPoint& pt)
{
    if(NULL == m_application) return;
    if(pt.x() >= 0
       && pt.x() < 8
       && pt.y() >=0
       && pt.y() < 8){
        m_application->sendPutChess(pt);
    }
}

void JOthelloInput::ready()
{
    if(NULL == m_application) return;
    m_application->sendReady();
}

JID JOthelloInput::getMyUserId()const
{
    if(NULL == m_application) return -1;
    return m_application->getMyUserId();
}

//void JOthelloInput::emit_input(const QPoint& pt)
//{
//    emit input(pt);
//}
