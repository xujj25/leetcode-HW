#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
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
    Solution solu;
    cout << solu.ladderLength(beginWord, endWord, wordList) << endl;
    return 0;
}