#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    void timeConvert(vector<int>& times, vector<string>& timePoints) {
        int size = timePoints.size();
        for (int i = 0; i < size; i++) {
            times[i] = ((timePoints[i][0] - '0') * 10 +
                        (timePoints[i][1] - '0')) * 60 +
                        (timePoints[i][3] - '0') * 10 +
                        (timePoints[i][4] - '0');
        }
    }

    int getDiff(int a, int b) {
        int t = b - a;
        if (t > 720)
            return 1440 - t;
        else
            return t;
    }

    int findMinDifference(vector<string>& timePoints) {
        if (timePoints.empty() || timePoints.size() == 1)
            return 0;
        int size = timePoints.size();
        vector<int> times(size);
        timeConvert(times, timePoints);
        sort(times.begin(), times.end());
        int mind = getDiff(times[0], times[1]);
        int t;
        for (int i = 0; i <= size - 2; i++) {
            t = getDiff(times[i], times[i + 1]);
            if (t < mind)
                mind = t;
        }
        t = getDiff(times[0], times[size - 1]);
        if (t < mind)
            mind = t;
        return mind;
    }
};

int main(int argc, char const *argv[])
{
    int size;
    cin >> size;
    vector<string> timePoints(size);
    string t;
    for (int i = 0; i < size; i++) {
        cin >> t;
        timePoints[i] = t;
    }
    cout << Solution().findMinDifference(timePoints) << endl;
    return 0;
}