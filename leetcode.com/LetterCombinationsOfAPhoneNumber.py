class Solution:

    _keyboardMap = {
        '1': '',
        '2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxzy',
        '0': '',
    }

    # @param {string} digits
    # @return {string[]}
    def letterCombinations(self, digits):
        res = ['']

        for d in digits:
            possible = len(self._keyboardMap[d])
            last = res
            res = []
            for key in self._keyboardMap[d]:
                res += [rep + key for rep in last]

        if len(digits) == 0:
            res = []

        return res


if __name__ == '__main__':
    print(Solution().letterCombinations('2338'))
