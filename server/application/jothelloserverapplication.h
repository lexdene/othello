#ifndef JOTHELLOSERVERAPPLICATION_H
#define JOTHELLOSERVERAPPLICATION_H

#include <JServerApplicationBase>

class JOthello;
class QPoint;

const int Othello_MAX_USER=2;

class JOthelloServerApplication : public JServerApplicationBase
{
    Q_OBJECT
public:
	explicit JOthelloServerApplication(JID roomId,QObject *parent = 0);
    void resetGame(quint8 type);
	JCode enterRoom(JID userId);
    JCode escapeRoom(JID userId);
    void afterEnterRoom(JID userId);
    void afterEscapeRoom(JID userId);
    void processGameData(int at, const QByteArray& data);
    void resetAndSend(quint8 type);
private:
	JID m_users[Othello_MAX_USER];
    JOthello* m_othello;
    bool m_ready[Othello_MAX_USER];
private:
    bool isGameStarted()const;
    void processReady(int at);
    void processPutChess(int at,const QPoint& pt);

    void sendReady(int at);
    void sendPutChess(int at,const QPoint& pt);
    void sendGameOver(quint8 winner);
    void sendEscape();
    void sendReset(quint8 type);
};

#endif // JOTHELLOSERVERAPPLICATION_H
