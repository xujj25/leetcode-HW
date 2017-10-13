# Best Time to Buy and Sell Stock 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

------

## Description

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), design an algorithm to find the maximum profit.

**Example 1:**
```
Input: [7, 1, 5, 3, 6, 4]
Output: 5

max. difference = 6-1 = 5 (not 7-1 = 6, as selling price needs to be larger than buying price)
```
**Example 2:**
```
Input: [7, 6, 4, 3, 1]
Output: 0

In this case, no transaction is done, i.e. max profit = 0.
```

## Solution
```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty() || prices.size() == 1)
            return 0;

        int i, j, max = 0, low, high;
        int stockCount = prices.size();
        bool flag = false;
        for (i = 0; i < stockCount - 1; i++)
            if (prices[i] < prices[i + 1]) {
                low = i;
                flag = true;
                break;
            }

        if (!flag)
            return 0;

        for (j = stockCount - 1; j >= low + 1; j--)
            if (prices[j] > prices[j - 1]) {
                high = j;
                break;
            }


        for (i = low; i <= high - 1; i++) {
            for (j = i + 1; j <= high; j++) {
                if (max < prices[j] - prices[i])
                    max = prices[j] - prices[i];
            }
        }
        return max;
    }
};
```

------

## 解题描述

这道题一开始想到的就是暴力破解，第一遍交就TLE，看了测例之后通过先分别从前往后和从后往前探测符合要求的买入点和卖出点之后才大大降低了对比的时间。