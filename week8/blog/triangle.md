# Triangle 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/triangle/description/

------

## Description

Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.

For example, given the following triangle
```
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
```
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).


## Solution
```cpp
class Solution {
public:
    int min(int a, int b) {
        return a < b ? a : b;
    }

    int minimumTotal(vector< vector<int> >& triangle) {
        int size = triangle.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return triangle[0][0];
        int** result = new int*[size];
        int i, j;
        for (i = 0; i < size; i++)
            result[i] = new int[size];
        for (i = 0; i < size; i++)
            result[size - 1][i] = triangle[size - 1][i];
        for (i = size - 2; i >= 0; i--) {
            for (j = 0; j <= i; j++) {
                result[i][j] = min(result[i + 1][j], result[i + 1][j + 1]) + triangle[i][j];
            }
        }

        j = result[0][0];
        for (i = 0; i < size; i++)
            delete [] result[i];
        delete [] result;
        return j;
    }
};
```

------

## 解题描述

这道题是典型的动态规划问题。从最底层开始向上推导，每一步都是求当前的点应该选择什么后续路径才能保证最终的路径权值之和最小。上面是我最开始的解答，时间复杂度为O(n^2)，空间复杂度为O(n^2)。后面重新想了一下，发现其实记录后续路径之和只需要用一维数组就可以了，于是加以修改得到空间复杂度为O(n)的新解：

```cpp
class Solution {
public:
    int min(int a, int b) {
        return a < b ? a : b;
    }

    int minimumTotal(vector< vector<int> >& triangle) {
        int size = triangle.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return triangle[0][0];
        int *result = new int[size];
        int i, j;
        for (i = 0; i < size; i++)
            result[i] = triangle[size - 1][i];
        for (i = size - 2; i >= 0; i--) {
            for (j = 0; j <= i; j++)
                result[j] = min(result[j], result[j + 1]) + triangle[i][j];
        }
        j = result[0];
        delete [] result;
        return j;
    }
};
```
