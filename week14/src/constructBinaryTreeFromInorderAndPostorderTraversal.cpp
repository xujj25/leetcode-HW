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
};

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

int main() {
    int in[7] = { 4, 2, 5, 1, 6, 3, 7 };
    int post[7] = { 4, 5, 2, 6, 7, 3, 1 };

    vector<int> inOrder(in, in + 7);
    vector<int> postOrder(post, post + 7);
    TreeNode* resultNode = Solution().buildTree(inOrder, postOrder);

    inOrderPrintTree(resultNode);
    freeTree(resultNode);

    return 0;
}

/*
     1
  2     3
4  5  6  7

*/

