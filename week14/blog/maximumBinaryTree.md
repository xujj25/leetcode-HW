# Maximum Binary Tree 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/maximum-binary-tree/description/

------

## Description

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

1. The root is the maximum number in the array.
2. The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
3. The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.

Construct the maximum tree by the given array and output the root node of this tree.

## Example

```plain
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
```

**Note:** The size of the given array will be in the range [1,1000].

## Solution
```cpp
class Solution {
public:
    TreeNode* getSubTree(vector<int>& nums, int start, int end) {
        TreeNode* resultNode;
        if (start == end) {
            resultNode = new TreeNode(nums[start]);
            return resultNode;
        }
        int maxIdx = start;
        int i;
        for (i = start; i <= end; i++) {
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }
        resultNode = new TreeNode(nums[maxIdx]);
        if (maxIdx > start) {
            resultNode -> left = getSubTree(nums, start, maxIdx - 1);
        }
        if (maxIdx < end) {
            resultNode -> right = getSubTree(nums, maxIdx + 1, end);
        }
        return resultNode;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty())
            return NULL;
        return getSubTree(nums, 0, nums.size() - 1);
    }
};
```

------

## 解题描述

这道题的题意是，对给定的一个数组，构造一棵所谓的“最大二叉树”。很容易想到的就是使用递归的思想，每次都对数组的一段进行处理，找出数组段中最大的元素，将该元素所谓当前树的树根，对元素左右两边两个数组段分别构造“最大二叉树”，分别作为树根的左子树和右子树。