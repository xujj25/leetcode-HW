#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int> > subsetsWithDup(vector<int>& nums) {
        vector<vector<int> > result;
        if (nums.empty())
            return result;
        result.resize(1);
        sort(nums.begin(), nums.end());
        int lastNum = nums[0], size = 1, newResSize;
        int i, j;
        for (i = 0; i < nums.size(); i++) {
            if (lastNum != nums[i]) {
                lastNum = nums[i];
                size = result.size();
            }
            newResSize = result.size();
            for (j = newResSize - size; j < newResSize; j++) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    int arr[3] = {1, 2, 2};
    vector<int> nums(arr, arr + 3);
    vector<vector<int> > res = Solution().subsetsWithDup(nums);
    int i, j;
    for (i = 0; i < res.size(); i++) {
        for (j = 0; j < res[i].size(); j++)
            cout << res[i][j] << " ";
        cout << endl;
    }
    return 0;
}