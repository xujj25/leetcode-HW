#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void printFlags(vector<bool>& flags, int size) {
    // test
    cout << "flags: ";
    for (int i = 0; i <= size; i++)
        cout << (flags[i] ? 1 : 0) << " ";
    cout << endl;
}

void printVector(vector<string>& vec) {
    int size = vec.size();
    cout << "\nin vector 'res':" << endl;
    for (int i = 0; i < size; i++)
        cout << vec[i] << endl;
}


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

int main(int argc, char const *argv[])
{
    string s, temp;
    vector<string> wordDict;
    int dictSize, i;

    cin >> s;
    cin >> dictSize;
    for (i = 0; i < dictSize; i++) {
        cin >> temp;
        wordDict.push_back(temp);
    }
    vector<string> res = Solution().wordBreak(s, wordDict);

    cout << "\nResults:" << endl;
    for (i = 0; i < res.size(); i++)
        cout << res[i] << endl;
    return 0;
}

/*
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
10
a
aa
aaa
aaaa
aaaaa
aaaaaa
aaaaaaa
aaaaaaaa
aaaaaaaaa
aaaaaaaaaa
*/