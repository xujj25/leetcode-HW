# Palindrome Partitioning 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/palindrome-partitioning/description/

------

## Description

Given a string s, partition s such that every substring of the partition is a palindrome.

Return all possible palindrome partitioning of s.

For example, given s = `"aab"`,
Return
```
[
  ["aa","b"],
  ["a","a","b"]
]
```

## Solution
```cpp
class Solution {
public:
    vector<vector<string>> partition(string s) {
        int len = s.length();
        vector<vector<string>> res;
        vector<string> path;
        dfs(0, s, path, res);
        return res;
    }

    void dfs(int idx, string& str, vector<string>& path, vector<vector<string>>& res) {
        if (idx == str.length()) {
            res.push_back(path);
            return;
        }
        for (int i = idx; i < str.size(); i++) {
            if (isPalindrome(str, idx, i)) {
                path.push_back(str.substr(idx, i - idx + 1));
                dfs(i + 1, str, path, res);

                /* pop back every time in recurse stack,
                 * than all the paces added in dfs can be remove */
                path.pop_back();
            }
        }
    }

    bool isPalindrome(string& str, int start, int end) {
        while (start < end) {
            if (str[start] != str[end]) {
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
};
```

------

## 解题描述

这道题是目的是找到一个字符串中所有由回文子串组成的集合，算法是对给出的字符串进行遍历，查找所有回文子串，对每个回文子串再进行DFS查找新的回文子串，这样就能找到所有由回文子串切分的子串的集合。