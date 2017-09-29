#include <iostream>
#include <queue>
#include <vector>
using namespace std;

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

int main(int argc, char const *argv[])
{
    int numCourses, numP, v1, v2;
    cin >> numCourses;
    cin >> numP;
    vector<pair<int, int>> pre;
    for (int i = 0; i < numP; i++) {
        cin >> v1 >> v2;
        pre.push_back(make_pair(v1, v2));
    }
    Solution solu;
    vector<int> r = solu.findOrder(numCourses, pre);
    for (auto& e: r)
        cout << e << " ";
    cout << endl;
    return 0;
}