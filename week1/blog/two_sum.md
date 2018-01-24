# Two Sum题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/two-sum/description/

------

## Description

Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

## Example

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

## Solution
```c
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int* result = (int*)malloc(2 * sizeof(int));

    int i, j;
    for (i = 0; i < numsSize; i++) {
    	for (j = 0; j < numsSize; j++) {
    		if (i == j) continue;
    		if (nums[i] + nums[j] == target) {
    			if (i < j) {
    				result[0] = i;
    				result[1] = j;
    			} else {
    				result[0] = j;
    				result[1] = i;
    			}
    			return result;
    		}
    	}
    }
    return result;
}
```

------

## 解题描述

这道题目还是比较简单的，为了找到目标数字的下标，使用的是直接用双层循环遍历数组里面任意两个数的和，检查和是否等于给定的target。之后再返回存有所求的两个数字的下标的数组。

**2018.1.24 更新：**

之前这道题的做法属于暴力破解，时间复杂度还是较高的，达到了O(n^2)，查了一些资料之后发现使用哈希可以把时间复杂度降到O(n)：

```cpp

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        int size = nums.size();
        vector<int> res(2);
        for (int i = 0; i < size; i++) {
            auto got = hash.find(target - nums[i]);
            if (got != hash.end()) {
                res[0] = got -> second;
                res[1] = i;
                return res;
            }
            hash[nums[i]] = i;
        }
    }
};


```
