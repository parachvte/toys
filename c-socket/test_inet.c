#include <stdio.h>
#include <arpa/inet.h>

int main() {
    struct in_addr addr;
    addr.s_addr = 0x1f23ab02;

    printf("network address is: %x\n", addr.s_addr);
    printf("local network address is: %x\n", inet_lnaof(addr));
    printf("network number is: %x\n", inet_netof(addr));

    return 0;
}
