#ifndef ICMP_H
#define ICMP_H

typedef struct _icmp_hdr
{
    unsigned char   icmp_type;
    unsigned char   icmp_code;
    unsigned short  icmp_checksum;
    unsigned short  icmp_id;
    unsigned short  icmp_sequence;
    unsigned long   icmp_timestamp;
} ICMP_HDR, *PICMP_HDR;


/**
 * Compute Internet Checksum for "count" bytes,
 * beginning at location "addr".
 */
unsigned short checksum(unsigned short *addr, int count)
{
    unsigned long sum = 0;

    while (count > 1)
    {
        sum += *((unsigned short *) addr++);
        count -= 2;
    }

    // Add left-over byte, if any
    if (count > 0)
        sum += *((unsigned short *) addr);

    // Fold 32-bit sum to 16-bit
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}

#endif // ICMP_H
