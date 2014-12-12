#include <stdio.h>
#include <string.h>
#include <winsock2.h>
#include "../common/initsock.h"

#define BUFFER_SIZE 2028
char buff[BUFFER_SIZE];

void Usage() {
    printf("Usage:\n");
    printf("  client.exe remote_ip command\n");
}

int send_command(char *remote_ip, char *cmd) {
    SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    SOCKADDR_IN server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(48888);
    server_addr.sin_addr.s_addr = inet_addr(remote_ip);

    // there is vulnerability, but client is running on hacker's PC, take it easy
    strncpy(buff, cmd, BUFFER_SIZE);
    buff[strlen(cmd)] = 0;
    printf("sending buff [%s] to %s\n", buff, inet_ntoa(server_addr.sin_addr));
    return sendto(s, buff, strlen(buff), 0, (PSOCKADDR) &server_addr, sizeof(SOCKADDR));
}

int main(int argc, char *argv[]) {
    InitWinsock();

    if (argc < 3) {
        Usage();
        return 0;
    }
    if (send_command(argv[1], argv[2]) < 0) {
        printf("send_command() failed: %s\n", GetLastError());
    }

    CleanupWinsock();
    return 0;
}
