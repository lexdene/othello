#ifndef JOTHELLOOUTPUT_H
#define JOTHELLOOUTPUT_H

#include <QObject>

class QPoint;
class JOthelloWidget;

class JOthelloOutput : public QObject
{
    Q_OBJECT
public:
    static JOthelloOutput* getInstance();
    void setWidget(JOthelloWidget* widget);
    void ready(int at);
    void putChess(int at,const QPoint& pt);
    void gameOver(quint8 winner);
    void escape(quint8 at);
    void resetOthello();
    void resetReady();
private:
    explicit JOthelloOutput(QObject *parent = 0);
    JOthelloWidget* m_widget;
};

#endif // JOTHELLOOUTPUT_H
