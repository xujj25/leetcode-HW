#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) {
            return false;
        }

        int size = matrix.size();
        int low = 0, high = size - 1, mid;
        while (low < high) {
            mid = (high + low) / 2;
            if (target == matrix[mid].back())
                return true;
            else if (target < matrix[mid].back())
                high = mid;
            else
                low = mid + 1;
        }
        size = matrix[low].size();
        vector<int>& arr = matrix[low];
        low = 0;
        high = size - 1;
        while (low < high) {
            mid = (high + low) / 2;
            if (target == arr[mid])
                return true;
            else if (target < arr[mid])
                high = mid;
            else
                low = mid + 1;
        }
        return arr[low] == target;
    }
};

int main() {
    int row, col;
    cin >> row >> col;
    vector<vector<int>> matrix(row, vector<int>(col));
    int i, j, t;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            cin >> t;
            matrix[i][j] = t;
        }
    }
    int target;
    cin >> target;
    cout << (Solution().searchMatrix(matrix, target) ? 1 : 0) << endl;
    return 0;
}
