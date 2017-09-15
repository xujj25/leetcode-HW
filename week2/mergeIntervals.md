# Merge Intervals题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/merge-intervals/description/

------

## Description

Given a collection of intervals, merge all overlapping intervals.

## Example

```
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].
```

## Solution
```C++
/* Definition for an interval.
 * struct Interval {
 *    int start;
 *    int end;
 *    Interval() : start(0), end(0) {}
 *    Interval(int s, int e) : start(s), end(e) {}
 * };
*/
 
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
```

------

## 解题描述

这道题还是费了一番周折去解决的。可能一开始的想法就是不想使用暴力破解的方法，想试着看看在解决问题的过程中就实现优化，减少遍历次数，但是却弄巧成拙出了些莫名奇妙的bug，一度WA好几次。最后还是妥协了，“先做到，再做好”，使用暴力破解，也就是通过不断更新即将插入结果容器的区间的上下界，每次更新完再重复遍历结果容器，以达到完全排除区间有交叠的情况。
