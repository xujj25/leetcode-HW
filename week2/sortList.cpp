#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:

	int partition(vector<int>& arr, int low, int high) {
		int key = arr[low];

		while (low < high) {
			while (low < high && key <= arr[high])
				high--;
			if (low < high) {
				arr[low] = arr[high];
				low++;
			}
			while (low < high && key >= arr[low])
				low++;
			if (low < high) {
				arr[high] = arr[low];
				high--;
			}
		}
		arr[low] = key;

		return low;
	}

	void quickSort(vector<int>& arr, int start, int end) {
		int pos;
		if (start < end) {
			pos = partition(arr, start, end);
			quickSort(arr, start, pos - 1);
			quickSort(arr, pos + 1, end);
		}
		return;
	}

    ListNode* sortList(ListNode* head) {
    	if (head == NULL || head -> next == NULL) {
    		return head;
    	}

        ListNode* temp = head;
        vector<int> arr;

        while (temp != NULL) {
        	arr.push_back(temp -> val);
        	temp = temp -> next;
        }

        quickSort(arr, 0, arr.size() - 1);

        temp = head;
        int i = 0;
        while (temp != NULL) {
        	temp -> val = arr[i++];
        	temp = temp -> next;
        }

        return head;
    }
};

int main() {
	int count, i, num;
	cout << "Please input count of numbers: ";
	cin >> count;
	if (count == 0)
		return 0;

	cout << "Please input " << count << " numbers: " << endl;

	cin >> num;
	ListNode* curNode = new ListNode(num);
	ListNode* head = curNode;
	for (i = 1; i < count; i++) {
		cin >> num;
		curNode -> next = new ListNode(num);
		curNode = curNode -> next;
	}

	Solution solu;
	curNode = solu.sortList(head);
	while (curNode) {
		cout << curNode -> val << " ";
		curNode = curNode -> next;
	}
	cout << endl;

	return 0;
}