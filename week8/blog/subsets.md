# Subsets 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/subsets/description/

------

## Description

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = `[1,2,3]`, a solution is:
```
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```


## Solution
```cpp
class Solution {
public:
    vector< vector<int> > subsets(vector<int>& nums) {
        int size = nums.size(), j;
        unsigned long long bits = 1 << size;
        unsigned long long i;
        vector< vector<int> > result;
        for (i = 0; i < bits; i++) {
            vector<int> temp;
            for (j = 0; j < size; j++) {
                if ((i >> j) & 1)
                    temp.push_back(nums[j]);
            }
            result.push_back(temp);
        }
        return result;
    }
};
```

------

## 解题描述

这道题其实就是简单的求幂集。我使用的是穷举每一位的有无两种情况来构造所有的子集。