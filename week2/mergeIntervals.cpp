#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// Definition for an interval.
struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};
 
class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> resultVector;
        if (intervals.size() == 0)
            return resultVector;

        int size = intervals.size();
        int i, j, rsize;

        resultVector.push_back(intervals[0]);

        Interval tempInterval;
        bool is_finish;

        for (i = 1; i < size; i++) {
            tempInterval.start = intervals[i].start;
            tempInterval.end = intervals[i].end;

            is_finish = false;
            while (!is_finish) {
                if (resultVector.size() == 0) {
                    resultVector.push_back(tempInterval);
                    break;
                }

                for (j = 0; j < resultVector.size(); j++) {
                    if ( (tempInterval.end >= resultVector[j].start && tempInterval.end <= resultVector[j].end) ||
                         (tempInterval.start >= resultVector[j].start && tempInterval.start <= resultVector[j].end) ||
                         (tempInterval.start <= resultVector[j].start && tempInterval.end >= resultVector[j].end)) {

                        tempInterval.start = tempInterval.start < resultVector[j].start ? tempInterval.start : resultVector[j].start;
                        tempInterval.end = tempInterval.end > resultVector[j].end ? tempInterval.end : resultVector[j].end;
                        resultVector.erase(resultVector.begin() + j);
                        break;
                    }
                    if (j == resultVector.size() - 1) {
                        resultVector.push_back(tempInterval);
                        is_finish = true;
                        break;
                    }
                }
            }
        }        

        return resultVector;
    }
};

int main()
{
    for ( ; ; ) {
        vector<Interval> inputVector;
        int i;
        cin >> i;
        while (i--) {
            Interval inter;
            cin >> inter.start >> inter.end;
            inputVector.push_back(inter);
        }

        Solution solu;
        vector<Interval> result = solu.merge(inputVector);
        int size = result.size();

        cout << "Result: ";
        for (i = 0; i < size; i++) {
            cout << "[" << result[i].start << ", " << result[i].end << "] ";
        }
        cout << endl;
    }

    return 0;
}