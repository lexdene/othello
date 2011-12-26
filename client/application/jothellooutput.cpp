#include "jothellooutput.h"

#include "gui/jothellowidget.h"

#include <QDebug>

JOthelloOutput* JOthelloOutput::getInstance()
{
    static JOthelloOutput instance;
    return &instance;
}

void JOthelloOutput::setWidget(JOthelloWidget* widget)
{
    m_widget = widget;
}

void JOthelloOutput::ready(int at)
{
    if(NULL == m_widget) return;
    m_widget->ready(at);
}

void JOthelloOutput::putChess(int at,const QPoint& pt)
{
    if(NULL == m_widget) return;
    m_widget->putChess(at,pt);
}

void JOthelloOutput::gameOver(quint8 winner)
{
    if(NULL == m_widget) return;
    m_widget->gameOver(winner);
}

void JOthelloOutput::escape(quint8)
{
    qDebug()<<"JOthelloOutput::escape : unfinished";
}

void JOthelloOutput::resetOthello()
{
    if(NULL == m_widget) return;
    m_widget->resetOthello();
}

void JOthelloOutput::resetReady()
{
    if(NULL == m_widget) return;
    m_widget->resetReady();
}

JOthelloOutput::JOthelloOutput(QObject *parent) :
    QObject(parent)
{
    m_widget = NULL;
}
