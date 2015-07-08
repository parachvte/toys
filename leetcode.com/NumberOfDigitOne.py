class Solution:
    # @param {integer} n
    # @return {integer}
    def countDigitOne(self, n):
        if n <= 0:
            return 0

        f = [[0 for d in range(10)] for l in range(21)]

        f[1][1] = 1
        for l in range(1, 20):
            for d in range(10):
                f[l + 1][d] = (d == 1) * (10 ** l)
                for i in range(10):
                    f[l + 1][d] += f[l][i]

        digits = []
        while n:
            digits.append(n % 10)
            n //= 10

        current = 0
        ans = 0
        while digits:
            for i in range(digits[-1]):
                ans += f[len(digits)][i] + (current * 10 ** (len(digits) - 1))
            current += (digits[-1] == 1)
            del digits[-1]
        ans += current

        return ans

if __name__ == '__main__':
    print(Solution().countDigitOne(110))
    print(Solution().countDigitOne(999))
