# Sort Colors题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/sort-colors/description/

------

## Description

Given an array with n objects colored red, white or blue, sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

Note:
You are not suppose to use the library's sort function for this problem.

## Solution
```C
void sortColors(int* nums, int numsSize) {
    int b[3] = {0};
    int i;
    for (i = 0; i < numsSize; i++)
    	b[nums[i]]++;
    for (i = 0; i < b[0]; i++)
    	nums[i] = 0;
    for (i = b[0]; i < b[0] + b[1]; i++)
    	nums[i] = 1;
    for (i = b[0] + b[1]; i < numsSize; i++)
    	nums[i] = 2;
}
```

------

## 解题描述

这道题一上手想到的解法就是桶排序。因为数字的范围是确定的且较小。但是跑出来的时间挺长的。尝试手写快排看看能不能提速，发现还是差不多的，所以Solution只给出了写起来容易点的桶排序。