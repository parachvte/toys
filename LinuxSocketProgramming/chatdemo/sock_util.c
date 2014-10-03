#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "sock_util.h"


int make_passive_socket_tcp(int port, int backlog)
{
    int sockfd;
    struct sockaddr_in serv_addr;

    // Socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("call socket() error");
        exit(1);
    }

    // Set serv_addr
    init_sockaddr(&serv_addr, "", port);

    // Once the service is down, we should wait for the port to clear,
    // or just call setsockopt() to reuse the port
    int yes = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("call setsocketopt() error");
        exit(1);
    }

    // Bind sockfd with serv_addr
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof (struct sockaddr)) == -1) {
        perror("call bind() error");
        exit(1);
    }

    // Listen
    if (listen(sockfd, backlog) < 0) {
        perror("call listen() error");
        exit(1);
    }

    return sockfd;
}

/**
 * `port` is the port client is connecting to.
 *
 * @param `port`
 */
int make_active_socket_tcp(const char *hostname, int port) {
    int sockfd;
    struct hostent *hostinfo;
    struct sockaddr_in serv_addr;

    // Socket
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("call socket() error");
        exit(1);
    }
 
    // Set serv_addr
    init_sockaddr(&serv_addr, hostname, port);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) {
        perror("call connect() error");
        exit(1);
    }

    return sockfd;
}

/**
 * Given `hostname` and `port`, return a well filled struct sockaddr_in.
 *
 * @param `addr`
 * @param `hostname`
 * @param `port`
 */
int init_sockaddr(struct sockaddr_in *addr, const char *hostname, uint16_t port) {
    struct hostent *hostinfo;

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    if (!strcmp(hostname, "")) {
        // set hostname empty means
        addr->sin_addr.s_addr = INADDR_ANY;
    } else {
        hostinfo = gethostbyname(hostname);

        if (hostinfo == NULL) {
            perror("Unknown host");
            exit(1);
        }
        addr->sin_addr = *(struct in_addr *) hostinfo->h_addr;
    }
    memset(&(addr->sin_zero), 0, 8);
}
