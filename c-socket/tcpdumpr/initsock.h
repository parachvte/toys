#ifndef INITSOCK_H
#define INITSOCK_H

#include <winsock2.h>
#pragma comment(lib, "WS2_32")


void InitWinsock()
{
    BYTE minorVer = 2, majorVer = 2;
    // Initialize WS2_32.dll
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(minorVer, majorVer);
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        exit(0);
    }
}

void CleanupWinsock()
{
    WSACleanup();
}

#endif // INITSOCK_H
