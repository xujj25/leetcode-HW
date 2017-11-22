#include <iostream>
using namespace std;

class Solution {
    int combinatorial(int big, int small) {
        unsigned long long res = 1;
        unsigned long long i = static_cast<unsigned long long>(big - small + 1);
        unsigned long long j = 1;
        for (; i <= big, j <= small; i++, j++) {
            res *= i;
            res /= j;
        }
        return static_cast<int>(res);
    }
public:
    int uniquePaths(int m, int n) {
        return combinatorial(m + n - 2, min(m, n) - 1);
    }
};

int main() {
    int m, n;
    cin >> m >> n;
    cout << Solution().uniquePaths(m, n) << endl;
    return 0;
}