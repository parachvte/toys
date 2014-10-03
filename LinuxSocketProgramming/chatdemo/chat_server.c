#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "sock_util.h"


#define SERV_PORT       2333
#define SERV_BACKLOG    5
#define MAX_MSG_SIZE    500

int read_from_client(int sock);

void chat_server() {
    int sockfd = make_passive_socket_tcp(SERV_PORT, SERV_BACKLOG); // make a TCP socket

    fd_set active_fds;
    fd_set read_fds;

    struct sockaddr_in client_addr;
    int i;

    // Initialize
    FD_ZERO(&active_fds);
    FD_SET(sockfd, &active_fds);

    while (1) {
        memcpy(&read_fds, &active_fds, sizeof(read_fds));

        if (select(FD_SETSIZE, &read_fds, (fd_set *)NULL, (fd_set *)NULL,
                   (struct timeval *)NULL) < 0) {
            perror("call select() error");
            exit(1);
        }

        // Connections on original socket
        if (FD_ISSET(sockfd, &read_fds)) {
            int new_socket, size;

            size = sizeof (client_addr);
            new_socket = accept(sockfd, (struct sockaddr *)&client_addr, &size);
            if (new_socket < 0) {
                perror("call accept() error");
                exit(1);
            }
            FD_SET(new_socket, &active_fds);
        }
        for (i = 0; i < FD_SETSIZE; i++)
            if (i != sockfd && FD_ISSET(i, &read_fds)) {
                // Data arriving on already connected socket
                if (read_from_client(i)) {
                    close(i);
                    FD_CLR(i, &active_fds);
                }
            }
    }
}

int read_from_client(int sockfd) {
    char msg[MAX_MSG_SIZE];
    char res[MAX_MSG_SIZE];
    int numbytes;

    if ((numbytes = recv(sockfd, msg, MAX_MSG_SIZE, 0)) == -1) {
        perror("call recv() error");
        exit(1);
    } else {
        msg[numbytes] = '\0';
        printf("Recieve message: %s\n", msg);
    }

    strcpy(res, "success");
    if ((numbytes = send(sockfd, res, strlen(res), 0)) == -1) {
        perror("call send() error");
        exit(1);
    }

    return !strcmp(res, "success");
}

int main() {
    printf("Starting chat server on port: %d\n", SERV_PORT);
    chat_server();
    return 0;
}
