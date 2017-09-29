#include <iostream>
using namespace std;


/* Definition for singly-linked list. */ 
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode *n1, *n2, *preNode;
        ListNode *head = new ListNode(0);
        preNode = head;
        n1 = l1, n2 = l2;
        while (true) {
            if (!n1 && !n2) {
                break;
            } else if (!n1 && n2) {
                preNode -> next = new ListNode(n2 -> val);
                n2 = n2 -> next;
            } else if (n1 && !n2) {
                preNode -> next = new ListNode(n1 -> val);
                n1 = n1 -> next;
            } else {
                if (n1 -> val < n2 -> val) {
                    preNode -> next = new ListNode(n1 -> val);
                    n1 = n1 -> next;
                } else {
                    preNode -> next = new ListNode(n2 -> val);
                    n2 = n2 -> next;
                }
            }
            preNode = preNode -> next;
        }
        return head -> next;
    }
};

int main(int argc, char const *argv[])
{
    int len1, len2, i, val;
    ListNode *h1, *h2, *curNode;
    cin >> len1;
    cin >> val;
    curNode = h1 = new ListNode(val);
    for (i = 0; i < len1 - 1; i++) {
        cin >> val;
        curNode -> next = new ListNode(val);
        curNode = curNode -> next;
    }
    cin >> len2;
    cin >> val;
    curNode = h2 = new ListNode(val);
    for (i = 0; i < len2 - 1; i++) {
        cin >> val;
        curNode -> next = new ListNode(val);
        curNode = curNode -> next;
    }
    Solution solu;
    curNode = solu.mergeTwoLists(h1, h2);
    while (curNode) {
        cout << curNode -> val << " ";
        curNode = curNode -> next;
    }
    cout << endl;
    return 0;
}