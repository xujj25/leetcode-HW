#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int min(int a, int b) {
        return a < b ? a : b;
    }

    int minimumTotal(vector< vector<int> >& triangle) {
        int size = triangle.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return triangle[0][0];
        int** result = new int*[size];
        int i, j;
        for (i = 0; i < size; i++)
            result[i] = new int[size];
        for (i = 0; i < size; i++)
            result[size - 1][i] = triangle[size - 1][i];
        for (i = size - 2; i >= 0; i--) {
            for (j = 0; j <= i; j++) {
                result[i][j] = min(result[i + 1][j], result[i + 1][j + 1]) + triangle[i][j];
            }
        }

        j = result[0][0];
        for (i = 0; i < size; i++)
            delete [] result[i];
        delete [] result;
        return j;
    }
};

int main(int argc, char const *argv[])
{
    int a1[1] = {2};
    int a2[2] = {3, 4};
    int a3[3] = {6, 5, 7};
    int a4[4] = {4, 1, 8, 3};
    vector<int> v1(a1, a1 + 1);
    vector<int> v2(a2, a2 + 2);
    vector<int> v3(a3, a3 + 3);
    vector<int> v4(a4, a4 + 4);

    vector< vector<int> > v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    cout << Solution().minimumTotal(v) << endl;

    return 0;
}