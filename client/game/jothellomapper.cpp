#include "jothellomapper.h"

#include "../common/Othello/jothello.h"

JOthelloMapper::JOthelloMapper()
{
    Q_ASSERT(s_height>0);
    Q_ASSERT(s_width>0);
    Q_ASSERT(s_initx>=0);
    Q_ASSERT(s_inity>=0);
}

QPoint JOthelloMapper::mapToChess(const QPoint& pt)const
{
    return QPoint(
            (pt.x()-s_initx+s_width*10)/s_width-10,
            (pt.y()-s_inity+s_height*10)/s_height-10
            );
}

QRect JOthelloMapper::mapToReal(const QPoint& pt)const
{
    return QRect(
            pt.x()*s_width + s_initx,
            pt.y()*s_height + s_inity,
            s_width,
            s_height
            );
}

QRect JOthelloMapper::board()const
{
    return QRect(
            s_initx,
            s_inity,
            s_width * MAXX,
            s_height * MAXY
            );
}

JOthelloMapper* JOthelloMapper::getInstance()
{
    static JOthelloMapper instance;
    return &instance;
}

void JOthelloMapper::setLength(int length)
{
    setWidth(length);
    setHeight(length);
}

void JOthelloMapper::setHeight(int height)
{
    if(height > 0){
        s_height = height;
    }
}

void JOthelloMapper::setWidth(int width)
{
    if(width>0){
        s_width = width;
    }
}

void JOthelloMapper::setInitX(int initx)
{
    s_initx = initx;
}

void JOthelloMapper::setInitY(int inity)
{
    s_inity = inity;
}

int JOthelloMapper::s_height=40;
int JOthelloMapper::s_width=40;
int JOthelloMapper::s_initx=30;
int JOthelloMapper::s_inity=60;
