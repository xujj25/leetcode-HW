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
    TreeNode* getSubTree(vector<int>& nums, int start, int end) {
        TreeNode* resultNode;
        if (start == end) {
            resultNode = new TreeNode(nums[start]);
            return resultNode;
        }
        int maxIdx = start;
        int i;
        for (i = start; i <= end; i++) {
            if (nums[i] > nums[maxIdx])
                maxIdx = i;
        }
        resultNode = new TreeNode(nums[maxIdx]);
        if (maxIdx > start) {
            resultNode -> left = getSubTree(nums, start, maxIdx - 1);
        }
        if (maxIdx < end) {
            resultNode -> right = getSubTree(nums, maxIdx + 1, end);
        }
        return resultNode;
    }

    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        if (nums.empty())
            return NULL;
        return getSubTree(nums, 0, nums.size() - 1);
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
    int n;
    cin >> n;
    vector<int> nums(n);
    int i, t;
    for (i = 0; i < n; i++) {
        cin >> t;
        nums[i] = t;
    }
    TreeNode* resultNode = Solution().constructMaximumBinaryTree(nums);
    inOrderPrintTree(resultNode);
    freeTree(resultNode);

    return 0;
}