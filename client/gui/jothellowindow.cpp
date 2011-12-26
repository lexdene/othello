#include "jothellowindow.h"
#include "ui_jothellowindow.h"

JOthelloWindow::JOthelloWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JOthelloWindow)
{
    ui->setupUi(this);
}

JOthelloWindow::~JOthelloWindow()
{
    delete ui;
}

void JOthelloWindow::on_page_roomwidget_enterRoom(JID roomId)
{
    if(roomId >=0){
        ui->page_gamewidget->clearContent();
        ui->page_gamewidget->setRoomId(roomId);
        ui->page_gamewidget->refreshUserList();
        ui->centralWidget->setCurrentIndex(1);

    }else{
        ui->page_gamewidget->clearContent();
        ui->centralWidget->setCurrentIndex(0);
        ui->page_gamewidget->setRoomId(-1);
    }
}
