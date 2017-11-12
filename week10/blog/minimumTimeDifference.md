# Minimum Time Difference 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/minimum-time-difference/description/

------

## Description

Given a list of 24-hour clock time points in "Hour:Minutes" format, find the minimum minutes difference between any two time points in the list.

**Example 1:**


```
Input: ["23:59","00:00"]
Output: 1
```

**Note:**
1. The number of time points in the given list is at least 2 and won't exceed 20000.
2. The input time is legal and ranges from 00:00 to 23:59.


## Solution
```cpp
class Solution {
public:
    void timeConvert(vector<int>& times, vector<string>& timePoints) {
        int size = timePoints.size();
        for (int i = 0; i < size; i++) {
            times[i] = ((timePoints[i][0] - '0') * 10 +
                        (timePoints[i][1] - '0')) * 60 +
                        (timePoints[i][3] - '0') * 10 +
                        (timePoints[i][4] - '0');
        }
    }

    int getDiff(int a, int b) {
        int t = b - a;
        if (t > 720)
            return 1440 - t;
        else
            return t;
    }

    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.empty() || timePoints.size() == 1)
            return 0;
        int size = timePoints.size();
        vector<int> times(size);
        timeConvert(times, timePoints);
        sort(times.begin(), times.end());
        int mind = getDiff(times[0], times[1]);
        int t;
        for (int i = 0; i <= size - 2; i++) {
            t = getDiff(times[i], times[i + 1]);
            if (t < mind)
                mind = t;
        }
        t = getDiff(times[0], times[size - 1]);
        if (t < mind)
            mind = t;
        return mind;
    }
};
```

------

## 解题描述

这道题考察的主要是字符串的比较处理，相对简单，主要问题在于时间字符串与时间数值之间的转换。