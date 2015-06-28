class Solution:
    """
    @param {string} s
    @return {string[]}
    """
    def findRepeatedDnaSequences(self, s):
        count = {}
        len_s = len(s)
        for i in range(0, len_s - 9):
            subs = s[i: i + 10]
            if not count.get(subs):
                count[subs] = 1
            else:
                count[subs] += 1

        res = []
        for key, value in count.items():
            if value >= 2:
                res.append(key)

        return res

print Solution().findRepeatedDnaSequences("AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT")
