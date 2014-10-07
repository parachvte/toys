#include "ChatClient.h"
#include "SockUtil.h"

#include <QDebug>

ChatClient::ChatClient()
{
    setServHost("localhost");
    serv_port = 2333;
}

bool ChatClient::setServHost(const char *_serv_host) {
    if (strlen(_serv_host) >= 30)
        return false;

    strcpy(serv_host, _serv_host);
    return true;
}

bool ChatClient::sendMessage(const char *message)
{
    int sockfd;
    int numbytes;

    if ((sockfd = SockUtil::makeActiveTCP(serv_host, serv_port)) == -1)
    {
        qDebug() << "Can't connect to server";
        return false;
    }

    if ((numbytes = send(sockfd, message, strlen(message), 0)) == -1)
    {
        qDebug() << "Call send() error";
        return false;
    }

    char response[MAX_MSG_SIZE];
    if ((numbytes = recv(sockfd, response, MAX_MSG_SIZE, 0)) == -1)
    {
        qDebug() << "Call send() error";
        return false;
    } else
    {
        response[numbytes] = '\0';
        return !strcmp(response, "success");
    }
}
