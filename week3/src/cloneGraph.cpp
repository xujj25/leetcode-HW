#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct UndirectedGraphNode {
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x) {};
};

class Solution {
public:
    UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node) {
        if (node == NULL)
            return NULL;
        map< UndirectedGraphNode*, UndirectedGraphNode* > hashmap;
        queue< UndirectedGraphNode* > nodeq;
        nodeq.push(node);
        hashmap[node] = new UndirectedGraphNode(node -> label);
        UndirectedGraphNode *curNodeHash;
        while (!nodeq.empty()) {
            UndirectedGraphNode* preNode = nodeq.front();
            nodeq.pop();
            for (auto curNode : preNode -> neighbors) {
                if (hashmap.find(curNode) == hashmap.end()) {
                    curNodeHash = new UndirectedGraphNode(curNode -> label);
                    hashmap[curNode] = curNodeHash;
                    nodeq.push(curNode);
                }
                (hashmap[preNode] -> neighbors).push_back(hashmap[curNode]);
            }
        }

        return hashmap[node];
    }
};

UndirectedGraphNode* mapToGraphNode(map< int, vector<int> >& graph) {
    UndirectedGraphNode* resultNode = new UndirectedGraphNode(graph.begin() -> first);
    queue<UndirectedGraphNode*> nodeq;
    nodeq.push(resultNode);
    UndirectedGraphNode *curNode, *node;
    map<int, bool> color;
    int i;
    while (!nodeq.empty()) {
        curNode = nodeq.front();
        nodeq.pop();

        // test
        cout << "curNode label = " << curNode -> label << endl;

        color[curNode -> label] = true;
        for (i = 0; i < graph[curNode -> label].size(); i++) {
            node = new UndirectedGraphNode(graph[curNode -> label][i]);
            (curNode -> neighbors).push_back(node);
            if (curNode -> label != node -> label &&
                    (color.find(node -> label) == color.end() || !color[node -> label])) {
                //test
                cout << "mapToGraphNode: Push " << node -> label << " for " << curNode -> label << endl;

                color[node -> label] = false;
                nodeq.push(node);
            }
        }
    }

    return resultNode;
}

void printGraph(UndirectedGraphNode* node) {
    map<int, bool> color;
    queue<UndirectedGraphNode*> nodeq;
    nodeq.push(node);
    UndirectedGraphNode* tempNode;
    int i;
    while (!nodeq.empty()) {
        tempNode = nodeq.front();
        nodeq.pop();
        color[tempNode -> label] = true;
        cout << tempNode -> label << " ";
        for (i = 0; i < (tempNode -> neighbors).size(); i++) {
            cout << (tempNode -> neighbors)[i] -> label << " ";
            if (color.find((tempNode -> neighbors)[i] -> label) == color.end() || !color[(tempNode -> neighbors)[i] -> label]) {
                color[(tempNode -> neighbors)[i] -> label] = false;
                nodeq.push((tempNode -> neighbors)[i]);
            }
        }
        cout << "# ";
    }
    cout << endl;
}

int main(int argc, char const *argv[])
{
    map< int, vector<int> > graph1, graph2;
    graph1[0].push_back(0);
    graph1[0].push_back(0);

    graph2[0].push_back(1);
    graph2[0].push_back(2);
    graph2[1].push_back(2);
    graph2[2].push_back(2);

    printGraph(mapToGraphNode(graph1));
    printGraph(mapToGraphNode(graph2));

    cout << "\nTest Solution: \n";

    Solution solu;
    printGraph(solu.cloneGraph(mapToGraphNode(graph1)));
    printGraph(solu.cloneGraph(mapToGraphNode(graph2)));

    return 0;
}