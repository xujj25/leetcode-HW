# Word Break 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/word-break/description/

------

## Description

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words. You may assume the dictionary does not contain duplicate words.

For example, given
s = "leetcode",
dict = ["leet", "code"].

Return true because "leetcode" can be segmented as "leet code".

## Solution
```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int i, j;
        int size = s.length();
        vector<bool> flags(size + 1, false);
        flags[0] = true;
        for (i = 0; i <= size; i++) {
            for (j = 0; j <= i - 1; j++) {
                if (flags[j] && find(wordDict.begin(), wordDict.end(), s.substr(j, i - j)) != wordDict.end()) {
                    flags[i] = true;
                    break;
                }
            }
        }
        return flags[size];
    }
};
```

------

## 解题描述

这道题采用的是动态规划的方式进行求解。将整个问题化成小问题：生成来源字符串的所有子串，并在词典中查找字串，如果存在则进行标记，之后查看所有的这些字串能否连起来组成原来的字符串。