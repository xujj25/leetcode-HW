# Unique Paths 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/unique-paths/description/

------

## Description

A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?

![example](https://leetcode.com/static/images/problemset/robot_maze.png)

Above is a 3 x 7 grid. How many possible unique paths are there?

**Note:** m and n will be at most 100.

## Solution
```cpp
class Solution {
    int combinatorial(int big, int small) {
        unsigned long long res = 1;
        unsigned long long i = static_cast<unsigned long long>(big - small + 1);
        unsigned long long j = 1;
        for (; i <= big, j <= small; i++, j++) {
            res *= i;
            res /= j;
        }
        return static_cast<int>(res);
    }
public:
    int uniquePaths(int m, int n) {
        return combinatorial(m + n - 2, min(m, n) - 1);
    }
};

```

------

## 解题描述

这道题目其实只需要使用简单的数学求解。机器人每次只能向右或者向下走一步，如果是在m * n的网格中，则向右走要m - 1步，向下走要n - 1步。所以求所有路径的数目其实就是求一个组合数。即在m + n - 2步中取m - 1步。然后主要的问题是计算上面的问题：第一次WA是因为大数计算溢出。于是换了个算法，改成每次乘上一个数之后要除去一个数，而不是连乘后连除；第二次WA是因为从大数方向往小数方向进行计算的时候会出现不能整除的情况，只能是换成从小数向大数进行累积计算。