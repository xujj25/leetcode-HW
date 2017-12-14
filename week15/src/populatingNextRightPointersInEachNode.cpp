#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
private:
    void connectNode(vector<TreeLinkNode*>& v) {
        int size = v.size();
        for (int i = 0; i <= size - 2; i++) {
            v[i] -> next = v[i + 1];
        }
    }
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;
        int levelNodeNum = 1;
        int curLevelNodeNum = 0;
        queue<TreeLinkNode*> q;
        vector<TreeLinkNode*> v;
        q.push(root);
        while (!q.empty()) {
            TreeLinkNode* node = q.front();
            q.pop();
            v.push_back(node);
            if (node -> left != NULL)
                q.push(node -> left);
            if (node -> right != NULL)
                q.push(node -> right);
            curLevelNodeNum++;
            if (curLevelNodeNum == levelNodeNum) {
                levelNodeNum *= 2;
                curLevelNodeNum = 0;
                connectNode(v);
                v.clear();
            }
        }
    }
};

int main() {
    return 0;
}
