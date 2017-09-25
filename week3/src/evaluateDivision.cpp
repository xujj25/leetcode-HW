#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <stdexcept>      // std::out_of_range
using namespace std;

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

int main(int argc, char const *argv[])
{
    int equNum, i, qNum;
    string v1, v2;
    double val;
    cout << "Input equations num: ";
    cin >> equNum;
    vector<pair<string, string>> equations;
    vector<double> values;
    vector<pair<string, string>> queries;
    cout << "Input " << equNum << " equation(s):" << endl;
    for (i = 0; i < equNum; i++) {
        cin >> v1 >> v2;
        equations.push_back(make_pair(v1, v2));
    }
    cout << "Input " << equNum << " value:" << endl;
    for (i = 0; i < equNum; i++) {
        cin >> val;
        values.push_back(val);
    }
    cout << "Input query num: ";
    cin >> qNum;
    cout << "Input " << qNum << " queries:" << endl;
    for (i = 0; i < qNum; i++) {
        cin >> v1 >> v2;
        queries.push_back(make_pair(v1, v2));
    }
    Solution solu;
    vector<double> result = solu.calcEquation(equations, values, queries);
    for (i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}