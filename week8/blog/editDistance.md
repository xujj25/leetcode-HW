# Edit Distance 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/edit-distance/description/

------

## Description

Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character


## Solution
```cpp
class Solution {
    public:
    int minDistance(string word1, string word2) {
        if (word1 == word2)
            return 0;
        if (word1.empty())
            return word2.length();
        if (word2.empty())
            return word1.length();

        int len1 = word1.length() + 1;
        int len2 = word2.length() + 1;
        int** f = new int*[len1];
        int i, j;
        for (i = 0; i < len1; i++) {
            f[i] = new int[len2];
            f[i][0] = i;
        }

        for (j = 0; j < len2; j++) {
            f[0][j] = j;
        }

        for (i = 1; i < len1; i++) {
            for (j = 1; j < len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    f[i][j] = f[i - 1][j - 1];
                } else {
                    f[i][j] = min(min(f[i - 1][j] + 1, f[i][j - 1] + 1), f[i - 1][j - 1] + 1);
                }                
            }
        }
        int res = f[len1 - 1][len2 - 1];

        for (i = 0; i < len1; i++)
            delete [] f[i];
        delete [] f;

        return res;
    }
};
```

------

## 解题描述

这道题是动态规划中经典的编辑距离问题，关键之处在于将求算总的编辑的距离这个大问题转换成每一步比较两个字符串中指定位置上的字符的时候应该得到的编辑距离`f[i][j]`。增加、删除、替换都是相对上一步编辑距离+1，那关键就是上一步应该选择哪一步？很明显就是选择之前的编辑距离最少的一步，即`f[i][j] = min(min(f[i - 1][j] + 1, f[i][j - 1] + 1), f[i - 1][j - 1] + 1)`的意义；如果指定位上的字符相等，那显然就有`f[i][j] = f[i - 1][j - 1]`。