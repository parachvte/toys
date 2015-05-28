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
    map<pair<int, int>, vector<TreeNode*> > calculatedTrees;

    vector<TreeNode*> genTrees(int start, int end) {
        pair<int, int> key = make_pair(start, end);
        if (calculatedTrees.count(key)) {
            return calculatedTrees[key];
        }
        vector<TreeNode*> trees;
        if (start > end) {
            trees.push_back(NULL);
        } else {
            for (int rootVal = start; rootVal <= end; ++ rootVal) {
                vector<TreeNode*> leftTrees = genTrees(start, rootVal - 1);
                vector<TreeNode*> rightTrees = genTrees(rootVal + 1, end);
                
                for (vector<TreeNode*>::iterator leftIt = leftTrees.begin(); leftIt != leftTrees.end(); ++ leftIt) {
                    for (vector<TreeNode*>::iterator rightIt = rightTrees.begin(); rightIt != rightTrees.end(); ++ rightIt) {
                        TreeNode *root = new TreeNode(rootVal);
                        root->left = *leftIt;
                        root->right = *rightIt;
                        trees.push_back(root);
                    }
                }
            }
        }
        
        return calculatedTrees[key] = trees;
    }

    vector<TreeNode*> generateTrees(int n) {
        return genTrees(1, n);
    }
};