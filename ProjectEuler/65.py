""" Problem 65
    Use module fractions.Fraction
    not efficent but intuitive :(
"""
from fractions import Fraction


def get(n):
    if n == 1:
        return Fraction(2)
    k = n / 3
    res = Fraction(2 * k if n % 3 == 0 else 1)
    for i in range(n - 1, 1, -1):
        if i % 3 == 0:
            res = 2 * k + 1 / res
            k -= 1
        else:
            res = 1 + 1 / res
    return 2 + 1 / res

print sum(int(i) for i in str(get(100).numerator))
