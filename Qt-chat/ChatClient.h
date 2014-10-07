#ifndef CHATCLIENT_H
#define CHATCLIENT_H


class ChatClient
{
private:
    const static int MAX_MSG_SIZE = 200;
    char serv_host[32];
    int serv_port;

public:
    ChatClient();
    bool sendMessage(const char *message);
    bool setServHost(const char *_serv_host);
};

#endif // CHATCLIENT_H
