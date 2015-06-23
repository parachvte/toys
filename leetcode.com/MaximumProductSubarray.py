# https://oj.leetcode.com/problems/maximum-product-subarray/
#
# 智商捉急，居然写了这么复杂的东西……
# 先把元数组以0为分隔分成几段，然后每段基于负数的个数去算最大积

class Solution:
    # @param A, a list of integers
    # @return an integer
    def maxProduct(self, A):
        n = len(A)
        maxValue = max(A)

        start = 0
        while start < n:
            i = start
            B = []
            while i < n and A[i]:
                B.append(A[i])
                i += 1
            while i < n and not A[i]:
                i += 1
            start = i

            maxValue = max(maxValue, self.maxProduct_v2(B))
        return maxValue

    def maxProduct_v2(self, A):
        if not A:
            return -10**9
        neg = 0
        for i in A:
            if i < 0:
                neg += 1
        if neg % 2 == 0:
            multi = 1
            for i in A:
                multi *= i
            return multi
        else:
            multi1 = 1
            count = neg_count = 0
            for i in A:
                if i < 0:
                    neg_count += 1
                    if neg_count == neg and count:
                        break
                multi1 *= i
                count += 1
            multi2 = 1
            count = neg_count = 0
            for i in reversed(A):
                if i < 0:
                    neg_count += 1
                    if neg_count == neg and count:
                        break
                multi2 *= i
                count += 1
            return max(multi1, multi2)


print(
    Solution().maxProduct([2, 3, -2, 4]),
    Solution().maxProduct([2, 4, 0, 4]),
    Solution().maxProduct([2, 3, -2, 4, -1]),
    Solution().maxProduct([-2]),
    Solution().maxProduct([0]),
    Solution().maxProduct([6, 3, -10, 0, 2]),
)

