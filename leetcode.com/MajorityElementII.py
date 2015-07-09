class Solution:
    # @param {integer[]} nums
    # @return {integer[]}
    def majorityElement(self, nums):
        if not nums:
            return []

        c1 = c2 = 0
        for n in nums:
            if c1 == 0:
                c1 = 1
                n1 = n
            elif n == n1:
                c1 += 1
            elif c2 == 0:
                c2 = 1
                n2 = n
            elif n == n2:
                c2 += 1
            else:
                c1 -= 1
                c2 -= 1

        c1 = c2 = 0
        for n in nums:
            if n == n1:
                c1 += 1
            elif n == n2:
                c2 += 1

        res = []
        if c1 * 3 > len(nums):
            res.append(n1)
        if c2 * 3 > len(nums):
            res.append(n2)
        return res

if __name__ == '__main__':
    print(Solution().majorityElement([]))
    print(Solution().majorityElement([1, 2, 3]))
    print(Solution().majorityElement([1, 2, 3, 3]))
