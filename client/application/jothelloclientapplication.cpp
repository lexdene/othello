#include "jothelloclientapplication.h"

#include "jothelloinput.h"
#include "jothellooutput.h"
#include "../common/jothelloprotocol.h"

#include <JRoom>

#include <QPoint>

#include <QDebug>

JOthelloClientApplication::JOthelloClientApplication(QObject *parent) :
    JClientApplicationBase(parent)
{
    m_input = NULL;
    m_output = NULL;
}

void JOthelloClientApplication::processGameData(const QByteArray& data)
{
    QDataStream stream(data);
    quint8 protocol;
    stream>>protocol;
    switch(protocol){
    case EOP_Ready:
        {
            quint8 at;
            stream>>at;
            m_output->ready(at);
        }
        break;
    case EOP_PutChess:
        {
            quint8 pt;
            stream>>pt;
            int at = pt/64;
            int x = pt/8%8;
            int y = pt%8;
            Q_ASSERT( 0 == at || 1 == at);
            m_output->putChess(at,QPoint(x,y));
        }
        break;
    case EOP_GameOver:
        {
            quint8 winner;
            stream>>winner;
            Q_ASSERT( 0 == winner || 1 == winner);
            m_output->gameOver(winner);
        }
        break;
    case EOP_Escape:
        {
            quint8 at;
            stream>>at;
            Q_ASSERT( 0 == at || 1 == at);
            m_output->escape(at);
        }
        break;
    case EOP_Reset:
        {
            quint8 type;
            stream>>type;
            if( type & ERT_Othello){
                m_output->resetOthello();
            }
            if( type & ERT_Ready){
                m_output->resetReady();
            }
        }
        break;
    default:
        qDebug()<<"JOthelloClientApplication::processGameData : no such protocol :"<<protocol;
        break;
    }
}

void JOthelloClientApplication::createRoomInfo(JRoom& room)
{
    room.setMax(2);
}

void JOthelloClientApplication::setInput(JOthelloInput* input)
{
    m_input = input;
    m_input->setApplication(this);
}

void JOthelloClientApplication::setOutput(JOthelloOutput* output)
{
    m_output = output;
}

void JOthelloClientApplication::sendPutChess(const QPoint& pt)
{
    Q_ASSERT(pt.x() >=0);
    Q_ASSERT(pt.x() < 8);
    Q_ASSERT(pt.y() >=0);
    Q_ASSERT(pt.y() < 8);
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    quint8 p;
    p = pt.x()*8 + pt.y();
    outstream<<(quint8)EOP_PutChess;
    outstream<<p;
    sendData(outdata);
}

void JOthelloClientApplication::sendReady()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_Ready;
    sendData(outdata);
}
