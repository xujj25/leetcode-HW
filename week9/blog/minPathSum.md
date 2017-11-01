# Minimum Path Sum 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/minimum-path-sum/description/

------

## Description

Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

**Note:** You can only move either down or right at any point in time.

**Example 1:**
```
[[1,3,1],
 [1,5,1],
 [4,2,1]]
```

Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the sum.

## Solution
```cpp
class Solution {
public:
    int minPathSum(vector<vector<int> >& grid) {
        if (grid.empty())
            return 0;
        int i, j;
        int rowCount = grid.size();
        int colCount = grid[0].size();
        int **stepCount;
        stepCount = new int*[rowCount];

        stepCount[0] = new int[colCount];
        stepCount[0][0] = grid[0][0];
        for (i = 1; i < rowCount; i++) {
            stepCount[i] = new int[colCount];
            stepCount[i][0] = grid[i][0] + stepCount[i - 1][0];
        }
        for (j = 1; j < colCount; j++) {
            stepCount[0][j] = grid[0][j] + stepCount[0][j - 1];
        }

        for (i = 1; i < rowCount; i++) {
            for (j = 1; j < colCount; j++) {
                stepCount[i][j] = min(stepCount[i - 1][j], stepCount[i][j - 1]) + grid[i][j];
            }
        }
        j = stepCount[rowCount - 1][colCount - 1];
        for (i = 0; i < rowCount; i++)
            delete [] stepCount[i];
        delete [] stepCount;
        return j;
    }
};
```

------

## 解题描述

这道题其实本质上类似于经典的动态规划问题中的最小编辑距离问题，大概的方法还是差不多的，通过一个矩阵去计算所有的状态下的步数，最后返回右下角的点的步数即为最小的步数之和。