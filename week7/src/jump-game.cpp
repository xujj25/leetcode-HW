#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    int max(int a, int b) {
        return a > b ? a : b;
    }
public:
    bool canJump(vector<int>& nums) {
        int size = nums.size();
        if (size == 0)
            return false;
        if (size == 1)
            return true;
        if (nums[0] >= size - 1)
            return true;

        int* farthestPoint = new int[size];
        farthestPoint[0] = nums[0];
        for (int i = 1; i < size; i++) {
            if (i <= farthestPoint[i - 1]) {
                farthestPoint[i] = max(farthestPoint[i - 1], i + nums[i]);
            } else {
                delete []farthestPoint;
                return false;
            }
        }
        bool result = farthestPoint[size - 2] >= size - 1;
        delete [] farthestPoint;
        return result;

    }
};

int main(int argc, char const *argv[])
{
    vector<int> v1, v2;
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(1);
    v1.push_back(1);
    v1.push_back(4);

    v2.push_back(3);
    v2.push_back(2);
    v2.push_back(1);
    v2.push_back(0);
    v2.push_back(4);

    cout << Solution().canJump(v1) << endl;
    cout << Solution().canJump(v2) << endl;

    return 0;
}