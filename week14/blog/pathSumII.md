# Path Sum II 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/path-sum-ii/description/

------

## Description

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

## Example

Given the below binary tree and `sum = 22`

```plain

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

```

return

```plain

[
   [5,4,11,2],
   [5,8,4,5]
]

```

## Solution
```cpp
class Solution {
    void dfs(vector<vector<int>>& res, vector<int>& path, TreeNode* root, int sum) {
        if (root -> left == NULL && root -> right == NULL) {
            if (sum == root -> val) {
                path.push_back(root -> val);
                res.push_back(path);
                path.pop_back();
            }
            return;
        }
        if (root -> left != NULL) {
            path.push_back(root -> val);
            dfs(res, path, root -> left, sum - (root -> val));
            path.pop_back();
        }
        if (root -> right != NULL) {
            path.push_back(root -> val);
            dfs(res, path, root -> right, sum - (root -> val));
            path.pop_back();
        }
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;
        vector<int> path;
        dfs(res, path, root, sum);
        return res;
    }
};
```

------

## 解题描述

这道题目题意是，在一棵二叉树中，寻找一个从根节点到叶子节点的路径，使得路径上的数字之和为给定的数字sum，要求找出所有这样的路径。当然最容易想到的就是使用DFS来解决。