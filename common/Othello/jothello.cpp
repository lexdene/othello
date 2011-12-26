#include "jothello.h"

JOthello::JOthello()
{
    reset();
}

JOthello* JOthello::getInstance()
{
    static JOthello instance;
    return &instance;
}

JOthello::PutResult JOthello::PutChess(JOthello::Color turn , const QPoint &pt)
{
    static const QPoint direction[8]={
        QPoint(-1,-1),QPoint(-1,0),QPoint(-1,1),
        QPoint(0,-1),              QPoint(0,1),
        QPoint(1,-1), QPoint(1,0), QPoint(1,1)
    };
    if(turn != getTurn()) return PR_NOTYOURTURN;
    if(getColor(pt)==COL_ERROR ) return PR_OVERLOAD;
    if(getColor(pt)!=COL_NONE ) return PR_ILLEGAL;
    bool turnsuccess=false;
    for(int i=0;i<8;++i)
    {
        if( getColor(pt+direction[i]) + m_turn == COL_BLACK + COL_WHITE)
        {
            for(int step=1;step<MAXL;++step)
            {
                switch(getColor(pt+direction[i]*step))
                {
                case COL_NONE:
                case COL_ERROR:
                    step=MAXL;//to excape the step loop
                    break;
                case COL_BLACK:
                case COL_WHITE:
                    if(getColor(pt+direction[i]*step)==m_turn)
                    {
                        for(int j=1;j<step;++j)
                        {
                            m_map[(pt+direction[i]*j).x()][(pt+direction[i]*j).y()]=m_turn;
                        }
                        step=MAXL;
                        turnsuccess=true;
                    }
                    break;
                }
            }
        }
    }
    if(turnsuccess)
    {
        m_map[pt.x()][pt.y()]=m_turn;
        m_turn=(JOthello::Color)(COL_BLACK+COL_WHITE-m_turn);
        return PR_SUCCESS;
    }else{
        return PR_ILLEGAL;
    }
}

JOthello::PutResult JOthello::PutChess(JOthello::Color turn , int x,int y)
{
    return PutChess(turn,QPoint(x,y));
}

JOthello::Color JOthello::getTurn()const
{
    return m_turn;
}

void JOthello::reset()
{
    for(int i=0;i<MAXX;++i)
    {
        for(int j=0;j<MAXY;++j)
        {
            m_map[i][j]=COL_NONE;
        }
    }
    m_map[MAXX/2][MAXY/2]=m_map[MAXX/2-1][MAXY/2-1]=COL_WHITE;
    m_map[MAXX/2-1][MAXY/2]=m_map[MAXX/2][MAXY/2-1]=COL_BLACK;
    m_turn=COL_BLACK;
}

JOthello::Color JOthello::getColor (const QPoint &pt)const
{
    if(pt.x()<0 || pt.x() >=MAXX || pt.y()<0 || pt.y()>= MAXY)
    {
        return COL_ERROR;
    }
    return m_map[pt.x()][pt.y()];
}

const JOthello::Color* JOthello::operator[](int i)const
{
    return m_map[i];
}

JOthello::Color JOthello::getWinner()const
{
    int i,j;
    int count[4];
    for(i=0;i<4;++i){
        count[i] = 0;
    }
    for(i=0;i<MAXX;++i){
        for(j=0;j<MAXY;++j){
            if(canPutChess(getTurn(),QPoint(i,j))){
                return COL_ERROR;
            }
            Color color = getColor(QPoint(i,j));
            ++count[color];
        }
    }
    if(count[COL_BLACK] > count[COL_WHITE]){
        return COL_BLACK;
    }else if(count[COL_BLACK] < count[COL_WHITE]){
        return COL_WHITE;
    }else{
        return COL_NONE;
    }
}

int JOthello::getScore(JOthello::Color turn)const
{
    int i,j;
    int count = 0;
    for(i=0;i<MAXX;++i){
        for(j=0;j<MAXY;++j){
            if(getColor(QPoint(i,j)) == turn){
                ++count;
            }
        }
    }
    return count;
}

JOthello::Color JOthello::getOpstColor(Color col)
{
    return (JOthello::Color)(COL_BLACK+COL_WHITE-col);
}

bool JOthello::canPutChess(JOthello::Color turn,const QPoint& pt)const
{
    static const QPoint direction[8]={
        QPoint(-1,-1),QPoint(-1,0),QPoint(-1,1),
        QPoint(0,-1),              QPoint(0,1),
        QPoint(1,-1), QPoint(1,0), QPoint(1,1)
    };
    if(getColor(pt)==COL_ERROR ) return false;
    if(getColor(pt)!=COL_NONE ) return false;
    for(int i=0;i<8;++i)
    {
        if( getColor(pt+direction[i]) + turn == COL_BLACK + COL_WHITE)
        {
            for(int step=1;step<MAXL;++step)
            {
                switch(getColor(pt+direction[i]*step))
                {
                case COL_NONE:
                case COL_ERROR:
                    step=MAXL;//to excape the step loop
                    break;
                case COL_BLACK:
                case COL_WHITE:
                    if(getColor(pt+direction[i]*step)==turn)
                    {
                        return true;
                    }
                    break;
                }
            }
        }
    }
    return false;
}
