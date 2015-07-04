# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:

    # @param {TreeNode} root
    # @return {integer}
    def getChildrenCount(self, root):
        if not root:
            return 0

        if hasattr(root, 'childrenCount'):
            return root.childrenCount

        lc = self.getChildrenCount(root.left)
        rc = self.getChildrenCount(root.right)
        root.childrenCount = lc + rc + 1
        return root.childrenCount

    # @param {TreeNode} root
    # @param {integer} k
    # @return {integer}
    def kthSmallest(self, root, k):
        l = root.left
        r = root.right
        lc = self.getChildrenCount(l)
        rc = self.getChildrenCount(r)

        if lc + 1 == k:
            return root.val

        if k <= lc:
            return self.kthSmallest(l, k)
        else:
            return self.kthSmallest(r, k - lc - 1)


if __name__ == '__main__':
    t1 = TreeNode(1)
    t2 = TreeNode(2)
    t1.right = t2

    print("{}th smallest element is: {}".format(1, Solution().kthSmallest(t1, 1)))
    print("{}th smallest element is: {}".format(2, Solution().kthSmallest(t1, 2)))
