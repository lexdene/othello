#include "jmemorylineedit.h"

#include <QKeyEvent>

JMemoryLineEdit::JMemoryLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}

void JMemoryLineEdit::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()){
    case Qt::Key_Up:
        moveP(ED_Up);
        break;
    case Qt::Key_Down:
        moveP(ED_Down);
        break;
    case Qt::Key_Return:
        addMemory(text());
        resetP();
        break;
    }
    QLineEdit::keyPressEvent(e);
}

void JMemoryLineEdit::resetP()
{
    m_p = m_memory.length();
}

void JMemoryLineEdit::moveP(EDirection dire)
{
    int di =0 ;
    switch(dire){
    case ED_Up:
        di = -1;
        break;
    case ED_Down:
        di = 1;
        break;
    }
    int p = m_p + di;
    if(p>=0 && p<m_memory.length()){
        m_p = p;
        setText(m_memory.at(m_p));
    }else if( -1 == p || m_memory.length() == p){
        m_p = p;
        clear();
    }
}

void JMemoryLineEdit::addMemory(const QString& text)
{
    if(!text.isEmpty()){
        m_memory.push_back(text);
    }
}
