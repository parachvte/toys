#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define DEST_IP "127.0.0.1"
#define DEST_PORT 80

int main() {
    int sockfd;
    struct sockaddr_in dest_addr;

    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket() error");
        exit(1);
    }

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(DEST_PORT);
    inet_aton(DEST_IP, &dest_addr.sin_addr);
    memset(&(dest_addr.sin_zero), 0, 8);

    if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof (struct sockaddr)) == -1) {
        perror("connect() error");
        exit(1);
    } else {
        printf("connect() success\n");
    }

    return 0;
}
