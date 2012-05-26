#include "jothelloserverapplication.h"

#include "../common/jothelloprotocol.h"
#include "../common/Othello/jothello.h"

#include <RoomErrorCode>

#include <QDebug>

JOthelloServerApplication::JOthelloServerApplication(JID roomId,QObject *parent) :
	JServerApplicationBase(roomId,parent)
{
	for(int i=0;i<Othello_MAX_USER;++i){
		m_users[i]=-1;
	}
    m_othello = new JOthello();
    resetGame(3);
}

void JOthelloServerApplication::resetGame(quint8 type)
{
    if( type & ERT_Othello){
        m_othello->reset();
    }
    if( type & ERT_Ready){
        for(int i=0;i<Othello_MAX_USER;++i){
            m_ready[i] = false;
        }
    }
}

JCode JOthelloServerApplication::enterRoom(JID userId)
{
	for(int i=0;i<Othello_MAX_USER;++i){
		if(m_users[i]<0){
			m_users[i]=userId;
			return 0;
		}
	}
	return ERoomIsFull;
}

JCode JOthelloServerApplication::escapeRoom(JID userId)
{
    for(int i=0;i<Othello_MAX_USER;++i){
        if(m_users[i]==userId){
            m_users[i]=-1;
            if(isGameStarted()) resetAndSend(3);
            else resetAndSend( ERT_Ready );
            return 0;
        }
    }
    return EUserIdNotExist;
}

void JOthelloServerApplication::afterEnterRoom(JID)
{
    for(int i=0;i<Othello_MAX_USER;++i){
        if(m_ready[i]){
            sendReady(i);
        }
    }
}

void JOthelloServerApplication::processGameData(int at , const QByteArray& data)
{
    Q_ASSERT( 0 == at || 1 == at);
    QDataStream stream(data);
    quint8 protocol;
    stream>>protocol;
    switch(protocol){
    case EOP_Ready:
        processReady(at);
        break;
    case EOP_PutChess:
        {
            quint8 pt;
            stream>>pt;
            int x = pt/8%8;
            int y = pt%8;
            processPutChess(at,QPoint(x,y));
        }
        break;
    default:
        qDebug()<<"JOthelloServerApplication::processGameData : no such protocol :"<<protocol;
        break;
    }
}

void JOthelloServerApplication::resetAndSend(quint8 type)
{
    resetGame(type);
    sendReset(type);
}

bool JOthelloServerApplication::isGameStarted()const
{
    for(int i=0;i<Othello_MAX_USER;++i){
        if(!m_ready[i]) return false;
    }
    return true;
}

void JOthelloServerApplication::processReady(int at)
{
    Q_ASSERT( 0 == at || 1 == at);
    if(!m_ready[at]){
        m_ready[at] =  true;
        sendReady(at);
        if(isGameStarted()) resetAndSend(ERT_Othello);
    }
}

void JOthelloServerApplication::processPutChess(int at,const QPoint& pt)
{
    if(!isGameStarted()) return;
    JOthello::Color color;
    if( 0 == at){
        color = JOthello::COL_BLACK;
    }else{
        color = JOthello::COL_WHITE;
    }
    if(m_othello->PutChess(color,pt) == JOthello::PR_SUCCESS){
        sendPutChess(at,pt);
    }
    JOthello::Color winnerColor = m_othello->getWinner();
    if(JOthello::COL_BLACK == winnerColor){
        sendGameOver(0);
        resetAndSend(ERT_Ready);
    }else if(JOthello::COL_WHITE == winnerColor){
        sendGameOver(1);
        resetAndSend(ERT_Ready);
    }else if(JOthello::COL_NONE == winnerColor){
        sendGameOver(2);
        resetAndSend(ERT_Ready);
    }
}

void JOthelloServerApplication::sendReady(int at)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_Ready;
    outstream<<(quint8)at;
    emit sendGameData(outdata);
}

void JOthelloServerApplication::sendPutChess(int at,const QPoint& pt)
{
    Q_ASSERT( 0 == at || 1 == at);
    Q_ASSERT( pt.x()>=0 && pt.x()<8 );
    Q_ASSERT( pt.y()>=0 && pt.y()<8 );
    quint8 ptdata;
    ptdata = at*64 + pt.x()*8 + pt.y();
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_PutChess;
    outstream<<ptdata;
    emit sendGameData(outdata);
}

void JOthelloServerApplication::sendGameOver(quint8 winner)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_GameOver;
    outstream<<winner;
    emit sendGameData(outdata);
}

void JOthelloServerApplication::sendEscape()
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_Escape;
    emit sendGameData(outdata);
}

void JOthelloServerApplication::sendReset(quint8 type)
{
    QByteArray outdata;
    QDataStream outstream(&outdata,QIODevice::WriteOnly);
    outstream<<(quint8)EOP_Reset;
    outstream<<type;
    emit sendGameData(outdata);
}
