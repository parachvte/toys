#include "ChatServer.h"

#include <QDebug>

#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "SockUtil.h"

ChatServer::ChatServer()
{
}

void ChatServer::run()
{
    // make a TCP socket
    int sockfd = SockUtil::makePassiveTCP(SERV_PORT, SERV_BACKLOG);

    fd_set active_fds;
    fd_set read_fds;

    struct sockaddr_in client_addr;
    int i;

    // Initialize
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);

    while (1)
    {
        memcpy(&read_fds, &active_fds, sizeof(read_fds));

        if (select(FD_SETSIZE, &read_fds, (fd_set *)NULL, (fd_set *)NULL,
                   (struct timeval *)NULL) < 0)
        {
            qDebug() << "Call select() error";
            exit(1);
        }

        // Connections on original socket
        if (FD_ISSET(sockfd, &read_fds))
        {
            int new_socket;
            socklen_t size;

            size = sizeof (client_addr);
            new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &size);
            if (new_socket < 0)
            {
                qDebug() << "Call accept() error";
                exit(1);
            }
            FD_SET(new_socket, &active_fds);
        }
        for (i = 0; i < FD_SETSIZE; i++)
            if (i != sockfd && FD_ISSET(i, &read_fds))
            {
                // Data arriving on already connected socket
                if (processRequest(i))
                {
                    close(i);
                    FD_CLR(i, &active_fds);
                }
            }
    }
}

bool ChatServer::processRequest(int sockfd)
{
    char msg[MAX_MSG_SIZE];
    char res[MAX_MSG_SIZE];
    int numbytes;

    if ((numbytes = recv(sockfd, msg, MAX_MSG_SIZE, 0)) == -1) {
        qDebug() << "Call recv() error";
        exit(1);
    } else {
        msg[numbytes] = '\0';
        emit messageReceived(QString(msg));
    }

    strcpy(res, "success");
    if ((numbytes = send(sockfd, res, strlen(res), 0)) == -1) {
        qDebug() << "Call send() error";
        exit(1);
    }

    return (size_t)numbytes == strlen(res);
}
