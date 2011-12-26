#ifndef JMEMORYLINEEDIT_H
#define JMEMORYLINEEDIT_H

#include <QLineEdit>

class JMemoryLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit JMemoryLineEdit(QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent *);
private:
    enum EDirection{ED_Up,ED_Down};

    void resetP();
    void moveP(EDirection dire);
    void addMemory(const QString& text);
    QStringList m_memory;
    int m_p;
};

#endif // JMEMORYLINEEDIT_H
