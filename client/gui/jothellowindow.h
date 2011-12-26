#ifndef JOTHELLOWINDOW_H
#define JOTHELLOWINDOW_H

#include <Global/Global>

#include <QMainWindow>

namespace Ui {
    class JOthelloWindow;
}


class JOthelloWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit JOthelloWindow(QWidget *parent = 0);
    ~JOthelloWindow();

private:
    Ui::JOthelloWindow *ui;
private slots:
    void on_page_roomwidget_enterRoom(JID roomId);
};

#endif // JOTHELLOWINDOW_H
