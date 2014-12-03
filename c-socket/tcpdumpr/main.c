#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include <winsock2.h>
#include <mstcpip.h>
#include <mswsock.h>

#include "initsock.h"
#include "tcpip.h"


void print_time()
{
    struct timeval tv;
    struct timezone tz;
    struct tm *tm;
    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);
    printf("%02d:%02d:%02d.%06d", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec);
}

void AnalyzeData(char *pData)
{
    PIP_HEADER pIpHdr = (PIP_HEADER) pData;

    char szSourceIp[32], szDestIp[32];

    strcpy(szSourceIp, inet_ntoa(pIpHdr->ip_src));
    strcpy(szDestIp, inet_ntoa(pIpHdr->ip_dst));

    switch (pIpHdr->ip_p)
    {
    case IPPROTO_ICMP:
        printf(" IP %s > %s, ICMP", szSourceIp, szDestIp); break;
    case IPPROTO_IGMP:
        printf(" IP %s > %s, IGMP", szSourceIp, szDestIp); break;
    case IPPROTO_TCP:
        {
            unsigned short nSourcePort, nDestPort;
            PTCP_HEADER pTcpHdr = (PTCP_HEADER) (pData + ((pIpHdr->ip_vhl & 0xf) << 2));
            nSourcePort = ntohs(pTcpHdr->th_sport);
            nDestPort = ntohs(pTcpHdr->th_dport);
            printf(" IP %s.%d > %s.%d, TCP", szSourceIp, nSourcePort, szDestIp, nDestPort);

            switch (nDestPort)
            {
            case 21:    printf(" (FTP)");       break;
            case 22:    printf(" (FTP)");       break;
            case 23:    printf(" (telnet)");    break;
            case 25:    printf(" (SMTP)");      break;
            case 43:    printf(" (WHOIS)");     break;
            case 80:    printf(" (HTTP)");      break;
            case 110:   printf(" (POP3)");      break;
            case 143:   printf(" (IMAP)");      break;
            case 443:   printf(" (HTTPS)");     break;
            case 843:   printf(" (Adobe Flash)"); break;
            case 993:   printf(" (IMAP - SSL)"); break;
            case 995:   printf(" (POP3 - SSL)"); break;
            case 1433:  printf(" (MSSQL)");     break;
            case 2082:  printf(" (cPanel)");    break;
            case 3306:  printf(" (MySQL)");     break;
            default:    printf(" %d", nDestPort); exit(-1); break;
            }
        }
        break;
    case IPPROTO_UDP:
        {
            unsigned short nSourcePort, nDestPort;
            PUDP_HEADER pUdpHdr = (PUDP_HEADER) (pData + ((pIpHdr->ip_vhl & 0xf) << 2));
            nSourcePort = ntohs(pUdpHdr->uh_sport);
            nDestPort = ntohs(pUdpHdr->uh_dport);
            printf(" IP %s.%d > %s.%d, UDP", szSourceIp, nSourcePort, szDestIp, nDestPort);
            switch (nDestPort)
            {
            case 53:    printf(" (DNS)");   break;
            case 80:    printf(" (HTTP)");  break;
            case 137:   printf(" (NetBIOS NS)");    break;
            case 443:   printf(" (QUIC)");  break;
            case 5355:  printf(" (LLMNR)"); break;
            default:    printf(" %d", nDestPort); exit(-1); break;
            }
        }
        break;
    /*case IPPROTO_IPV6:
        printf(" IP %s > %s, IPv6", szSourceIp, szDestIp); break;
    case IPPROTO_ICMPV6:
        printf(" IP %s > %s, ICMPv6", szSourceIp, szDestIp); break;*/
    default:
        printf(" IP %s > %s, protocol = %d", szSourceIp, szDestIp, pIpHdr->ip_p); break;
    }
    printf(" len = %d", pIpHdr->ip_len);
}

#define BUFFER_SIZE 65536
char buff[BUFFER_SIZE];

int main()
{
    InitWinsock();

    /* Create a raw socket descriptor */
    SOCKET sRaw = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
    if (sRaw == INVALID_SOCKET)
    {
        printf("socket() failed: %s\n", GetLastError());
        return 0;
    }

    /* Get local host & bind it to socket descriptor */
    char hostname[56];
    if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
    {
        printf("gethostname() failed: %s\n", GetLastError());
        return 0;
    }
    struct hostent *pHost;
    if ((pHost = gethostbyname(hostname)) == NULL)
    {
        printf("gethostbyname() failed: %s\n", GetLastError());
        return 0;
    }

    SOCKADDR_IN local_addr;
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(0);
    memcpy(&local_addr.sin_addr.S_un.S_addr, pHost->h_addr_list[0], pHost->h_length);

    if (bind(sRaw, (PSOCKADDR) &local_addr, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        printf("bind() failed: %s\n", GetLastError());
        return 0;
    }

    /* Promiscuous mode */
    DWORD dwValue = 1;
    if (ioctlsocket(sRaw, SIO_RCVALL, &dwValue) != 0)
    {
        printf("ioctlsocket() set to SIO_RCVVAL failed: %s\n", GetLastError());
        return 0;
    }

    printf("tcpdumpr: dump traffic on a network (by Ryannnnnnn)\n");
    printf("listening on interface: %s, capture size %d bytes\n", inet_ntoa(local_addr.sin_addr), BUFFER_SIZE);
    while (TRUE)
    {
        int nLen = recv(sRaw, buff, BUFFER_SIZE, 0);
        if (nLen > 0)
        {
            print_time();
            AnalyzeData(buff);
            printf("\n");
        }
    }
    closesocket(sRaw);

    CleanupWinsock();
    return 0;
}
