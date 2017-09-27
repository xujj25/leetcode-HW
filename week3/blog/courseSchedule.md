# Course Schedule题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/course-schedule/description/

------

## Description

There are a total of n courses you have to take, labeled from 0 to n - 1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite **pairs**, is it possible for you to finish all courses?

For example:
```
2, [[1,0]]
```
There are a total of 2 courses to take. To take course 1 you should have finished course 0. So it is possible.
```
2, [[1,0],[0,1]]
```
There are a total of 2 courses to take. To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

**Note:**
    1. The input prerequisites is a graph represented by **a list of edges**, not adjacency matrices. Read more about how a graph is represented.
    2. You may assume that there are no duplicate edges in the input prerequisites.


## Solution
```cpp
class Solution {
private:
    bool **graph;
    int* color;
    int graphDim = 0;


public:
    ~Solution() {
        if (graphDim == 0)
            return;
        delete[] color;
        for (int i = 0; i < graphDim; i++)
            delete[] graph[i];
        delete graph;
    }

    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        if (numCourses <= 0)
            return false;
        if (prerequisites.size() == 0)
            return true;
        int i, j;

        graphDim = numCourses;
        graph = new bool*[numCourses];
        color = new int[numCourses];

        for (i = 0; i < numCourses; i++)
            graph[i] = new bool[numCourses];

        for (i = 0; i < numCourses; i++) {
            color[i] = 0;
            for (j = 0; j < numCourses; j++) {
                graph[i][j] = false;
            }
        }

        for (auto p: prerequisites) {
            graph[p.first][p.second] = true;
        }

        int sv;
        for (auto p: prerequisites) {
            sv = p.first;
            for (i = 0; i < numCourses; i++) {
                if (graph[sv][i]) {
                    if (color[sv] == 2)
                        continue;
                    if (!dfs(sv))
                        return false;
                    else
                        color[i] = 2;
                }
            }
        }
        return true;
    }

    bool dfs(int v) {
        color[v] = 1;
        int i;
        for (i = 0; i < graphDim; i++) {
            if (graph[v][i]) {
                if (color[i] == 2) {
                    break;
                } else if (color[i] == 1) {
                    return false;
                } else {
                    if (!dfs(i)) {
                        return false;
                    }
                }
            }
        }
        color[v] = 2;
        return true;
    }
};

```

------

## 解题描述
这道题我使用的是DFS，过程中通过对以访问的顶点进行染色来判断是否有环。不过提交后出现了几次TLE，检查代码发现好几处可以充分利用染色数组来减少充分访问。改了好几次才AC。现实利用中DFS和BFS处理的数据量往往会很大，这几次TLE还是提醒我要注意优化算法时间复杂度。

------

## 文章更新
这道题本质上是检查图是否有环，而如果图是可以拓扑排序的，则一定是无环的。通过BFS检查图是否能够拓扑排序也是可以解决的，且相对来说实现效率较高，避免了DFS的递归开销。下面给出实现：
```cpp
class Solution
{
private:
    map<int, int> inDegree;
public:
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        int i, curVertex;
        for (i = 0; i < numCourses; i++)
            inDegree[i] = 0;

        for (auto p: prerequisites) 
            inDegree[p.second]++;

        queue<int> vq;
        for (i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                vq.push(i);
            }
        }

        if (vq.empty())
            return false;

        while (!vq.empty()) {
            curVertex = vq.front();
            vq.pop();
            inDegree.erase(curVertex);
            for (i = 0; i < prerequisites.size(); i++) {
                if (curVertex == prerequisites[i].first) {
                    inDegree[prerequisites[i].second]--;
                    if (inDegree[prerequisites[i].second] == 0)
                        vq.push(prerequisites[i].second);
                }
            }
        }

        return inDegree.empty();
    }    
};
```
