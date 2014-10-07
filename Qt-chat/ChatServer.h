#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QThread>

class ChatServer : public QThread
{
private:
    const static int MAX_MSG_SIZE = 200;
    const static int SERV_PORT = 2333;
    const static int SERV_BACKLOG = 5;
    bool processRequest(int sockfd);

public:
    ChatServer();

protected:
    void run();
};

#endif // CHATSERVER_H
