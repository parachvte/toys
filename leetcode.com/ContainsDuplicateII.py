class Solution:
    # @param {integer[]} nums
    # @param {integer} k
    # @return {boolean}
    def containsNearbyDuplicate(self, nums, k):
        positionMap = {}
        for i, num in enumerate(nums):
            pos = positionMap.get(num)
            if pos is not None and i - pos <= k:
                return True
            positionMap[num] = i
        return False

if __name__ == '__main__':
    t = Solution()
    print(t.containsNearbyDuplicate([1, 1, 2, 4, 5], 1))
    print(t.containsNearbyDuplicate([1, 1, 2, 4, 5], 0))
    print(t.containsNearbyDuplicate([1, -1, 2, 4, 5], 2))
