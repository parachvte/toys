class Solution:
    # @param {integer} n
    # @return {boolean}
    def isPowerOfTwo(self, n):
        if n <= 0:
            return False
        while n > 1 and n % 2 == 0:
            n /= 2
        return n == 1
