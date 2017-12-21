#include <iostream>
#include <vector>
using namespace std;

void printVec(vector<int>& vec) {
    for (auto& e: vec) {
        cout << e << " ";
    }
    cout << endl;
}

class NumArray {
private:
    vector<int> segTree;
    int size;

    void pushUp(int root) {
        segTree[root] = segTree[root * 2 + 1] + segTree[root * 2 + 2];
    }

    void build(int root, int left, int right, vector<int>& nums) {
        if (left == right) {
            segTree[root] = nums[left];
            return;
        }
        int mid = (left + right) / 2;
        build(root * 2 + 1, left, mid, nums);
        build(root * 2 + 2, mid + 1, right, nums);
        pushUp(root);
    }

    void updateValInInterval(int root, int left, int right, int index, int val) {
        if (left == right) {
            if (index == left) {
                segTree[root] = val;
            }
            return;
        }
        int mid = (left + right) / 2;
        if (index <= mid) {
            updateValInInterval(root * 2 + 1, left, mid, index, val);
        } else {
            updateValInInterval(root * 2 + 2, mid + 1, right, index, val);
        }
        pushUp(root);
    }

    int queryInInterval(int root, int left, int right, int targetLeft, int targetRight) {
        if (left == targetLeft && right == targetRight) {
            return segTree[root];
        }
        int mid = (left + right) / 2;
        if (targetRight <= mid)
            return queryInInterval(root * 2 + 1, left, mid, targetLeft, targetRight);
        else if (targetLeft >= mid + 1)
            return queryInInterval(root * 2 + 2, mid + 1, right, targetLeft, targetRight);
        else
            return queryInInterval(root * 2 + 1, left, mid, targetLeft, mid) +
                   queryInInterval(root * 2 + 2, mid + 1, right, mid + 1, targetRight);

    }
public:
    NumArray(vector<int> nums) {
        size = nums.size();
        if (size > 0) {
            segTree = vector<int>(size * 3);
            build(0, 0, size - 1, nums);

            // test
            printVec(segTree);
        }
    }

    void update(int i, int val) {
        if (size == 0)
            return;
        updateValInInterval(0, 0, size - 1, i, val);
    }

    int sumRange(int i, int j) {
        if (size == 0)
            return 0;
        return queryInInterval(0, 0, size - 1, i, j);
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