#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "sock_util.h"

#define SERV_HOST       "localhost"
#define SERV_PORT       2333
#define MAX_MSG_SIZE    500

int send_msg(char *msg) {
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
    if (argc != 2) {
        printf("arguments wrong");
        exit(1);
    }

    char msg[MAX_MSG_SIZE];
    int res;
    strcpy(msg, argv[1]);

    if ((res = send_msg(msg)) == 1) {
        printf("send_msg() success\n");
    } else {
        printf("send_msg() failed\n");
    }
    return 0;
}
