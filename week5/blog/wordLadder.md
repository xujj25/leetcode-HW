# Word Ladder题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/word-ladder/description/

------

## Description

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

1. Only one letter can be changed at a time.
2. Each transformed word must exist in the word list. Note that beginWord is not a transformed word.

For example,

Given:
beginWord = `"hit"`
endWord = `"cog"`
wordList = `["hot","dot","dog","lot","log","cog"]`
As one shortest transformation is `"hit" -> "hot" -> "dot" -> "dog" -> "cog"`,
return its length `5`.

**Note:**
- Return 0 if there is no such transformation sequence.
- All words have the same length.
- All words contain only lowercase alphabetic characters.
- You may assume no duplicates in the word list.
- You may assume beginWord and endWord are non-empty and are not the same.

**UPDATE (2017/1/20):**
The wordList parameter had been changed to a list of strings (instead of a set of strings). Please reload the code definition to get the latest changes.

## Solution
```cpp
class Solution {
private:
    set<string> isVisited;
    map<string, string> preVertex;
public:
    bool canTrans(string a, string b) {
        int count = 0;
        for (int i = 0; i < a.length(); i++)
            if (a[i] != b[i]) {
                if (count == 0)
                    count++;
                else
                    return false;
            }
        return count == 1;
    }

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (wordList.size() == 0)
            return 0;
        isVisited.insert(beginWord);
        queue<string> vq;
        vq.push(beginWord);
        string qfront;
        bool finish = false;
        while (!finish && !vq.empty()) {
            qfront = vq.front();
            vq.pop();
            for (auto& w: wordList) {
                if (canTrans(qfront, w) && isVisited.count(w) == 0) {
                    isVisited.insert(w);
                    vq.push(w);
                    preVertex[w] = qfront;
                    if (w == endWord) {
                        finish = true;
                        break;
                    }
                }
            }
        }
        if (finish) {
            int len = 1;
            string v = endWord;
            while (v != beginWord) {
                v = preVertex[v];
                len++;
            }
            return len;
        } else {
            return 0;
        }        
    }
};

```

------

## 解题描述
这道题我采用的是BFS去查找指定的终点。同时用一个map来记录每一个已经被搜索的顶点的前一个点。