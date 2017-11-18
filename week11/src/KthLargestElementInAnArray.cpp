#include <iostream>
#include <vector>
using namespace std;

void printArr(vector<int>& arr, int len) {
    for (int i = 0; i < len; i++)
        cout << arr[i] << " ";
    cout << endl;
}

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
        for (int i = len / 2 - 1; i >= 0; i--) {
            heapFixDown(arr, i, len - 1);
            // printArr(arr, len);
        }

        // cout << "finish makeHeap" << endl;
    }

    void heapSort(vector<int>& arr, int len) {        
        makeHeap(arr, len);

        for (int i = len - 1; i >= 1; i--) {
            swap(arr[i], arr[0]);
            heapFixDown(arr, 0, i - 1);
            // printArr(arr, len);
        }
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int len = nums.size();
        heapSort(nums, len);
        return nums[len - k];
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