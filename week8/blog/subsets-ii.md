# Subsets II 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/subsets-ii/description/

------

## Description

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,2], a solution is:
```
[
  [2],
  [1],
  [1,2,2],
  [2,2],
  [1,2],
  []
]
```


## Solution
```cpp
class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        if (nums.empty())
            return result;
        result.resize(1);
        sort(nums.begin(), nums.end());
        int lastNum = nums[0], size = 1;
        int i, j;
        for (i = 0; i < nums.size(); i++) {
            if (lastNum != nums[i]) {
                lastNum = nums[i];
                size = result.size();
            }
            int newResSize = result.size();
            for (j = newResSize - size; j < newResSize; j++) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};
```

------

## 解题描述

这道题是求幂集的升级版：原始集合含有重复元素，生成幂集的过程中要去重。这道题在第一版的算法基础上，对重复数字开始的地方进行区分（记录不应重复添加新数字的集合数目），以避免对前面产生的数组再全部进行新数字的添加而导致重复的集合的出现。