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
    void swap(int& a, int& b) {
        int t = a;
        a = b;
        b = t;
    }

    ListNode* partition(ListNode* low, ListNode* high) {
        int key = low -> val;
        ListNode *locNode = low;  // the location node the that key will locate at last
        for (ListNode* tempNode = low -> next; tempNode != high; tempNode = tempNode -> next) {
            if (tempNode -> val < key) {
                locNode = locNode -> next;
                swap(locNode -> val, tempNode -> val);
            }
        }
        swap(low -> val, locNode -> val);
        return locNode;
    }

    void quickSort(ListNode* head, ListNode* tail) {
        ListNode* posNode;
        if (head != tail && head -> next != tail) {  // left close, right open interval
            posNode = partition(head, tail);
            quickSort(head, posNode);
            quickSort(posNode -> next, tail);
        }
        return;
    }

    ListNode* sortList(ListNode* head) {
        quickSort(head, NULL);
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