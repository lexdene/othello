#ifndef JOTHELLOCLIENTAPPLICATION_H
#define JOTHELLOCLIENTAPPLICATION_H

#include <JClientApplicationBase>

class QPoint;

class JOthelloInput;
class JOthelloOutput;

class JOthelloClientApplication : public JClientApplicationBase
{
    Q_OBJECT
public:
    explicit JOthelloClientApplication(QObject *parent = 0);
    void processGameData(const QByteArray& data);
    void createRoomInfo(JRoom&);
    void setInput(JOthelloInput* input);
	void setOutput(JOthelloOutput* output);
    void sendPutChess(const QPoint& pt);
    void sendReady();
private:
	JOthelloInput* m_input;
    JOthelloOutput* m_output;
};

#endif // JOTHELLOCLIENTAPPLICATION_H
