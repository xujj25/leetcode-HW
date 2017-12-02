# Search a 2D Matrix 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/search-a-2d-matrix/description/

------

## Description
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

- Integers in each row are sorted from left to right.
- The first integer of each row is greater than the last integer of the previous row.

## Example

For example,

Consider the following matrix:

```plain
[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]
```
Given **target** = `3`, return `true`.


## Solution
```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int size = matrix.size();
        int low = 0, high = size - 1, mid;
        while (low < high) {
            mid = (high + low) / 2;
            if (target == matrix[mid].back())
                return true;
            else if (target < matrix[mid].back())
                high = mid;
            else
                low = mid + 1;
        }
        size = matrix[low].size();
        vector<int>& arr = matrix[low];
        low = 0;
        high = size - 1;
        while (low < high) {
            mid = (high + low) / 2;
            if (target == arr[mid])
                return true;
            else if (target < arr[mid])
                high = mid;
            else
                low = mid + 1;
        }
        return arr[low] == target;
    }
};

```

------

## 解题描述

这道题考察的是二分查找。我选择的算法是先用二分查找确定target在矩阵的哪一行，再在这一行中进行二分查找找出target。不过AC之后想想，其实可以把矩阵直接看成一维数组进行二分查找，只需要多做一步下标转换即可。