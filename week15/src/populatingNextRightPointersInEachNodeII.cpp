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

    struct LevelNode {
        TreeLinkNode* node;
        int level;
        LevelNode(TreeLinkNode* n, int l) {
            node = n;
            level = l;
        }
    };

    const int InitLevel = 1;
public:
    void connect(TreeLinkNode *root) {
        if (root == NULL)
            return;
        int curLevel = InitLevel;
        vector<TreeLinkNode*> v;
        queue<LevelNode> q;
        q.push(LevelNode(root, InitLevel));
        while (!q.empty()) {
            LevelNode ln = q.front();
            q.pop();
            if (ln.node -> left != NULL) {
                q.push(LevelNode(ln.node -> left, ln.level + 1));
            }
            if (ln.node -> right != NULL) {
                q.push(LevelNode(ln.node -> right, ln.level + 1));
            }
            if (ln.level != curLevel) {
                connectNode(v);
                v.clear();
                curLevel++;
            }
            v.push_back(ln.node);
        }
        connectNode(v);
    }
};

int main() {
    TreeLinkNode* root = new TreeLinkNode(1);
    root -> left = new TreeLinkNode(2);
    root -> right= new TreeLinkNode(3);
    Solution().connect(root);
    queue<TreeLinkNode*> q;
    vector<TreeLinkNode*> levelTraverseVector;
    q.push(root);
    while (!q.empty()) {
        TreeLinkNode* node = q.front();
        q.pop();
        levelTraverseVector.push_back(node);
        if (node -> left != NULL) {
            q.push(node -> left);
        }
        if (node -> right != NULL) {
            q.push(node -> right);
        }
    }
    for (int i = 0; i < levelTraverseVector.size(); i++) {
        cout << levelTraverseVector[i] -> val;
        cout << " -> ";
        if (levelTraverseVector[i] -> next == NULL) {
            cout << "NULL" << endl;
        }
    }
    delete(root -> left);
    delete(root -> right);
    delete(root);
    return 0;
}
