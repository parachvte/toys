import math


def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def period(N):
    """ with remainder format (p * sqrt(N) - q) / r, where tpl = (p, q, r)
        repeat calculate a for several times util tuple (p, q, r) appears the 2nd time
        period = time(2nd) - time(1st)
    """
    if int(math.sqrt(N)) * int(math.sqrt(N)) == N:
        return 0
    tuples = {}
    tpl = 1, 0, 1
    count = 0
    while not tpl in tuples:
        tuples[tpl] = count
        p, q, r = tpl
        a = (int(p * math.sqrt(N)) - q) / r
        tpl = r * p, - (r * q + a * r * r), p * p * N - (q + a * r) * (q + a * r)
        d = gcd(tpl[0], gcd(tpl[1], tpl[2]))
        tpl = tuple(map(int, (tpl[0] / d, tpl[1] / d, tpl[2] / d)))
        count += 1
    return count - tuples[tpl]

N = 10000
count = 0
for i in range(1, N + 1):
    if period(i) % 2 == 1:
        count += 1
print count
