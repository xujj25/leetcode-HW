# H-Index题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/h-index/description/

------

## Description

Given an array of citations (each citation is a non-negative integer) of a researcher, write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have **at least** h citations each, and the other N − h papers have **no more than** h citations each."

For example, given citations = [3, 0, 6, 1, 5], which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the researcher has 3 papers with **at least** 3 citations each and the remaining two with **no more than** 3 citations each, his h-index is 3.

**Note:** If there are several possible values for h, the maximum one is taken as the h-index.

## Solution
```c
typedef struct range {
    int start, end;
} range;

range new_range(int s, int e) {
    range r;
    r.start = s;
    r.end = e;
    return r;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quickSort(int arr[], int size) {
    if (size <= 1)
        return;

    range rangeStack[size], tempRange;
    int pos = 0, mid, left, right;
    rangeStack[pos++] = new_range(0, size - 1);
    while (pos) {
        tempRange = rangeStack[--pos];
        if (tempRange.start >= tempRange.end)
            continue;
        left = tempRange.start;
        right = tempRange.end - 1;
        mid = arr[tempRange.end];
        while (left < right) {
            while (arr[left] < mid && left < right)
                left++;
            while (arr[right] >= mid && left < right)
                right--;
            swap(&arr[left], &arr[right]);
        }
        if (arr[left] >= arr[tempRange.end])
            swap(&arr[left], &arr[tempRange.end]);
        else
            left++;
        rangeStack[pos++] = new_range(tempRange.start, left - 1);
        rangeStack[pos++] = new_range(left + 1, tempRange.end);
    }
}

int hIndex(int* citations, int citationsSize) {
    if (citationsSize <= 0)
        return 0;
    int i;
    quickSort(citations, citationsSize);
    for (i = citationsSize - 1; i >= 0; i--) {
        if (citations[i] >= citationsSize - i) {
            if (i == 0) {
                return citationsSize;                
            } else if (citations[i - 1] <= citationsSize - i) {
                return citationsSize - i;
            }
        }
    }
    return 0;
}
```

------

## 解题描述
这道题我考虑的算法是先将给定的数组进行排序，之后再从后往前检测数组，查看是否存在所求的H指数。我的解答中自己写了用迭代实现的快排