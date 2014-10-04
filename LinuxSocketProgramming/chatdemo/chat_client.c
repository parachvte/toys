#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "sock_util.h"

#define SERV_HOST       "localhost"
#define SERV_PORT       2333
#define MAX_MSG_SIZE    500

int send_msg(char *serv_host, int serv_port, char *msg) {
    int sockfd;
    int numbytes;
    char res[MAX_MSG_SIZE];

    if ((sockfd = make_active_socket_tcp(SERV_HOST, SERV_PORT)) == -1) {
        perror("can't connect to server");
        return 0;
    }

    printf("Sending message: %s\n", msg);
    if ((numbytes = send(sockfd, msg, strlen(msg), 0)) == -1) {
        perror("call send() error");
        exit(1);
    }

    if ((numbytes = recv(sockfd, res, MAX_MSG_SIZE, 0)) == -1) {
        perror("call recv() error");
        exit(1);
    } else {
        res[numbytes] = '\0';
        printf("Recieve message: %s\n", res);
    }
    return !strcmp(res, "success");
}

int main(int argc, char **argv) {
    int command;
    char serv_host[30];
    char msg[MAX_MSG_SIZE];
    int res;

    while (1) {
        printf("\n");
        printf("Type command:\n");
        printf(" 1) Set target host\n");
        printf(" 2) Send message\n");

        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%s", serv_host);

                struct hostent *hostinfo;
                hostinfo = gethostbyname(serv_host);

                if (hostinfo == NULL) {
                    perror("Unknown host");
                    return -1;
                }
                printf("Set target host to: %s\n", serv_host);
                break;
            case 2:
                scanf("%s", msg);
                if (!strcmp(serv_host, "")) strcpy(serv_host, SERV_HOST);

                printf("%s\n", serv_host);
                if ((res = send_msg(serv_host, SERV_PORT, msg)) == 1) {
                    // pass
                } else {
                    printf("send_msg() failed\n");
                }
                break;
            default:
                printf("ERROR\n");
                exit(1);
        }
    }


    return 0;
}
