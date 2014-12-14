#ifndef INITSOCK_H
#define INITSOCK_H

#include <winsock2.h>

//#pragma comment(lib, "WS2_32")

class CInitSock
{
public:
    CInitSock(BYTE minorVer = 2, BYTE majorVer = 2)
    {
        // Initialize WS2_32.dll
        WSADATA wsaData;
        WORD sockVersion = MAKEWORD(minorVer, majorVer);
        if (::WSAStartup(sockVersion, &wsaData) != 0)
        {
            exit(0);
        }
    }
    ~CInitSock()
    {
        ::WSACleanup();
    }
};

#endif // INITSOCK_H
