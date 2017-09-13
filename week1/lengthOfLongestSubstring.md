# Longest Substring Without Repeating Characters题解

题目来源：https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

------

## Description

Given a string, find the length of the longest substring without repeating characters..

## Example

```
Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

## Solution
```c
int lengthOfLongestSubstring(char* s) {
    int len = strlen(s);
    if (len == 0)
    	return 0;
    
    int charbucket[300] = {0};
    int startidx, i;
    int maxlen = 1, substrlen = 0;
    for (startidx = 0; startidx < len; startidx++) {
    	memset(charbucket, 0, sizeof(charbucket));
    	for (i = startidx; i < len; i++) {
    		if (charbucket[s[i]] == 0) {
    			charbucket[s[i]] = 1;
    		} else {
    			break;
    		}
    	}
    	substrlen = 0;
    	for (i = 0; i < 300; i++) {
    		if (charbucket[i] == 1)
    			substrlen++;
    	}
    	if (substrlen > maxlen)
    		maxlen = substrlen;
    }
    return maxlen;    
}
```

------

## 解题描述

这道题目的是找到给定字符串最长的子串的长度，且子串的字符不能重复。我的突破口是针对字符不能重复这个点，使用一个类似C++中的布尔数组，记录子串中出现的字符。然后通过不断查找到最长字串的长度更新结果值。