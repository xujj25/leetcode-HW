#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int> >& grid) {
        if (grid.empty())
            return 0;
        int i, j;
        int rowCount = grid.size();
        int colCount = grid[0].size();
        int **stepCount;
        stepCount = new int*[rowCount];

        stepCount[0] = new int[colCount];
        stepCount[0][0] = grid[0][0];
        for (i = 1; i < rowCount; i++) {
            stepCount[i] = new int[colCount];
            stepCount[i][0] = grid[i][0] + stepCount[i - 1][0];
        }
        for (j = 1; j < colCount; j++) {
            stepCount[0][j] = grid[0][j] + stepCount[0][j - 1];
        }

        for (i = 1; i < rowCount; i++) {
            for (j = 1; j < colCount; j++) {
                stepCount[i][j] = min(stepCount[i - 1][j], stepCount[i][j - 1]) + grid[i][j];
            }
        }
        j = stepCount[rowCount - 1][colCount - 1];
        for (i = 0; i < rowCount; i++)
            delete [] stepCount[i];
        delete [] stepCount;
        return j;
    }
};

int main(int argc, char const *argv[])
{
    /*
    [
    [1,3,1],
    [1,5,1],
    [4,2,1]
    ]
    */
    int row, col, i, j;
    cin >> row >> col;
    vector<vector<int> > grid(row, vector<int>(col));
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++)
            cin >> grid[i][j];
    }
    cout << Solution().minPathSum(grid) << endl;
    return 0;
}
