# Evaluate Division题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/evaluate-division/description/

------

## Description

Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

## Example

Given a / b = 2.0, b / c = 3.0. 
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? . 
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

```
equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
```

The input is always valid. You may assume that evaluating the queries will result in no division by zero and there is no contradiction.



## Solution
```cpp
class Solution {
private:
    map<pair<string, string>, double> graph;
    map<string, bool> isVisited;
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {        
        int i;
        vector<double> resultVec;
        for (i = 0; i < equations.size(); i++) {
            graph[equations[i]] = values[i];
            graph[make_pair(equations[i].second, equations[i].first)] = 1.0 / values[i];
            isVisited[equations[i].first] = isVisited[equations[i].second] = false;
        }
        for (auto& q: queries) {
            if (isVisited.find(q.first) == isVisited.end() ||
                isVisited.find(q.second) == isVisited.end()) {
                resultVec.push_back(-1.0);
            } else if (q.first == q.second) {
                resultVec.push_back(1.0);
            } else {
                resultVec.push_back(dfs_cal(q));
            }
        }
        return resultVec;
    }

    double dfs_cal(pair<string, string> p) {
        double result = -1.0;
        isVisited[p.first] = true;

        try {
            result = graph.at(p);
        } catch (const out_of_range& err) {
            for (auto& edge: graph) {
                if (p.first == edge.first.first && !isVisited[edge.first.second]) {
                    if ((result = dfs_cal(make_pair(edge.first.second, p.second))) > 0) {
                        result *= edge.second;
                        break;
                    }
                }
            }
        }

        isVisited[p.first] = false;
        return result;
    }
};
```

------

## 解题描述

这道题初步的想法就是通过以字符串作为顶点的标识，用map模拟构建一个邻接矩阵。然后对于给定的查询，使用DFS求得路径。总的来说没有坑点，不过可能由于使用的STL较多，运行的时间还是相对比较长。查看了一下题目的Discuss，发现使用[并查集算法](https://discuss.leetcode.com/topic/58577/0ms-c-union-find-solution-easy-to-understand)来解决的话耗费时间较少，而且也不难理解。

