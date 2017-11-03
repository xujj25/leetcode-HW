# Word Break II 题解

题目来源：https://leetcode.com/problems/word-break-ii/description/

------

## Description

Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. You may assume the dictionary does not contain duplicate words.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].

## Solution
```cpp
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        int size = s.size();
        string outputStr;
        vector<string> result;
        vector<bool> flags(size + 1, true);
        dfs(s, 0, wordDict, flags, outputStr, result);
        return result;
    }

    void dfs(string& s, int startIdx, vector<string>& wordDict, vector<bool>& flags, string& outputStr, vector<string>& result) {
        int size = s.size();
        if (startIdx == size) {
            result.push_back(outputStr.substr(0, outputStr.size() - 1));
            return;
        }

        for (int i = startIdx; i < size; i++) {
            string tempSubStr = s.substr(startIdx, i + 1 - startIdx);
            if (find(wordDict.begin(), wordDict.end(), tempSubStr) != wordDict.end() && flags[i + 1]) {
                outputStr += tempSubStr + " ";
                int preSize = result.size();
                dfs(s, i + 1, wordDict, flags, outputStr, result);
                if (preSize == result.size())
                    flags[i + 1] = false;
                outputStr.resize(outputStr.size() - tempSubStr.size() - 1);
            }
        }
    }
};
```

------

## 解题描述

这道题虽然表面上是第一道Word Break的升级版，但是不同于第一道，这道题使用动态规划可能会出现问题。刚开始做的时候我就想着改用第一道题的做法就好，但是几次提交都是MLE；修改了代码，减少了变量的使用之后，在后面一个比较长的测例上面一直TLE。自己本机上也是运行那个测例的时候被KILL掉，查看系统日志原因仍然是超内存。查阅了一些资料之后才发现，这道题使用动态规划比较繁琐而且效率不高，没有做好剪枝的话还很容易就会出现MLE。结合各种资料重新修改代码，最终还是采用了DFS来解决，并且采用一个`bool`数组`flags`来做剪枝标记。