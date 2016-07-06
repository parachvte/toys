#include "SockUtil.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

#include <string.h>

#include <QDebug>


SockUtil::SockUtil()
{
}

int SockUtil::makeActiveTCP(const char *hostname, int port)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    // Socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
    {
        qDebug() << "Call socket() error";
        return -1;
    }

    // Set serv_addr
    if (initSockaddr(&serv_addr, hostname, port) == false)
    {
        qDebug() << "Call initSockaddr() error";
        close(sockfd);
        return -1;
    }

    // Connect
    if (connect(sockfd, (struct sockaddr *)&serv_addr,
                sizeof(struct sockaddr)) == -1)
    {
        qDebug() << "Call connect() error";
        close(sockfd);
        return -1;
    }

    return sockfd;
}

int SockUtil::makePassiveTCP(int port, int backlog)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    // Socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        qDebug() << "Call socket() error";
        exit(1);
    }

    // Set serv_addr
    if (initSockaddr(&serv_addr, "", port) == false) {
        qDebug() << "Call initSockaddr() error";
        close(sockfd);
        exit(1);
    }

    // Once the service is down, we should wait for the port to clear,
    // or just call setsockopt() to reuse the port
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        qDebug() << "Call setsockopt() error";
        close(sockfd);
        exit(1);
    }

    // Bind sockfd with serv_addr
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof (struct sockaddr)) == -1) {
        qDebug() << "Call bind() error";
        close(sockfd);
        exit(1);
    }

    // Listen
    if (listen(sockfd, backlog) < 0) {
        qDebug() << "Call listen() error";
        close(sockfd);
        exit(1);
    }

    return sockfd;
}

bool SockUtil::initSockaddr(sockaddr_in *addr, const char *hostname,
                           uint16_t port)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    if (!strcmp(hostname, ""))
    {
        addr->sin_addr.s_addr = INADDR_ANY;
    } else
    {
        struct hostent *hostinfo;
        hostinfo = gethostbyname(hostname);

        if (hostinfo == NULL)
        {
            qDebug() << "Unknown host";
            return false;
        }
        addr->sin_addr = *(struct in_addr *) hostinfo->h_addr;
    }
    memset(&(addr->sin_zero), 0, 8);
    return true;
}
