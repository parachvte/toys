#include "ThreadObj.h"
#include "Notifier.h"
#include <stdio.h>
#include <QDebug>

CRITICAL_SECTION g_cs; // Should be initialized first
PTHREAD_OBJ g_pThreadList; // thread list
int g_nThreadCount;

LONG g_nCurrentConnections; // number of current connections


PTHREAD_OBJ GetThreadObj()
{
    PTHREAD_OBJ pThread = (PTHREAD_OBJ) ::GlobalAlloc(GPTR, sizeof(THREAD_OBJ));
    if (pThread != NULL)
    {
        ::EnterCriticalSection(&g_cs);
        g_nThreadCount ++;
        g_notifier.NotifyThreadNumber(g_nThreadCount);
        g_notifier.NotifyLogging("A thread created.");
        ::LeaveCriticalSection(&g_cs);

        pThread->nBufferCount = 0;
        pThread->pBufferList = NULL;
        ::InitializeCriticalSection(&pThread->cs);
        pThread->nEventCount = 1;
        pThread->events[0] = ::WSACreateEvent(); // For rebuilding
    }
    return pThread;
}

/*
 * This function will be called by pThread itself
 */
void FreeThreadObj(PTHREAD_OBJ pThread)
{
    ::EnterCriticalSection(&g_cs);
    PTHREAD_OBJ pTest = g_pThreadList;
    if (pTest == pThread)
    {
        g_pThreadList = pTest->pNext;
    } else
    {
        while (pTest != NULL && pTest->pNext != pThread)
            pTest = pTest->pNext;
        if (pTest != NULL)
            pTest->pNext = pThread->pNext;
        else
            qDebug() << "pThread not found, may something is wrong.." << endl;
    }
    g_nThreadCount --;
    g_notifier.NotifyThreadNumber(g_nThreadCount);
    g_notifier.NotifyLogging("A thread freed.");
    ::LeaveCriticalSection(&g_cs);

    ::DeleteCriticalSection(&pThread->cs);
    ::CloseHandle(pThread->events[0]);
    ::GlobalFree(pThread);
}

void RebuildEventArray(PTHREAD_OBJ pThread)
{
    ::EnterCriticalSection(&pThread->cs);
    PBUFFER_OBJ pBuffer = pThread->pBufferList;
    pThread->nEventCount = 1;
    while (pBuffer != NULL)
    {
        pThread->events[pThread->nEventCount++] = pBuffer->ol.hEvent;
        pBuffer= pBuffer->pNext;
    }
    ::LeaveCriticalSection(&pThread->cs);
}

BOOL InsertBufferObj(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer)
{
    BOOL bRet = FALSE;

    ::EnterCriticalSection(&pThread->cs);
    if (pThread->nBufferCount < WSA_MAXIMUM_WAIT_EVENTS)
    {
        if (pThread->pBufferList == NULL)
            pThread->pBufferList = pBuffer;
        else
        {
            pBuffer->pNext = pThread->pBufferList;
            pThread->pBufferList = pBuffer->pNext;
        }
        pThread->nBufferCount ++;
        bRet = TRUE;
    }
    ::LeaveCriticalSection(&pThread->cs);

    if (bRet)
    {
        ::InterlockedIncrement(&g_nCurrentConnections);
        ::EnterCriticalSection(&g_cs);
        g_notifier.NotifyConnectionNumber((int) g_nCurrentConnections);
        g_notifier.NotifyClientAdded(::inet_ntoa(pBuffer->addrRemote.sin_addr));

        // ugly logging...
        char *log = (char *) malloc(40);
        strcpy(log, "Client [");
        strcat(log, ::inet_ntoa(pBuffer->addrRemote.sin_addr));
        strcat(log, "] is connecting ...");
        g_notifier.NotifyLogging(log);
        // free(log); // free outside
        ::LeaveCriticalSection(&g_cs);
    }
    return bRet;
}

BOOL RemoveBufferObj(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer)
{
    ::EnterCriticalSection(&pThread->cs);
    PBUFFER_OBJ pTest = pThread->pBufferList;
    if (pTest == pBuffer)
    {
        pThread->pBufferList = pBuffer->pNext;
    } else
    {
        while (pTest != NULL && pTest->pNext != pBuffer)
            pTest = pTest->pNext;
        if (pTest != NULL)
            pTest->pNext = pBuffer->pNext;
        else
        {
            //qDebug() << "RemoveBufferObj() failed." << endl; // shouldn't be
            return FALSE;
        }
    }
    pThread->nBufferCount --;
    ::LeaveCriticalSection(&pThread->cs);

    ::WSASetEvent(&pThread->events[0]);
    ::InterlockedDecrement(&g_nCurrentConnections); // disconnected
    ::EnterCriticalSection(&g_cs);
    g_notifier.NotifyConnectionNumber((int) g_nCurrentConnections);
    g_notifier.NotifyClientRemoved(::inet_ntoa(pBuffer->addrRemote.sin_addr));

    // ugly logging...
    char *log = (char *) malloc(40);
    strcpy(log, "Client [");
    strcat(log, ::inet_ntoa(pBuffer->addrRemote.sin_addr));
    strcat(log, "] is disconnecting ...");
    g_notifier.NotifyLogging(log);
    // free(log); // free outside
    ::LeaveCriticalSection(&g_cs);
    return TRUE;
}

PBUFFER_OBJ FindBufferObj(PTHREAD_OBJ pThread, HANDLE hEvent)
{
    ::EnterCriticalSection(&pThread->cs);
    PBUFFER_OBJ pBuffer = pThread->pBufferList;
    while (pBuffer != NULL)
    {
        if (pBuffer->ol.hEvent == hEvent) break;
        pBuffer = pBuffer->pNext;
    }
    ::LeaveCriticalSection(&pThread->cs);
    return pBuffer;
}

BOOL HandleIO(PTHREAD_OBJ pThread, PBUFFER_OBJ pBuffer)
{
    ::WSAResetEvent(pBuffer->ol.hEvent);

    PSOCKET_OBJ pSocket = pBuffer->pSocket;
    pSocket->nOutstandingOps --;

    DWORD dwTrans;
    DWORD dwFlags;
    BOOL bRet = ::WSAGetOverlappedResult(pSocket->s, &pBuffer->ol, &dwTrans,
                                         FALSE, &dwFlags);
    if (!bRet)
    {
        CleanupSocket(pSocket);
        RemoveBufferObj(pThread, pBuffer);
        FreeBufferObj(pBuffer);
        return FALSE;
    }

    switch (pBuffer->nOperation)
    {
    case OP_READ:
        {
            if (dwTrans > 0)
            {
                // ugly logging...
                ::EnterCriticalSection(&g_cs);
                char *log = (char *) malloc(100);
                strcpy(log, "Tranfering file [");
                strcat(log, pBuffer->buff);
                strcat(log, "] to client [");
                strcat(log, ::inet_ntoa(pBuffer->addrRemote.sin_addr));
                strcat(log, "] ...");
                g_notifier.NotifyLogging(log);
                // free(log); // free outside
                ::LeaveCriticalSection(&g_cs);

                // Reuse `pBuffer` to send
                pBuffer->nLen = dwTrans;
                if (ReadFileToBuffer(pBuffer))
                {
                    PostSend(pBuffer);
                } else
                {
                    ::EnterCriticalSection(&g_cs);
                    g_notifier.NotifyLogging("File not exist.");
                    ::LeaveCriticalSection(&g_cs);

                    CleanupSocket(pSocket);
                    RemoveBufferObj(pThread, pBuffer);
                    FreeBufferObj(pBuffer);
                    return FALSE;
                }
            } else
            {
                CleanupSocket(pSocket);
                RemoveBufferObj(pThread, pBuffer);
                FreeBufferObj(pBuffer);
                return FALSE;
            }
        }
        break;
    case OP_WRITE:
        {
            ::EnterCriticalSection(&g_cs);
            g_notifier.NotifyLogging("File transfer finished.");
            ::LeaveCriticalSection(&g_cs);

            CleanupSocket(pSocket);
            RemoveBufferObj(pThread, pBuffer);
            FreeBufferObj(pBuffer);
            return FALSE;
        }
        break;
    }
    return TRUE;
}

DWORD WINAPI WorkerThread(LPVOID lpParam)
{
    PTHREAD_OBJ pThread = (PTHREAD_OBJ) lpParam;

    while (TRUE)
    {
        int nIndex = ::WSAWaitForMultipleEvents(pThread->nEventCount,
                                                pThread->events,
                                                FALSE, WSA_INFINITE, FALSE);
        if (nIndex == WSA_WAIT_FAILED)
        {
            printf("WSAWaitForMultipleEvents() failed()\n");
            break;
        }

        nIndex = nIndex - WSA_WAIT_EVENT_0;
        for (int i = nIndex; i < pThread->nEventCount; i++)
        {
            int nRet = ::WSAWaitForMultipleEvents(1, &pThread->events[i],
                                                  TRUE, 0, FALSE);
            if (nRet == WSA_WAIT_TIMEOUT || nRet == WSA_WAIT_FAILED)
                continue;
            else
            {
                if (i == 0)
                {
                    RebuildEventArray(pThread);

                    // all connections are finished, then terminate this thread
                    if (pThread->nBufferCount == 0)
                    {
                        FreeThreadObj(pThread); // Destroy itself
                        return 0;
                    }
                    ::WSAResetEvent(pThread->events[0]);
                } else
                {
                    PBUFFER_OBJ pBuffer = FindBufferObj(pThread, pThread->events[i]);
                    if (pBuffer != NULL)
                    {
                        // Maybe number of buffer objects is decreased
                        if (!HandleIO(pThread, pBuffer))
                            RebuildEventArray(pThread);
                    } else
                    {
                        qDebug() << "Unable to find buffer object." << endl;
                        printf("Unable to find buffer object.\n");
                    }
                }
            }
        }
    }

    return -1; // Probably not return here
}

BOOL AssignToFreeThread(PBUFFER_OBJ pBuffer)
{
    PTHREAD_OBJ pThread = g_pThreadList;

    ::EnterCriticalSection(&g_cs);
    while (pThread != NULL)
    {
        if (InsertBufferObj(pThread, pBuffer))
            break;
        pThread = pThread->pNext;
    }

    // If insertion failed, create a new thread for assignment
    if (pThread == NULL)
    {
        pThread = GetThreadObj();
        if (pThread == NULL)
            return FALSE;

        // Insert to thread list
        ::EnterCriticalSection(&g_cs);
        pThread->pNext = g_pThreadList;
        g_pThreadList = pThread;
        ::LeaveCriticalSection(&g_cs);

        // Insert to thread, and start this thread
        InsertBufferObj(pThread, pBuffer);
        ::CreateThread(NULL, 0, WorkerThread, pThread, 0, NULL);
    }
    ::LeaveCriticalSection(&g_cs);

    ::WSASetEvent(pThread->events[0]); // After insertion, perform a rebuild operation
    return TRUE;
}
