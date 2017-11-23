#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int row = obstacleGrid.size();
        int col = obstacleGrid[0].size();
        int i, j;
        vector<int> dp(col, 0);
        dp[0] = 1;
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (obstacleGrid[i][j] == 1)
                    dp[j] = 0;
                else if (j > 0)
                    dp[j] += dp[j - 1];
            }
        }
        return dp[col - 1];
    }
};

int main(void) {
    int row, col;
    cin >> row >> col;
    vector<int> rowvec(col);
    vector<vector<int>> grid(row, rowvec);
    int t;
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cin >> t;
            grid[i][j] = t;
        }
    }
    cout << Solution().uniquePathsWithObstacles(grid) << endl;
    return 0;
}