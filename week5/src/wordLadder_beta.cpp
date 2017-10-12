#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

/*
For example,

Given:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log","cog"]
As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
*/

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

int main(int argc, char const *argv[])
{
    string beginWord, endWord, word;
    vector<string> wordList;
    int listSize;
    cin >> beginWord >> endWord;
    cin >> listSize;
    for (int i = 0; i < listSize; i++) {
        cin >> word;
        wordList.push_back(word);
    }
    cout << "[" << endl;

    Solution solu;
    auto lists = solu.findLadders(beginWord, endWord, wordList);

    for (auto& list: lists) {
        cout << "\t[ ";
        for (auto& item: list)
            cout << item << " ";
        cout << "]" << endl;
    }

    cout << "]" << endl;

    return 0;
}