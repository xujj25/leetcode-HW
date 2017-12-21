# Range Sum Query - Mutable 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/range-sum-query-mutable/description/

------

## Description

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val. 

## Example

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8

## Solution
```cpp

class NumArray {
private:
    vector<int> segTree;
    int size;

    void pushUp(int root) {
        segTree[root] = segTree[root * 2 + 1] + segTree[root * 2 + 2];
    }

    void build(int root, int left, int right, vector<int>& nums) {
        if (left == right) {
            segTree[root] = nums[left];
            return;
        }
        int mid = (left + right) / 2;
        build(root * 2 + 1, left, mid, nums);
        build(root * 2 + 2, mid + 1, right, nums);
        pushUp(root);
    }

    void updateValInInterval(int root, int left, int right, int index, int val) {
        if (left == right) {
            if (index == left) {
                segTree[root] = val;
            }
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            updateValInInterval(root * 2 + 1, left, mid, index, val);
        } else {
            updateValInInterval(root * 2 + 2, mid + 1, right, index, val);
        }
        pushUp(root);
    }

    int queryInInterval(int root, int left, int right, int targetLeft, int targetRight) {
        if (left == targetLeft && right == targetRight) {
            return segTree[root];
        }
        int mid = (left + right) / 2;
        if (targetRight <= mid)
            return queryInInterval(root * 2 + 1, left, mid, targetLeft, targetRight);
        else if (targetLeft >= mid + 1)
            return queryInInterval(root * 2 + 2, mid + 1, right, targetLeft, targetRight);
        else
            return queryInInterval(root * 2 + 1, left, mid, targetLeft, mid) +
                   queryInInterval(root * 2 + 2, mid + 1, right, mid + 1, targetRight);

    }
public:
    NumArray(vector<int> nums) {
        size = nums.size();
        if (size > 0) {
            segTree = vector<int>(size * 3);
            build(0, 0, size - 1, nums);

            // test
            printVec(segTree);
        }
    }

    void update(int i, int val) {
        if (size == 0)
            return;
        updateValInInterval(0, 0, size - 1, i, val);
    }

    int sumRange(int i, int j) {
        if (size == 0)
            return 0;
        return queryInInterval(0, 0, size - 1, i, j);
    }
};

```

------

## 解题描述

这道题是典型的线段树问题，考察了线段树的构建、单节点值更新还有查询三个方面。上面给出来的解法是使用线性数据结构vector来实现线段树的做法。得出这种做法的过程中遇到的问题是，线段树数组长度的定义问题。如果说输入的数组长度为size，则线段树的节点数目确实为 `2 * size - 1` ，但是实际在vector中使用下标访问子节点的时候，如果vector长度定义过短，就会出现越界的问题，这也是在提交中发现Runtime Error。后面使用内存检查工具自己运行了下测试代码就跟踪到错误发生的位置：在线段树插入新的节点的时候出现了越界。但是由于下标的最大值并不是确定的，如果把vector开得比较大，正如上述解答中的是原数组的三倍，却是可以AC，但是却浪费了中间许多空间（实际测试中，vector中间会有一些位置没用到）。

于是想了一下，试着使用链接方式构建线段树，代码如下：
```cpp

class NumArray {
private:
    struct SegmentTreeNode {
        SegmentTreeNode* left;
        SegmentTreeNode* right;
        int val;
        SegmentTreeNode(int x) {
            val = x;
            left = NULL;
            right = NULL;
        }
    };

    int size;
    SegmentTreeNode *segTreeRoot;

    void pushUp(SegmentTreeNode* node) {
        node -> val = node -> left -> val + node -> right -> val;
    }

    SegmentTreeNode* build(int left, int right, vector<int>& nums) {
        if (left == right) {
            return new SegmentTreeNode(nums[left]);
        }
        SegmentTreeNode* node = new SegmentTreeNode(0);
        int mid = (left + right) / 2;
        node -> left = build(left, mid, nums);
        node -> right = build(mid + 1, right, nums);
        pushUp(node);
        return node;
    }

    void updateValInInterval(SegmentTreeNode* node, int left, int right, int index, int val) {
        if (left == right) {
            if (index == left) {
                node -> val = val;
            }
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            updateValInInterval(node -> left, left, mid, index, val);
        } else {
            updateValInInterval(node -> right, mid + 1, right, index, val);
        }
        pushUp(node);
    }

    int queryInInterval(SegmentTreeNode* node, int left, int right, int targetLeft, int targetRight) {
        if (left == targetLeft && right == targetRight) {
            return node -> val;
        }
        int mid = (left + right) / 2;
        if (targetRight <= mid)
            return queryInInterval(node -> left, left, mid, targetLeft, targetRight);
        else if (targetLeft >= mid + 1)
            return queryInInterval(node -> right, mid + 1, right, targetLeft, targetRight);
        else
            return queryInInterval(node -> left, left, mid, targetLeft, mid) +
                   queryInInterval(node -> right, mid + 1, right, mid + 1, targetRight);

    }

    void clearTree(SegmentTreeNode* node) {
        if (node != NULL) {
            clearTree(node -> left);
            clearTree(node -> right);
            delete(node);
        }
    }
public:
    NumArray(vector<int> nums) {
        size = nums.size();
        segTreeRoot = NULL;
        if (size > 0) {
            segTreeRoot = build(0, size - 1, nums);
        }
    }

    void update(int i, int val) {
        if (size == 0)
            return;
        updateValInInterval(segTreeRoot, 0, size - 1, i, val);
    }

    int sumRange(int i, int j) {
        if (size == 0)
            return 0;
        return queryInInterval(segTreeRoot, 0, size - 1, i, j);
    }
    ~NumArray() {
        clearTree(segTreeRoot);
    }
};

```

这样确实是可以节省空间，也省去了对vector长度的考虑，基本的逻辑也是相同的，但是实际提交之后，链接构建的线段树比线性结构的线段树跑出来的时间要长一些。确实，vector的底层是用数组实现，下标访问的速度肯定是要比链接构建的树要快。所以这里就需要权衡时间和空间的成本了。