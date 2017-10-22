# Jump Game 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/jump-game/description/

------

## Description

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

For example:
A = [2,3,1,1,4], return true.

A = [3,2,1,0,4], return false.



## Solution
```cpp
class Solution {
private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        if (size == 0)
            return false;
        if (size == 1)
            return true;
        if (nums[0] >= size - 1)
            return true;

        int* farthestPoint = new int[size];
        farthestPoint[0] = nums[0];
        for (int i = 1; i < size; i++) {
            if (i <= farthestPoint[i - 1]) {
                farthestPoint[i] = max(farthestPoint[i - 1], i + nums[i]);
            } else {
                delete []farthestPoint;
                return false;
            }
        }
        bool result = farthestPoint[size - 2] >= size - 1;
        delete [] farthestPoint;
        return result;

    }
};
```

------

## 解题描述

这道题我使用的是贪心算法，通过遍历nums来更新每一个点上能够达到的最远点，最终判断是否能够达到终点。
