#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

int main(int argc, char const *argv[])
{
    string s = "leetcode";
    vector<string> wordDict;
    wordDict.push_back("leet");
    wordDict.push_back("code");
    cout << (Solution().wordBreak(s, wordDict) ? "True" : "False") << endl;
    return 0;
}