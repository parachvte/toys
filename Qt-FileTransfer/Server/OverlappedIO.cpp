#include "OverlappedIO.h"
#include "ThreadObj.h"
#include <QDebug>

#include "../Common/InitSock.h"
CInitSock initSock;


void StartServer(int nPort, int backlog)
{
    SOCKET sListen = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in si;
    si.sin_family = AF_INET;
    si.sin_port = ::htons(nPort);
    si.sin_addr.S_un.S_addr = INADDR_ANY;
    if (::bind(sListen, (sockaddr *) &si, sizeof(si)) == SOCKET_ERROR)
    {
        qDebug() << "bind() failed." << endl;
        return;
    }
    ::listen(sListen, backlog);

    ::InitializeCriticalSection(&g_cs);
    while (TRUE)
    {
        sockaddr_in client_si;
        int nLen = sizeof(client_si);
        SOCKET sClient = ::accept(sListen, (sockaddr *) &client_si, &nLen);
        if (sClient == INVALID_SOCKET)
            continue;

        PSOCKET_OBJ pClientSocket = GetSocketObj(sClient);
        if (pClientSocket == NULL)
        {
            qDebug() << "GetSocketObj() error" << endl;
            continue;
        }
        PBUFFER_OBJ pClientBuffer = GetBufferObj(pClientSocket, BUFFER_SIZE);
        if (pClientBuffer == NULL)
        {
            qDebug() << "GetBufferObj() error" << endl;
            continue;
        }

        pClientBuffer->addrRemote = client_si;
        if (AssignToFreeThread(pClientBuffer))
        {
            PostRecv(pClientBuffer);
        } else
            qDebug() << "AssignToFreeThread() failed." << endl;
    }
    ::DeleteCriticalSection(&g_cs);
}
