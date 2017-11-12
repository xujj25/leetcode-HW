# 01 Matrix 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/01-matrix/description/

------

## Description
Given a matrix consists of 0 and 1, find the distance of the nearest 0 for each cell.

The distance between two adjacent cells is 1.

**Example 1:**

Input:

```
0 0 0
0 1 0
0 0 0
```

Output:

```
0 0 0
0 1 0
0 0 0
```
**Example 2:**

Input:

```
0 0 0
0 1 0
1 1 1
```

Output:

```
0 0 0
0 1 0
1 2 1
```

## Solution
```cpp
class Solution {
private:
    struct vertex
    {
        int r, c;
        vertex(int _r, int _c) : r(_r), c(_c) {}
    };
    int row, col;
    vector<vector<int> > res;
public:
    bool isValid(int r, int c) {
        return r >= 0 && r < row && c >= 0 && c < col;
    }

    void insertQ(queue<vertex>& q, int r, int c, int val) {
        if (!isValid(r, c))
            return;
        if (res[r][c] == -1) {
            res[r][c] = val + 1;
            q.push(vertex(r, c));
        } else if (res[r][c] > val + 1) {
            res[r][c] = val + 1;
        }
    }

    vector<vector<int> > updateMatrix(vector<vector<int> >& A) {
        this -> row = A.size();
        this -> col = A[0].size();
        vector<int> rowvec(col, -1);
        vector<vector<int> > resRef(row, rowvec);
        this -> res = resRef;
        int i, j;
        queue<vertex> q;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (A[i][j] == 0) {
                    res[i][j] = 0;
                    q.push(vertex(i, j));
                }
            }
        }

        while (!q.empty()) {
            vertex v = q.front();
            q.pop();
            int val = res[v.r][v.c];
            insertQ(q, v.r + 1, v.c, val);
            insertQ(q, v.r - 1, v.c, val);
            insertQ(q, v.r, v.c + 1, val);
            insertQ(q, v.r, v.c - 1, val);
        }
        return res;
    }
};
```

------

## 解题描述

这道题是典型的搜索类问题，我采用了BFS，从为0的顶点开始，逐步更新临近圈层的步数直到矩阵中所有的点的步数都计算出来。