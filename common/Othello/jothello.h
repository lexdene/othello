#ifndef JOTHELLO_H
#define JOTHELLO_H

const int MAXX=8;
const int MAXY=8;
const int MAXL=MAXX>MAXY?MAXX:MAXY;

#include <QPoint>

class JOthello
{
public:
    enum Color{COL_NONE,COL_BLACK,COL_WHITE,COL_ERROR};
    enum PutResult{
        PR_SUCCESS,
        PR_NOTYOURTURN,///< 没有轮到你呢
        PR_OVERLOAD,///< 超出棋盘边界
        PR_ILLEGAL,///< 非法置子
    };

    JOthello();
    static JOthello* getInstance();
    /// 这两个函数会自动修改turn
    PutResult PutChess(Color turn,const QPoint &pt);
    PutResult PutChess(Color turn,int x,int y);
    Color getTurn()const;
    void reset();
    Color getColor(const QPoint& pt)const;
    const Color* operator[](int i)const;
    // COL_NONE : draw
    // COL_ERROR : not over
    Color getWinner()const;
    int getScore(Color turn)const;
    static Color getOpstColor(Color);
private:
    Color m_turn;
    Color m_map[MAXX][MAXY];
private:
    bool canPutChess(Color turn,const QPoint& pt)const;
};

#endif // JOTHELLO_H
