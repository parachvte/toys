#include "Server.h"
#include "OverlappedIO.h"
#include "ThreadObj.h"
#include "Notifier.h"


Server::Server()
{
}

void Server::run()
{
    int nPort = 2333, backlog = 200;

    g_nThreadCount = 1;
    g_notifier.NotifyThreadNumber(g_nThreadCount);

    StartServer(nPort, backlog);
}

