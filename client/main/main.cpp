#include <QtGui/QApplication>
#include <QFile>
#include "gui/jothellowindow.h"

#include "application/jothelloclientapplication.h"
#include "application/jothelloinput.h"
#include "application/jothellooutput.h"

#include <JRoomModelClientStartup>

void loadStyles(){
    QFile qss("styles/othello.qss");
    qss.open(QFile::ReadOnly);
    QByteArray data = qss.readAll();
    qApp->setStyleSheet(data);
    qss.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JRoomModelClientStartup rmcs(a);
    if(!rmcs.startup()) return 1;
    JOthelloClientApplication oapp;
    oapp.setInput(JOthelloInput::getInstance());
    oapp.setOutput(JOthelloOutput::getInstance());
    oapp.setInstance(&oapp);
    JOthelloWindow w;
    w.show();
    loadStyles();
    return a.exec();
}
