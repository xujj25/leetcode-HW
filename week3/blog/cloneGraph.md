# Clone Graph题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/clone-graph/description/

------

## Description

Clone an undirected graph. Each node in the graph contains a label and a list of its neighbors.

**OJ's undirected graph serialization:**

Nodes are labeled uniquely.

We use # as a separator for each node, and , as a separator for node label and each neighbor of the node.
As an example, consider the serialized graph {0,1,2#1,2#2,2}.

The graph has a total of three nodes, and therefore contains three parts as separated by #.

	1. First node is labeled as 0. Connect node 0 to both nodes 1 and 2.
	2. Second node is labeled as 1. Connect node 1 to node 2.
	3. Third node is labeled as 2. Connect node 2 to node 2 (itself), thus forming a self-cycle.
Visually, the graph looks like the following:
```
       1
      / \
     /   \
    0 --- 2
         / \
         \_/
```

## Solution
```cpp
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
```

------

## 解题描述

在这道题上面还花费了很多的时间，一开始想到的算法就是BFS，但是BFS得到的结果总是WA。不断WA的过程中才想到，一个顶点可以有多条指向自己的边。我一开始是没有想到这个问题，然后使用map模拟邻接矩阵来记录边总是WA。然后到后面查阅了相关资料才发现，用哈希的方式，将原图和克隆图的每一个点一一对应起来是最为准确的，且会自动排除BFS中已经访问的点。另外，对于指向自己的边的记录，使用哈希也能准确反映其内涵：顶点包含的顶点指针vector中的顶点就是当前顶点的指针。另外，很多资料中提到，这类题使用DFS递归运算更为精妙简洁。
