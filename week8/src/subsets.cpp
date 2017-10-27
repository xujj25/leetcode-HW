#include <iostream>
#include <vector>
using namespace std;

/*
// Solution I
class Solution {
public:
    vector< vector<int> > subsets(vector<int>& nums) {
        int size = nums.size(), j;
        unsigned long long bits = 1 << size;
        unsigned long long i;
        vector< vector<int> > result;
        for (i = 0; i < bits; i++) {
            vector<int> temp;
            for (j = 0; j < size; j++) {
                if ((i >> j) & 1)
                    temp.push_back(nums[j]);
            }
            result.push_back(temp);
        }
        return result;
    }
};

*/

class Solution {
public:
    vector< vector<int> > subsets(vector<int>& nums) {
        vector<vector<int> > result;
        if (nums.empty()) return result;
        int numsSize = nums.size();
        int i, j;
        result.resize(1);
        for (i = 0; i < numsSize; i++) {
            int resultSize = result.size();
            for (j = 0; j < resultSize; j++) {
                result.push_back(result[j]);
                result.back().push_back(nums[i]);
            }
        }
        return result;
    }
};

int main(int argc, char const *argv[])
{
    int arr[3] = {1, 2, 3};
    vector<int> testvec(arr, arr + 3);
    vector< vector<int> > result = Solution().subsets(testvec);
    int i, j;
    for (i = 0; i < result.size(); i++) {
        for (j = 0; j < result[i].size(); j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
