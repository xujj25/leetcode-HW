# Construct Binary Tree from Inorder and Postorder Traversal 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/

------

## Description

Given inorder and postorder traversal of a tree, construct the binary tree.

**Note:**
You may assume that duplicates do not exist in the tree.

## Solution
```cpp
class Solution {
public:
    TreeNode* getTreeNode(vector<int>& inOrder, vector<int>& postOrder,
                          int inStart, int inEnd, int postStart, int postEnd) {
        TreeNode* resultNode = new TreeNode(postOrder[postEnd]);
        if (postStart == postEnd)
            return resultNode;
        int i;
        int inNodeVal = postOrder[postEnd];
        for (i = inStart; i <= inEnd; i++) {
            if (inNodeVal == inOrder[i])
                break;
        }
        if (i > inStart)
            resultNode -> left =
                    getTreeNode(inOrder, postOrder, inStart, i - 1, postStart, postStart + i - 1 - inStart);
        if (i < inEnd)
            resultNode -> right =
                    getTreeNode(inOrder, postOrder, i + 1, inEnd, postStart + i - inStart, postEnd - 1);
        return resultNode;
    }

    TreeNode* buildTree(vector<int>& inOrder, vector<int>& postOrder) {
        int size = inOrder.size();
        if (size == 0)
            return NULL;
        return getTreeNode(inOrder, postOrder, 0, size - 1, 0, size - 1);
    }
};
```

------

## 解题描述

这道题是经典的树构建问题，通过树的中序遍历和后序遍历结果来重建树，基本的算法是通过每次从后序遍历数组末端取出元素，这个元素为当前树的根，然后再在中序遍历结果中找到这个根，根的两边分别就是左右子树。对左右子树继续递归进行相同的操作，直到数组为空即可。
