#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    void insert(ListNode* &head, int x) {
        if (head == NULL) {
            head = new ListNode(x);
        } else {
            if (x <= head -> val) {
                ListNode* node = new ListNode(x);
                node -> next = head;
                head = node;
                return;
            }
            ListNode* preNode = head;
            ListNode* curNode = head -> next;
            while (curNode != NULL) {
                if (preNode -> val <= x && x <= curNode -> val) {
                    ListNode* node = new ListNode(x);
                    preNode -> next = node;
                    node -> next = curNode;
                    return;
                }
                preNode = curNode;
                curNode = curNode -> next;
            }
            preNode -> next = new ListNode(x);
        }
    }
public:
    ListNode* insertionSortList(ListNode* head) {
        ListNode* curNode = head;
        ListNode* resHead = NULL;
        while (curNode != NULL) {
            insert(resHead, curNode -> val);
            curNode = curNode -> next;
        }
        return resHead;
    }
};

void printList(ListNode* head) {
    ListNode* curNode = head;
    while (curNode != NULL) {
        cout << curNode -> val << " ";
        curNode = curNode -> next;
    }
    cout << endl;
}

void deleteList(ListNode* head) {
    if (head == NULL)
        return;
    ListNode* preNode = head;
    ListNode* curNode = head -> next;
    while (curNode != NULL) {
        delete(preNode);
        preNode = curNode;
        curNode = curNode -> next;
    }
    delete(preNode);
}

int main() {
    int n;
    int temp;

    cin >> n;
    if (n <= 1)
        return -1;

    cin >> temp;
    ListNode* head = new ListNode(temp);
    ListNode* preNode = head;
    for (int i = 1; i < n; i++) {
        cin >> temp;
        preNode -> next = new ListNode(temp);
        preNode = preNode -> next;
    }
    ListNode* resNode = Solution().insertionSortList(head);
    printList(resNode);
    deleteList(head);
    deleteList(resNode);
    return 0;
}