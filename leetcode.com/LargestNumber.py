class Solution:
    # @param {integer[]} nums
    # @return {string}
    def largestNumber(self, nums):
        res = ''
        while len(nums):
            b = ' '
            for num in nums:
                if str(num) + b > b + str(num):
                    b = str(num)
                    n = num
            nums.remove(n)
            res += b

        res = res.lstrip('0')
        if res == '':
            res = '0'

        return res


if __name__ == '__main__':
    print(Solution().largestNumber([3, 30, 34, 5, 9]))
    print(Solution().largestNumber([1,2,3,4,5,6,7,8,9,0]))
    print(Solution().largestNumber([1,1,1,1,1,]))
    print(Solution().largestNumber([0,0]))

