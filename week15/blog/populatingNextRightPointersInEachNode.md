# Populating Next Right Pointers in Each Node 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/

------

## Description

Given a binary tree

```cpp

struct TreeLinkNode {
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
}

```

Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to `NULL`.

Initially, all next pointers are set to `NULL`.

**Note:**

- You may only use constant extra space.
- You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).


## Example

Given the following perfect binary tree,

```plain

         1
       /  \
      2    3
     / \  / \
    4  5  6  7

```

After calling your function, the tree should look like:

```plain

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \  / \
    4->5->6->7 -> NULL

```


## Solution
```cpp

class Solution {
private:
    void connectNode(vector<TreeLinkNode*>& v) {
        int size = v.size();
        for (int i = 0; i <= size - 2; i++) {
            v[i] -> next = v[i + 1];
        }
    }
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;
        int levelNodeNum = 1;
        int curLevelNodeNum = 0;
        queue<TreeLinkNode*> q;
        vector<TreeLinkNode*> v;
        q.push(root);
        while (!q.empty()) {
            TreeLinkNode* node = q.front();
            q.pop();
            v.push_back(node);
            if (node -> left != NULL)
                q.push(node -> left);
            if (node -> right != NULL)
                q.push(node -> right);
            curLevelNodeNum++;
            if (curLevelNodeNum == levelNodeNum) {
                levelNodeNum *= 2;
                curLevelNodeNum = 0;
                connectNode(v);
                v.clear();
            }
        }
    }
};

```

------

## 解题描述

这道题是关于二叉树层次遍历问题的变种。题目给出的二叉树是完全二叉树，所以可以提前算出每一层的节点数目，因此来说还是相对比较容易的。所以基本的解决办法是，使用一个队列来存放节点。最开始将根节点加入队列。每次从队首取出一个节点，将其子节点加入队尾。然后使用一个计数变量来计算当前层次上已经加入队列的节点数目。一旦达到该层次的节点数目总和就对该层的节点进行next连接。