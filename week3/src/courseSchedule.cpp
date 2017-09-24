#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

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


int main(int argc, char const *argv[])
{
    int numCourses, pairsNum;
    vector<pair<int, int>> prerequisites;
    cout << "Input courses num: ";
    cin >> numCourses;
    cout << "Input pairs num: ";
    cin >> pairsNum;
    cout << "Input " << pairsNum << " course(s):" << endl;
    int first, second;
    for (int i = 0; i < pairsNum; i++) {
        cin >> first >> second;
        prerequisites.push_back(make_pair(first, second));
    }

    Solution solu;
    cout << (solu.canFinish(numCourses, prerequisites) ? "can finish" : "cannot finish") << endl;
    return 0;
}