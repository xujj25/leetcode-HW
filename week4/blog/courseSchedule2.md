# Course Schedule II题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/course-schedule-ii/description/

------

## Description

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.

There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.

For example:
```
2, [[1,0]]
```
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]
```
4, [[1,0],[2,0],[3,1],[3,2]]
```
There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

**Note:**
    1. The input prerequisites is a graph represented by **a list of edges**, not adjacency matrices. Read more about how a graph is represented.
    2. You may assume that there are no duplicate edges in the input prerequisites.


## Solution
```cpp
class Solution {
private:
    vector<int> inDegree;
    vector<bool> isFinish;
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        inDegree.resize(numCourses);
        isFinish.resize(numCourses);
        int i, v;
        for (i = 0; i < numCourses; i++) {
            inDegree[i] = 0;
            isFinish[i] = false;
        }
        for (i = 0; i < prerequisites.size(); i++) 
            inDegree[prerequisites[i].first]++;

        queue<int> vq;
        for (i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0)
                vq.push(i);
        }

        vector<int> resultVec;
        if (vq.empty())
            return resultVec;

        while (!vq.empty()) {
            v = vq.front();
            vq.pop();
            resultVec.push_back(v);
            isFinish[v] = true;
            for (i = 0; i < prerequisites.size(); i++) {
                if (v == prerequisites[i].second) {
                    inDegree[prerequisites[i].first]--;
                    if (inDegree[prerequisites[i].first] == 0 && !isFinish[prerequisites[i].first])
                        vq.push(prerequisites[i].first);
                }
            }
        }

        if (resultVec.size() == numCourses) {
            return resultVec;
        }
        else {
            vector<int> r;
            return r;
        }
    }
};

```

------

## 解题描述
这道题与[Course Schedule](https://leetcode.com/problems/course-schedule/description/)的解法基本是一样的。我还是采用了BFS进行拓扑排序，总的来说没有什么新的坑点。