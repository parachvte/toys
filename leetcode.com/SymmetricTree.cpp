/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetricTrees(TreeNode *left, TreeNode *right) {
        if (left == NULL && right == NULL) return true;
        if (left == NULL || right == NULL) return false;
        if (left->val != right->val) return false;
        return isSymmetricTrees(left->left, right->right) && isSymmetricTrees(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) {
        if (root == NULL) return true;
        
        return isSymmetricTrees(root->left, root->right);
    }
};