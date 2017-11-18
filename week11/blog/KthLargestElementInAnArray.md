# Kth Largest Element in an Array 题解


题目来源：https://leetcode.com/problems/kth-largest-element-in-an-array/description/

------

## Description

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.

**Note:**
You may assume k is always valid, 1 ≤ k ≤ array's length.

## Solution
```cpp
class Solution {
    void heapFixDown(vector<int>& arr, int start, int end) {
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end) {
            if (son + 1 <= end && arr[son] < arr[son + 1])
                son++;
            if (arr[dad] >= arr[son]) {
                return;
            } else {
                swap(arr[dad], arr[son]);
                dad = son;
                son = dad * 2 + 1;
            }
        }
    }

    void makeHeap(vector<int>& arr, int len) {
        for (int i = len / 2 - 1; i >= 0; i--) {
            heapFixDown(arr, i, len - 1);
            // printArr(arr, len);
        }

        // cout << "finish makeHeap" << endl;
    }

    void heapSort(vector<int>& arr, int len) {        
        makeHeap(arr, len);

        for (int i = len - 1; i >= 1; i--) {
            swap(arr[i], arr[0]);
            heapFixDown(arr, 0, i - 1);
            // printArr(arr, len);
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        heapSort(nums, len);
        return nums[len - k];
    }
};
```

------

## 解题描述

这道题我的基本思路是先对数组进行排序然后再直接获得K大的元素。排序部分使用了堆排序。

堆排序的关键步骤包含：
1. 堆化数组（将数组在树中每一对父子之间都满足父亲大于儿子的要求，根节点一定是最大的数字）
2. 建立最小堆（每次将根节点与最后的节点进行交换，然后将堆中最后的节点前面的节点进行堆化调整，使得每次调整完之后剩余堆中最大的数字“上浮”到根节点）
