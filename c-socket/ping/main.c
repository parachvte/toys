/*
 * ping - Send ICMP SEND_REQUEST packets to network hosts (Windows version)
 *
 * by Ryannnnnnn
 */

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#include "icmp.h"
#include "initsock.h"

BOOL SetTimeout(SOCKET s, int nTime, BOOL bRecv)
{
    int ret = setsockopt(s, SOL_SOCKET, bRecv ? SO_REUSEADDR : SO_SNDTIMEO,
                         (char *) &nTime, sizeof(nTime));
    return ret != SOCKET_ERROR;
}

int main()
{
    InitWinsock();

    char szDestIp[] = "172.20.250.21";
    SOCKET sRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sRaw == INVALID_SOCKET)
    {
        printf("Create raw socket failed: %d\n", GetLastError());
        return -1;
    }
    SetTimeout(sRaw, 1000, TRUE); // This function not found on Win API

    // Set destination
    SOCKADDR_IN dest;
    dest.sin_family = AF_INET;
    dest.sin_port = htons(0);
    dest.sin_addr.S_un.S_addr = inet_addr(szDestIp);

    // Create ICMP
    char buff[sizeof(ICMP_HDR) + 32]; // ICMP_HDR + IPHeader
    PICMP_HDR pIcmp = (PICMP_HDR) buff;
    pIcmp->icmp_type = 8; // Echo
    pIcmp->icmp_code = 0;
    pIcmp->icmp_id = (USHORT) GetCurrentProcessId();
    pIcmp->icmp_checksum = 0;
    pIcmp->icmp_sequence = 0;
    memset(&buff[sizeof(ICMP_HDR)], 'E', 32); // filled with whatever

    // Send / Recv
    USHORT nSeq = 0;
    char recvBuf[1024];
    SOCKADDR_IN from;
    int nLen = sizeof(from);

    while (TRUE)
    {
        static int nCount = 0;
        int nRet = 0;
        if (nCount ++ == 4)
            break;

        pIcmp->icmp_checksum = 0;
        pIcmp->icmp_timestamp = GetTickCount();
        pIcmp->icmp_sequence = nSeq ++;
        pIcmp->icmp_checksum = checksum((USHORT *) buff, sizeof(ICMP_HDR) + 32);

        // Send
        nRet = sendto(sRaw, buff, sizeof(ICMP_HDR) + 32, 0, (SOCKADDR *) &dest,
                      sizeof(dest));
        if (nRet == SOCKET_ERROR)
        {
            printf("sendto() failed: %d\n", WSAGetLastError());
            return -1;
        }

        // Recv
        nRet = recvfrom(sRaw, recvBuf, 1024, 0, (SOCKADDR *) &from, &nLen);
        if (nRet == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAETIMEDOUT)
            {
                printf("time out\n");
                continue;
            }
            printf("recvfrom() failed: %d\n", WSAGetLastError());
            return -1;
        }

        // Unpack
        int nTick = GetTickCount();
        if (nRet < 20 + sizeof(ICMP_HDR))
        {
            printf("Too few bytes from %s\n", inet_ntoa(from.sin_addr));
            return -1;
        }
        PICMP_HDR pRecvIcmp = (PICMP_HDR)(recvBuf + 20); // size of IP header
        if (pRecvIcmp->icmp_type != 0)
        {
            printf("nonecho type %d received\n", pRecvIcmp->icmp_type);
            return -1;
        }
        if (pRecvIcmp->icmp_id != GetCurrentProcessId())
        {
            printf("someone else's packet!\n");
            return -1;
        }

        printf(" %d types from %s:", nRet, inet_ntoa(from.sin_addr));
        printf(" icmp_seq = %d.", pRecvIcmp->icmp_sequence);
        printf(" time: %d ms\n", nTick - pRecvIcmp->icmp_timestamp);
        Sleep(1000);
    }

    CleanupWinsock();
    return 0;
}
