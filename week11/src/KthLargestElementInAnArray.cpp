#include <iostream>
#include <vector>
using namespace std;

class Solution {
    void heapFixDown(vector<int>& arr, int start, int end) {
        int dad = start;
        int son = dad * 2 + 1;
        while (son <= end) {
            if (son + 1 <= end && arr[son] < arr[son + 1])
                son++;
            if (arr[dad] >= arr[son]) {
                return;
            } else {
                swap(arr[dad], arr[son]);
                dad = son;
                son = dad * 2 + 1;
            }
        }
    }

    void makeHeap(vector<int>& arr, int len) {
        for (int i = len / 2 - 1; i >= 0; i--)
            heapFixDown(arr, i, len - 1);
    }

    void heapSort(vector<int>& arr) {
        int size = arr.size();
        makeHeap(arr, size);
        for (int i = size - 1; i >= 1; i--) {
            swap(arr[i], arr[0]);
            heapFixDown(arr, 0, i - 1);
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        heapSort(nums);
        return nums[k - 1];
    }
};

int main(int argc, char const *argv[])
{
    int k, t;
    int size;
    cin >> k >> size;
    vector<int> nums(size);
    for (int i = 0; i < size; i++) {
        cin >> t;
        nums[i] = t;
    }

    cout << "Kth largest: " << Solution().findKthLargest(nums, k) << endl;
    cout << "nums: ";
    for (int i = 0; i < size; i++)
        cout << nums[i] << " ";
    cout << endl;
    return 0;
}