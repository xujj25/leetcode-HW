#include <iostream>
#include <vector>
using namespace std;


class NumArray {
private:
    struct SegmentTreeNode {
        SegmentTreeNode* left;
        SegmentTreeNode* right;
        int val;
        SegmentTreeNode(int x) {
            val = x;
            left = NULL;
            right = NULL;
        }
    };

    int size;
    SegmentTreeNode *segTreeRoot;

    void pushUp(SegmentTreeNode* node) {
        node -> val = node -> left -> val + node -> right -> val;
    }

    SegmentTreeNode* build(int left, int right, vector<int>& nums) {
        if (left == right) {
            return new SegmentTreeNode(nums[left]);
        }
        SegmentTreeNode* node = new SegmentTreeNode(0);
        int mid = (left + right) / 2;
        node -> left = build(left, mid, nums);
        node -> right = build(mid + 1, right, nums);
        pushUp(node);
        return node;
    }

    void updateValInInterval(SegmentTreeNode* node, int left, int right, int index, int val) {
        if (left == right) {
            if (index == left) {
                node -> val = val;
            }
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            updateValInInterval(node -> left, left, mid, index, val);
        } else {
            updateValInInterval(node -> right, mid + 1, right, index, val);
        }
        pushUp(node);
    }

    int queryInInterval(SegmentTreeNode* node, int left, int right, int targetLeft, int targetRight) {
        if (left == targetLeft && right == targetRight) {
            return node -> val;
        }
        int mid = (left + right) / 2;
        if (targetRight <= mid)
            return queryInInterval(node -> left, left, mid, targetLeft, targetRight);
        else if (targetLeft >= mid + 1)
            return queryInInterval(node -> right, mid + 1, right, targetLeft, targetRight);
        else
            return queryInInterval(node -> left, left, mid, targetLeft, mid) +
                   queryInInterval(node -> right, mid + 1, right, mid + 1, targetRight);

    }

    void clearTree(SegmentTreeNode* node) {
        if (node != NULL) {
            clearTree(node -> left);
            clearTree(node -> right);
            delete(node);
        }
    }
public:
    NumArray(vector<int> nums) {
        size = nums.size();
        segTreeRoot = NULL;
        if (size > 0) {
            segTreeRoot = build(0, size - 1, nums);
        }
    }

    void update(int i, int val) {
        if (size == 0)
            return;
        updateValInInterval(segTreeRoot, 0, size - 1, i, val);
    }

    int sumRange(int i, int j) {
        if (size == 0)
            return 0;
        return queryInInterval(segTreeRoot, 0, size - 1, i, j);
    }
    ~NumArray() {
        clearTree(segTreeRoot);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray obj = new NumArray(nums);
 * obj.update(i,val);
 * int param_2 = obj.sumRange(i,j);
 */


int main() {
    int n, t, i;
    cout << "Input size of 'nums': ";
    cin >> n;
    vector<int> nums(n);
    cout << "Input " << n << " numbers:" << endl;
    for (i = 0; i < n; i++) {
        cin >> t;
        nums[i] = t;
    }
    NumArray numArray(nums);
    int cmd;
    int index, val;
    while (cin >> cmd) {
        if (cmd == 0) {
            cout << "Input index and value: ";
            cin >> index >> val;
            numArray.update(index, val);
        } else if (cmd == 1) {
            cout << "Input left and right: ";
            cin >> i >> t;
            cout << numArray.sumRange(i, t) << endl;
        }
    }
    return 0;
}

/*
 * ["NumArray",[-28,-39,53,65,11,-56,-65,-39,-43,97]
 * "sumRange","update","sumRange","sumRange","update","update","sumRange","sumRange","update","update"]
[[5,6],[9,27],[2,3],[6,7],[1,-82],[3,-72],[3,7],[1,8],[5,13],[4,-67]]
 * */