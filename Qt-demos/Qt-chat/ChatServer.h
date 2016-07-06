#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QThread>
#include <QString>

class ChatServer : public QThread
{
    Q_OBJECT

private:
    const static int MAX_MSG_SIZE = 200;
    const static int SERV_PORT = 2333;
    const static int SERV_BACKLOG = 5;
    bool processRequest(int sockfd);

public:
    ChatServer();

protected:
    void run();

signals:
    //void messageReceived(char *message);
    // I tried to use char*, but when the first time the signal is sent,
    // char *message is missing. (Maybe a Qt's bug)
    void messageReceived(QString message);
};

#endif // CHATSERVER_H
