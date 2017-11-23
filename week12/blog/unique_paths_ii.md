# Unique Paths II 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/unique-paths-ii/description/

------

## Description

Follow up for "Unique Paths":

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and empty space is marked as 1 and 0 respectively in the grid.

For example,
There is one obstacle in the middle of a 3x3 grid as illustrated below.

```plain
[
    [0, 0, 0],
    [0, 1, 0],
    [0, 0, 0]
]
```

Above is a 3 x 7 grid. How many possible unique paths are there?

**Note:** m and n will be at most 100.

## Solution
```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row = obstacleGrid.size();
        int col = obstacleGrid[0].size();
        int i, j;
        vector<int> dp(col, 0);
        dp[0] = 1;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (obstacleGrid[i][j] == 1)
                    dp[j] = 0;
                else if (j > 0)
                    dp[j] += dp[j - 1];
            }
        }
        return dp[col - 1];
    }
};

```

------

## 解题描述

这道题是第一道题目的升级版，也真正意义上需要使用动态规划来求解。这道题目中动态规划的最小问题是，到达每一个格子的路径数目等于其上方格子的路径数目加上其左侧格子的路径数目，因为robot每次只能像右走或者向下走。所以整道题目看下来还是从上到下从左到右扫描矩阵，如果某个格子有障碍物，这个格子的路径数置为0，这样其正右方、正下方和右下方的所有格子就都不会加上到达这个有障碍的格子的路径数，从而实现去除不能实现的路径数。