/**
 * UDP port scanner
 *
 * Author: Ryannnnnnn (ryannx6@gmail.com)
 *
 * How to use:
 *  gcc udp_port_scanner.c -o udp_port_scanner
 *  sudo ./udp_port_scanner [target_host] [target_port]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
//#include <netdb.h>

#include <net/if.h>

#include <pthread.h>

/* IP Header, copy from Linux TCP/IP implementation `netinet/ip.h` */
struct iphdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int ihl:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int ihl:4;
#else
# error "Please fix <bits/endian.h>"
#endif
    u_int8_t tos;
    u_int16_t tot_len;
    u_int16_t id;
    u_int16_t frag_off;
    u_int8_t ttl;
    u_int8_t protocol;
    u_int16_t check;
    u_int32_t saddr;
    u_int32_t daddr;
    /*The options start here. */
};

/* ICMP Header, copy from Linux TCP/IP implementation `netinet/ip.h` */
struct icmphdr
{
    u_int8_t type;        /* message type */
    u_int8_t code;        /* type sub-code */
    u_int16_t checksum;
    union
    {
        struct
        {
            u_int16_t id;
            u_int16_t sequence;
        } echo;         /* echo datagram */
        u_int32_t   gateway;    /* gateway address */
        struct
        {
            u_int16_t _unused; // `__unused` -> `_unused`
            u_int16_t mtu;
        } frag;         /* path mtu discovery */
    } un;
};


/* State */
enum PORTSTATE
{
    PORTOPEN = 0,
    PORTUNKNOWN
};

#define BUFFER_SIZE 1000

int sniffer_ready, sniffer_finish;
char recv_buffer[BUFFER_SIZE];
int port_open;

char *device = "en0";
char *myip = "172.20.250.21";
char host[20];
uint16_t port;


int checkICMP(const struct iphdr *ip_header)
{
    struct icmphdr *icmp_header = (struct icmphdr *) (ip_header + 1);
    struct iphdr *original_ip_hdr;

    if (icmp_header->type != 3) return -1; // Destination unreachable
    if (icmp_header->code != 3) return -1;

    original_ip_hdr = (struct iphdr*) ((char *) icmp_header + sizeof(struct icmphdr));
    if (original_ip_hdr->protocol != 0x11) return -1; // UDP
    if (original_ip_hdr->saddr != inet_addr(myip)) return -1;
    if (original_ip_hdr->daddr != inet_addr(host)) return -1;

    return 0; // NOT OPEN
}

void *icmp_sniffer(void *arg)
{
    int sockfd;
    int flag;
    struct sockaddr_in local_addr;

    // Create raw socket on ICMP
    //if ((sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_IP)) == -1) // On CentOS 7, when using `IPPROTO_IP`,
                                                                  // error `protocol not supported` occurs
    if ((sockfd = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1) // Note that IPPROTO_RAW doesn't work
    {
        perror("socket() error\n");
        sniffer_ready = 1;
        return NULL;
    }

    // Setup local address
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = INADDR_ANY;
    memset(&(local_addr.sin_zero), 0, 8);
    
    /* TODO: how to detect the IP corresponding to `device`
    char hostname[100];
    if (gethostname(hostname, sizeof hostname) == -1)
    {
        perror("socket() error\n");
        sniffer_ready = -1;
        return NULL;
    }
    printf("My hostname: %s\n", hostname);

    struct hostent *hostinfo;
    if ((hostinfo = gethostbyname(hostname)) == NULL)
    {
        perror("unknown host");
        sniffer_ready = -1;
        return NULL;
    }
    printf("My IP: %s\n", inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list));
    local_addr.sin_addr = *(struct in_addr *) hostinfo->h_addr;
    */
    // TODO: deal with this
    local_addr.sin_addr.s_addr = inet_addr(myip);

    // Once the service is down, we should wait for the port to clear,
    // or just call setsockopt() to reuse the port
    flag = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) == -1)
    {
        perror("setsockopt() error");
        close(sockfd);
        sniffer_ready = -1;
        return NULL;
    }

    // IP header included
    flag = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &flag, sizeof(int)) == -1)
    { 
        perror("setsockopt() error");
        close(sockfd);
        sniffer_ready = -1;
        return NULL;
    }

    // Receive all traffic (turn on promisc mode, `if_promisc_on`)
    struct ifreq ifr;
    strncpy(ifr.ifr_name, device, IFNAMSIZ);
    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr) == -1)
    {
        perror("ioctl(SIOCGIFFLAGS) 1 error");
        close(sockfd);
        sniffer_ready = -1;
        return NULL;
    }

    if (!(ifr.ifr_flags & IFF_PROMISC))
    {
        ifr.ifr_flags |= IFF_PROMISC;
        if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) == -1)
        {
            perror("ioctl(SIOCSIFFLAGS) 2 error");
            close(sockfd);
            sniffer_ready = -1;
            return NULL;
        }
    }

    // Bind local address
    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof (struct sockaddr)) == -1)
    {
        perror("bind() error\n");
        close(sockfd);
        sniffer_ready = -1;
        return NULL;
    }

    listen(sockfd, 10);

    sniffer_ready = 1;

    // Start to sniff!
    struct sockaddr_in *source_addr;
    socklen_t fromlen;
    while (!sniffer_finish)
    {
        int len = recvfrom(sockfd, recv_buffer, BUFFER_SIZE, 0, (struct sockaddr *) &source_addr, &fromlen);
        printf("recv data: length = %d\n", len);
        if (len < 42) {
            /* + 14 (source dest type)
             * + 20 (ip header)
             * + 8 (icmp, udp, tcp header)
             * = 42
             */
            printf("Incomplete header, packet corrupt\n");
            continue;
        }

        struct iphdr *ip_header = (struct iphdr *) recv_buffer;
        printf("(protocol = %x, saddr = %x, daddr = %x)\n", ip_header->protocol, ip_header->saddr, ip_header->daddr);
        switch (ip_header->protocol)
        {
            case IPPROTO_ICMP:
            {
                int ret = checkICMP(ip_header);
                if (ret == 0) // receive ICMP response means NOT OPEN
                {
                    port_open = 0;
                    sniffer_finish = 1;
                    return NULL;
                }
                break;
            }
            case IPPROTO_UDP:
                // Here I can't receive UDP packets...confused
                break;
            defalt:
                printf("receive protocol: %x\n", ip_header->protocol);
                break;
        }
        printf("\n");
    }

    return NULL;
}

/* Check UDP port */
int check_udp_port(const char *host, uint16_t port)
{
    int retval = PORTUNKNOWN;

    sniffer_ready = sniffer_finish = 0;

    // Start ICMP sniffer
    int err;
    pthread_t tid;
    if ((err = pthread_create(&tid, NULL, &icmp_sniffer, NULL)) != 0)
    {
        perror("can't create thread\n");
        return retval;
    }
    while (!sniffer_ready) usleep(50);
    if (sniffer_ready == -1) return retval;
    printf("Sniffer started\n");

    // Send a UDP packet to see if any ICMP response
    printf("Starting scanner\n");
    struct sockaddr_in dest_addr;
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(host);

    int sockfd;
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("scanner failed: socket()");
        return retval;
    }

    if (connect(sockfd, (struct sockaddr *) &dest_addr, sizeof(struct sockaddr)) == -1) {
        perror("scanner failed: connect()");
        close(sockfd);
        return retval;
    }

    char *message = "Hello?";
    port_open = 0;
    send(sockfd, message, sizeof message, 0);

    int count = 0;
    while (!sniffer_finish)
    {
        // Wait for 1s or more but not response, then the port is considered open
        if (++count == 10)
        {
            port_open = 1;
            break;
        }
        usleep(100000);
    }

    if (port_open)
        retval = PORTOPEN;

    close(sockfd);
    return retval;
}

int main(int argc, char *argv[])
{
    if (argc <= 2) return -1;

    strcpy(host, argv[1]);
    port = atoi(argv[2]);

    int result = check_udp_port(host, port);
    printf("Port %d, result = %s\n", port, result == PORTUNKNOWN ? "closed" : "open");

    return 0;
}
