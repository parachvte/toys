class Solution:
    def getRange(self, start, end):
        if start == end:
            return "{}".format(start)
        else:
            return "{}->{}".format(start, end)

    # @param {integer[]} nums
    # @return {string[]}
    def summaryRanges(self, nums):
        n = len(nums)
        res = []
        if n == 0:
            return []

        lastStart = nums[0]
        for i in range(1, n):
            if nums[i] != nums[i - 1] + 1:
                res.append(self.getRange(lastStart, nums[i - 1]))
                lastStart = nums[i]
        res.append(self.getRange(lastStart, nums[n - 1]))

        return res

# test case
# print Solution().summaryRanges([-1])
