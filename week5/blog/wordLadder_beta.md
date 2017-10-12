# Word Ladder II 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/word-ladder-ii/description/

------

## Description

Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

1. Only one letter can be changed at a time.
2. Each transformed word must exist in the word list. Note that *beginWord* is not a transformed word.

For example,

Given:
beginWord = `"hit"`

endWord = `"cog"`

wordList = `["hot","dot","dog","lot","log","cog"]`

Return
```
  [
    ["hit","hot","dot","dog","cog"],
    ["hit","hot","lot","log","cog"]
  ]
```

**Note:**
- Return an empty list if there is no such transformation sequence.
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
    map<string, int> isVisited;
    map<string, vector<string>> preVertex;
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

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> resultLists;
        vector<string> adjacentWordOfEnd;
        if (wordList.size() == 0)
            return resultLists;

        bool endWordExist = false;
        for (auto& w: wordList)
            if (w == endWord) {
                endWordExist = true;
                break;
            }
        if (!endWordExist)
            return resultLists;

        isVisited[beginWord] = 0;
        queue<string> vq;
        vq.push(beginWord);
        string qfront;

        bool flag = false;
        while (!vq.empty()) {
            qfront = vq.front();
            vq.pop();
            if (qfront == endWord)
                break;
            if (canTrans(qfront, endWord)) {
                adjacentWordOfEnd.push_back(qfront);
                flag = true;
                continue;
            }
            if (flag)
                continue;

            int curLevel = isVisited[qfront];
            for (auto& w: wordList) {
                if (canTrans(qfront, w)) {
                    if (isVisited.count(w) == 0) {
                        isVisited[w] = curLevel + 1;
                        vq.push(w);
                        preVertex[w].push_back(qfront);
                    } else if (isVisited[w] == 1 + curLevel) {
                        preVertex[w].push_back(qfront);
                    }
                }
            }
        }

        if (adjacentWordOfEnd.empty())
            return resultLists;

        queue< stack<string> > pathQueue;
        for (auto& w: adjacentWordOfEnd) {
            stack<string> path;
            path.push(endWord);
            path.push(w);
            pathQueue.push(path);
        }

        while (!pathQueue.empty()) {
            stack<string> curPath(pathQueue.front());
            pathQueue.pop();
            string curVertex = curPath.top();
            if (curVertex == beginWord) {
                insertPath(resultLists, curPath);                
            } else if (preVertex[curVertex].size() == 1 && preVertex[curVertex].back() == beginWord) {
                curPath.push(beginWord);
                insertPath(resultLists, curPath);
            } else {
                for (int i = 1; i < preVertex[curVertex].size(); i++) {
                    stack<string> newPath(curPath);
                    newPath.push(preVertex[curVertex][i]);
                    pathQueue.push(newPath);
                }
                curPath.push(preVertex[curVertex][0]);
                pathQueue.push(curPath);
            }
        }

        return resultLists;
    }


    void insertPath(vector<vector<string>>& resultLists, stack<string>& reversePath) {
        vector<string> path;
        while (!reversePath.empty()) {
            path.push_back(reversePath.top());
            reversePath.pop();
        }
        resultLists.push_back(path);
    }
};
```

------

## 解题描述

这道题是在leetcode上AC的第一道hard的题，花了一天。一开始想到的还是BFS，在[Word Ladder](https://leetcode.com/problems/word-ladder/description/)的基础上，多记录下完整的路径。但是实际并没有这么简单。这道题要多考虑相同长度的所有路径的情况。所以我起初想到的解决的办法就是通过记录BFS树中所求路径上每一个点的父节点，然后通过获取endWord的所有父节点来向上回溯直到达到beginWord。但是这里我想少了一点，就是其实路径中间的节点也可以和endWord一样拥有多个父节点。解决了这个问题之后，没有过的测例表明，对于endWord同层节点的排除还没有做。所以就另外加了一个flag来标记以排除与endWord同层的点，这才最终AC。