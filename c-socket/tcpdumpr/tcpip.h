#ifndef TCPIP_H
#define TCPIP_H

#include <winsock2.h>


typedef struct _IP_HREADER
{
    unsigned char   ip_vhl;     /* version << 4 | header length >> 2 */
    unsigned char   ip_tos;     /* type of service */
    unsigned short  ip_len;     /* total length */
    unsigned short  ip_id;      /* identification */
    unsigned short  ip_off;     /* fragment and offset */
    unsigned char   ip_ttl;     /* time to live */
    unsigned char   ip_p;       /* protocol */
    unsigned short  ip_sum;     /* checksum */
    struct in_addr  ip_src, ip_dst;  /* source and dest address */
} IP_HEADER, *PIP_HEADER;


typedef struct _TCP_HEADER
{
    unsigned short  th_sport;   /* source port */
    unsigned short  th_dport;   /* dest port */
    unsigned int    th_seq;     /* sequence number */
    unsigned int    th_ack;     /* acknowledge number */
    unsigned char   th_lenres;  /* 4-bit header length & 6 bit reserve */
    unsigned char   th_flag;    /* 6-bit flags */
    unsigned short  th_win;     /* window */
    unsigned short  th_sum;     /* checksum */
    unsigned short  th_urp;     /* urgent pointer */
} TCP_HEADER, *PTCP_HEADER;


typedef struct _UDP_HEADER
{
    unsigned short  uh_sport;   /* source port */
    unsigned short  uh_dport;   /* dest port */
    unsigned short  uh_ulen;    /* udp length */
    unsigned short  uh_sum;     /* udp checksum */
} UDP_HEADER, *PUDP_HEADER;

#endif // TCPIP_H
