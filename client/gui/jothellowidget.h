#ifndef JOTHELLOWIDGET_H
#define JOTHELLOWIDGET_H

#include <Global/Global>

#include <JRoom>

#include <QWidget>

namespace Ui {
    class JOthelloWidget;
}
class JRoomModelClientRoomProcessor;
class JRoom;
class JOthello;
class JOthelloInput;
class JOthelloOutput;
class JRequestUserInfo;

class JOthelloWidget : public QWidget
{
    Q_OBJECT
public:
    explicit JOthelloWidget(QWidget *parent = 0);
    ~JOthelloWidget();
    void setRoomId(JID roomId);
    void clearContent();///< 清理用户列表、聊天区域等。
    void resetOthello();
    void resetReady();
    void putChess(int at,const QPoint& pt);
    void ready(int at);
    void gameOver(quint8 winner);
public slots:
    void refreshUserList();
protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
private:
    Ui::JOthelloWidget *ui;
    JRoomModelClientRoomProcessor* m_processor;
    JRequestUserInfo* m_rui;
    JOthello *m_othello;
    JOthelloInput *m_input;
    JOthelloOutput *m_output;
    JID m_roomId;
    JRoom m_roominfo;
    QPixmap m_background;
    QPixmap m_pixblack;
    QPixmap m_pixwhite;
    QPixmap m_pixturn;
    QPixmap m_pixiam;
private:
    void updateTurnPixmap();
    void updateScore();
private slots:
    void on_btn_ready_clicked();
    void on_lineEdit_chat_returnPressed();
    void on_btn_escape_clicked();
    void receiveRoomInfo(const JRoom& room);
    void receiveRoomChat(JID userId,JID roomId,const QString& text);
};

#endif // JOTHELLOWIDGET_H
