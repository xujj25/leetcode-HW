#include <iostream>
#include <string>
using namespace std;

class Solution {
    public:
    int minDistance(string word1, string word2) {
        if (word1 == word2)
            return 0;
        if (word1.empty())
            return word2.length();
        if (word2.empty())
            return word1.length();

        int len1 = word1.length() + 1;
        int len2 = word2.length() + 1;
        int** f = new int*[len1];
        int i, j;
        for (i = 0; i < len1; i++) {
            f[i] = new int[len2];
            f[i][0] = i;
        }

        for (j = 0; j < len2; j++) {
            f[0][j] = j;
        }

        for (i = 1; i < len1; i++) {
            for (j = 1; j < len2; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    f[i][j] = f[i - 1][j - 1];
                } else {
                    f[i][j] = min(min(f[i - 1][j] + 1, f[i][j - 1] + 1), f[i - 1][j - 1] + 1);
                }                
            }
        }
        int res = f[len1 - 1][len2 - 1];

        for (i = 0; i < len1; i++)
            delete [] f[i];
        delete [] f;

        return res;
    }
};

int main()
{
    string a = "sunny", b = "snowy";
    // cin >> a >> b;
    cout << Solution().minDistance(a, b) << endl;
    return 0;
}
