#include "jothellowidget.h"
#include "ui_jothellowidget.h"

#include "game/jothellomapper.h"
#include "../common/Othello/jothello.h"
#include "application/jothelloinput.h"
#include "application/jothellooutput.h"

#include <JRoomModelClientRoomProcessor>

#include <Information/JRequestInformation>
#include <Socket/JMainClientSocket>

#include <QPainter>
#include <QMouseEvent>
#include <QTime>


JOthelloWidget::JOthelloWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JOthelloWidget)
{
    m_roomId = -1;
    m_processor = JRoomModelClientRoomProcessor::instance();
    ui->setupUi(this);
    m_othello = JOthello::getInstance();
    m_input = JOthelloInput::getInstance();
    m_output = JOthelloOutput::getInstance();
    connect(m_processor,
            SIGNAL(receiveRoomInfo(JRoom)),
            SLOT(receiveRoomInfo(JRoom)));
    connect(m_processor,
            SIGNAL(receiveRoomChat(JID,JID,QString)),
            SLOT(receiveRoomChat(JID,JID,QString)));
    m_output->setWidget(this);
    m_background.load(":/res/background.png");
    m_pixblack.load(":/res/black.png");
    m_pixwhite.load(":/res/white.png");
    m_pixturn.load(":/res/turn.png");
    m_pixiam.load(":/res/iam.png");
    JOthelloMapper::setLength(40);
    JOthelloMapper::setInitX(30);
    JOthelloMapper::setInitY(60);
    ui->label_color0->setPixmap(m_pixblack.scaledToHeight(20));
    ui->label_color1->setPixmap(m_pixwhite.scaledToHeight(20));
}

JOthelloWidget::~JOthelloWidget()
{
    delete ui;
}

void JOthelloWidget::setRoomId(JID roomId)
{
    m_roomId = roomId;
}

void JOthelloWidget::clearContent()
{
    ui->label_userid_0->clear();
    ui->label_userid_1->clear();
    ui->textBrowser_chat->clear();
    ui->lineEdit_chat->clear();
    m_othello->reset();
    updateScore();
}

void JOthelloWidget::resetOthello()
{
    m_othello->reset();
    updateScore();
    update();
}

void JOthelloWidget::resetReady()
{
    ui->label_userinfo_0->clear();
    ui->label_userinfo_1->clear();
}

void JOthelloWidget::putChess(int at,const QPoint& pt)
{
    Q_ASSERT( 0 == at || 1 == at );
    JOthello::Color color;
    if( 0 == at){
        color = JOthello::COL_BLACK;
    }else{
        color = JOthello::COL_WHITE;
    }
    JOthello::PutResult result = m_othello->PutChess(color,pt);
    Q_ASSERT( result == JOthello::PR_SUCCESS);
    if( JOthello::PR_SUCCESS == result ){
        updateTurnPixmap();
        updateScore();
    }
    update();
}

void JOthelloWidget::ready(int at)
{
    Q_ASSERT( 0 == at || 1 == at );
    JID userId = m_roominfo.getUserList().at(at);
    ui->textBrowser_chat->append(
        tr("<div style=\"color:red;font-size:14px\">%1 ready</div>")
        .arg( getUserNickName(userId) )
    );
    if( 0 == at){
        ui->label_userinfo_0->setText(tr("ready"));
    }else{
        ui->label_userinfo_1->setText(tr("ready"));
    }
}

void JOthelloWidget::gameOver(quint8 winner)
{
    JID userId = m_roominfo.getUserList().at(winner);
    ui->textBrowser_chat->append(
        tr("<div style=\"color:red;font-size:14px\">game over . %1 win .</div>")
        .arg( getUserNickName(userId) )
    );
}

void JOthelloWidget::refreshUserList()
{
    Q_ASSERT(m_roomId >=0);
    m_processor->requestRoomInfo(m_roomId);
}

void JOthelloWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    QPainter painter(this);
    JOthelloMapper* othelloMapper = JOthelloMapper::getInstance();
    JOthello othello = *m_othello;
    painter.drawPixmap(othelloMapper->board(),m_background);
    for(int i=0;i<MAXX;++i)
    {
        for(int j=0;j<MAXY;++j)
        {
            QRect rect = othelloMapper->mapToReal(QPoint(i,j));
            switch(othello[i][j])
            {
            case JOthello::COL_BLACK:
                painter.drawPixmap(rect,m_pixblack);
                break;
            case JOthello::COL_WHITE:
                painter.drawPixmap(rect,m_pixwhite);
                break;
            case JOthello::COL_NONE:
                break;
            case JOthello::COL_ERROR:
                break;
            }
        }
    }
}

void JOthelloWidget::mousePressEvent(QMouseEvent *e)
{
    JOthelloMapper* othelloMapper = JOthelloMapper::getInstance();
    QPoint pt = othelloMapper->mapToChess(e->pos());
    m_input->putChess(pt);
}

void JOthelloWidget::receiveRoomInfo(const JRoom& room)
{
    JID myUserId = m_input->getMyUserId();
    if(room.getRoomId() == m_roomId){
        m_roominfo = room ;
        if(room.getUserList().length()>0){
            JID userId = room.getUserList().at(0);
            if( userId == myUserId ){
                ui->label_iam0->setPixmap(m_pixiam);
                ui->label_iam1->clear();
            }
            ui->label_userid_0->setText( getUserNickName(userId) );
        }else{
            ui->label_userid_0->setText(QString::number(-1));
        }
        if(room.getUserList().length()>1){
            JID userId = room.getUserList().at(1);
            if( room.getUserList().at(1) == myUserId ){
                ui->label_iam1->setPixmap(m_pixiam);
                ui->label_iam0->clear();
            }
            ui->label_userid_1->setText( getUserNickName(userId) );
        }else{
            ui->label_userid_1->setText(QString::number(-1));
        }
    }
}

void JOthelloWidget::receiveRoomChat(JID userId,JID roomId,const QString& text)
{
    if( roomId == m_roomId ){
        ui->textBrowser_chat->append(
            QString("<div style=\"color:red;font-size:14px\">%1 "
                "<span style=\"color:blue;\">%2</span></div>"
                "<div>%3</div>"
            )
            .arg(getUserNickName(userId))
            .arg(QTime::currentTime().toString("hh:mm:ss"))
            .arg(text)
        );
    }
}

void JOthelloWidget::updateTurnPixmap()
{
    JOthello::Color turn = m_othello->getTurn();
    if(JOthello::COL_BLACK == turn){
        ui->label_turn0->setPixmap(m_pixturn);
        ui->label_turn1->clear();
    }else{
        ui->label_turn1->setPixmap(m_pixturn);
        ui->label_turn0->clear();
    }
}

void JOthelloWidget::updateScore()
{
    ui->label_score0->setText(QString::number(m_othello->getScore(JOthello::COL_BLACK)));
    ui->label_score1->setText(QString::number(m_othello->getScore(JOthello::COL_WHITE)));
}

QString JOthelloWidget::getUserNickName(JID userId){
    JRequestUserInfo rui(JMainClientSocket::instance(),0);
    JUserInfo userinfo = rui.pullInformation(userId,1000);
    QString userNickname;
    if( userinfo.m_userId == userId ){
        userNickname = userinfo.m_nickname ;
    }else{
        userNickname = tr("no nickname(%1)").arg(userId);
    }
    return userNickname;
}

void JOthelloWidget::on_btn_escape_clicked()
{
    m_processor->requestEnterRoom(-1);
}

void JOthelloWidget::on_lineEdit_chat_returnPressed()
{
    const QString& text = ui->lineEdit_chat->text();
    if(!text.isEmpty()){
        m_processor->sendRoomChat(text);
    }
    ui->lineEdit_chat->clear();
}

void JOthelloWidget::on_btn_ready_clicked()
{
    m_input->ready();
    updateTurnPixmap();
}
