#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    void dfs(vector<vector<int>>& res, vector<int>& path, TreeNode* root, int sum) {
        if (root -> left == NULL && root -> right == NULL) {
            if (sum == root -> val) {
                path.push_back(root -> val);
                res.push_back(path);
                path.pop_back();
            }
            return;
        }
        if (root -> left != NULL) {
            path.push_back(root -> val);
            dfs(res, path, root -> left, sum - (root -> val));
            path.pop_back();
        }
        if (root -> right != NULL) {
            path.push_back(root -> val);
            dfs(res, path, root -> right, sum - (root -> val));
            path.pop_back();
        }
    }
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> res;
        if (root == NULL)
            return res;
        vector<int> path;
        dfs(res, path, root, sum);
        return res;
    }
};



class TreeGenerator {
public:
    TreeNode* getTreeNode(vector<int>& inOrder, vector<int>& postOrder,
                          int inStart, int inEnd, int postStart, int postEnd) {
        TreeNode* resultNode = new TreeNode(postOrder[postEnd]);
        if (postStart == postEnd)
            return resultNode;
        int i;
        int inNodeVal = postOrder[postEnd];
        for (i = inStart; i <= inEnd; i++) {
            if (inNodeVal == inOrder[i])
                break;
        }
        if (i > inStart)
            resultNode -> left =
                    getTreeNode(inOrder, postOrder, inStart, i - 1, postStart, postStart + i - 1 - inStart);
        if (i < inEnd)
            resultNode -> right =
                    getTreeNode(inOrder, postOrder, i + 1, inEnd, postStart + i - inStart, postEnd - 1);
        return resultNode;
    }

    TreeNode* buildTree(vector<int>& inOrder, vector<int>& postOrder) {
        int size = inOrder.size();
        if (size == 0)
            return NULL;
        return getTreeNode(inOrder, postOrder, 0, size - 1, 0, size - 1);
    }

    void inOrderPrintTree(TreeNode* node) {
        if (node == NULL)
            return;
        inOrderPrintTree(node -> left);
        cout << node -> val << " ";
        inOrderPrintTree(node -> right);
    }

    void freeTree(TreeNode* node) {
        if (node == NULL)
            return;
        freeTree(node -> left);
        freeTree(node -> right);
        delete node;
    }
};

int main() {
    int in[10] = { 7, 12, 2, 3, 5, 13, 10, 6, 1, 9 };
    int post[10] = { 7, 2, 12, 3, 13, 6, 9, 1, 10, 5 };
    vector<int> inOrder(in, in + 10);
    vector<int> postOrder(post, post + 10);
    TreeGenerator treeGenerator;
    TreeNode* root = treeGenerator.buildTree(inOrder, postOrder);

    vector<vector<int>> res = Solution().pathSum(root, 22);

    cout << "result:" << endl;
    for (auto& vec : res) {
        for (auto& e : vec) {
            cout << e << " ";
        }
        cout << endl;
    }

    treeGenerator.freeTree(root);
    return 0;
}

/*
              5
             / \
            3   10
           /   / \
          12  13  1
         /  \    / \
        7    2  6   9
 */
