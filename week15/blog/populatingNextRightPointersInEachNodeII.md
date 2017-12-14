# Populating Next Right Pointers in Each Node II 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/

------

## Description

Follow up for problem "Populating Next Right Pointers in Each Node".

What if the given tree could be any binary tree? Would your previous solution still work?

**Note:** You may only use constant extra space.

## Example

Given the following binary tree,

```plain

         1
       /  \
      2    3
     / \    \
    4   5    7

```

After calling your function, the tree should look like:

```plain

         1 -> NULL
       /  \
      2 -> 3 -> NULL
     / \    \
    4-> 5 -> 7 -> NULL

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

    struct LevelNode {
        TreeLinkNode* node;
        int level;
        LevelNode(TreeLinkNode* n, int l) {
            node = n;
            level = l;
        }
    };

    const int InitLevel = 1;
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;
        int curLevel = InitLevel;
        vector<TreeLinkNode*> v;
        queue<LevelNode> q;
        q.push(LevelNode(root, InitLevel));
        while (!q.empty()) {
            LevelNode ln = q.front();
            q.pop();
            if (ln.node -> left != NULL) {
                q.push(LevelNode(ln.node -> left, ln.level + 1));
            }
            if (ln.node -> right != NULL) {
                q.push(LevelNode(ln.node -> right, ln.level + 1));
            }
            if (ln.level != curLevel) {
                connectNode(v);
                v.clear();
                curLevel++;
            }
            v.push_back(ln.node);
        }
        connectNode(v);
    }
};

```

------

## 解题描述

这道题是[Populating Next Right Pointers in Each Node](https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/)的升级版：这道题里面的二叉树不是完全二叉树，所以每一层的节点数目没有办法提前计算。我想到的算法是，使用一个新的结构体来记录队列中的节点，然后这个结构体中包含另外一个属性——即层次编号。通过层次编号来区分不同层次的节点，在层次编号发生变化的时候对当前层次记录表中的节点进行next连接即可。