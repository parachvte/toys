# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None


class Solution:
    def dfs(self, node, parent=None):
        if not node:
            return

        node.parent = parent
        node.depth = parent.depth + 1 if parent else 0

        self.dfs(node.left, node)
        self.dfs(node.right, node)

    # @param {TreeNode} root
    # @param {TreeNode} p
    # @param {TreeNode} q
    # @return {TreeNode}
    def lowestCommonAncestor(self, root, p, q):
        self.dfs(root)

        while p != q:
            if p.depth > q.depth:
                p = p.parent
            elif p.depth < q.depth:
                q = q.parent
            else:
                p = p.parent
                q = q.parent

        return p
