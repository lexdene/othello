#ifndef JOTHELLOMAPPER_H
#define JOTHELLOMAPPER_H

#include <QPoint>
#include <QRect>

// position on chess board called chess position (0-7,0-7)
// position on real screen called real position(0-600,0-400)
class JOthelloMapper
{
public:
    JOthelloMapper();
    QPoint mapToChess(const QPoint&)const;
    QRect mapToReal(const QPoint&)const;
    QRect board()const;

    static JOthelloMapper* getInstance();
    // together set height and width
    static void setLength(int length);
    static void setHeight(int height);
    static void setWidth(int width);
    static void setInitX(int initx);
    static void setInitY(int inity);
private:
    static int s_height;
    static int s_width;
    static int s_initx;
    static int s_inity;
};

#endif // JOTHELLOMAPPER_H
