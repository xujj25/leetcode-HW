#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

int main() {
    auto res = Solution().partition("abcdefgfefgxyaopqhjhi");
    int i, j;
    for (i = 0; i < res.size(); i++) {
        for (j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
