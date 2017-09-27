#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <map>
using namespace std;

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