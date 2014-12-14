#include <stdio.h>
#include <iostream>
#include "../Common/InitSock.h"

using namespace std;

CInitSock InitSock;

#define SERV_PORT 2333
#define BUFFER_SIZE 65536

void usage()
{
    cout << "Usage:" << endl;
    cout << "  Client.exe server_ip file_path [output_file]" << endl;
}

char server_ip[20];
char file_path[200];
char output_file[100];
char buff[BUFFER_SIZE];

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        usage();
        return 0;
    }

    strncpy(server_ip, argv[1], 20);
    strncpy(file_path, argv[2], 200);
    int file_path_len = strlen(file_path);

    if (argc == 4)
    {
        strncpy(output_file, argv[3], 100);
    } else
    {
        for (int i = file_path_len - 1; i >= 0; i--)
            if (file_path[i] == '\\')
            {
                for (int j = i + 1; j < file_path_len; j++)
                    output_file[j - i - 1] = file_path[j];
                output_file[file_path_len - i - 1] = '\0';
                break;
            }
    }
    printf("server_ip = %s,\nfile_path = %s,\noutput_file = %s\n\n", server_ip, file_path, output_file);

    // Start~
    SOCKET s = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s == INVALID_SOCKET)
    {
        printf("socket() failed.\n");
        return 0;
    }

    sockaddr_in si;
    si.sin_family = AF_INET;
    si.sin_port = ::htons(SERV_PORT);
    si.sin_addr.S_un.S_addr = inet_addr(server_ip);

    if (::connect(s, (sockaddr *) &si, sizeof(si)) == SOCKET_ERROR)
    {
        printf("connect() failed.\n");
        return 0;
    }

    int nSend = ::send(s, file_path, strlen(file_path), 0);
    if (nSend == 0)
    {
        printf("send() failed.\n");
        return 0;
    } else
        //printf("send: %s (length = %d)\n", file_path, nSend);
        printf("getting file [%s] from [%s] ...\n", file_path, server_ip);

    int nRecv = ::recv(s, buff, BUFFER_SIZE, 0);
    if (nRecv > 0)
    {
        buff[nRecv] = '\0';
        //printf("Received data: %s\n", buff);
        printf("Saving file to [%s] ...\n", output_file);
            freopen(output_file, "w", stdout);
        printf("%s", buff);
        fclose(stdout);
    } else
        printf("recv() failed.\n");

    ::closesocket(s);
    
    return 0;
}

