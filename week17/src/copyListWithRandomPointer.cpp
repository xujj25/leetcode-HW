#include <iostream>
using namespace std;


struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        if (head == NULL)
            return NULL;
        RandomListNode *node1, *node2;
        for (node1 = head; node1 != NULL; node1 = node1 -> next -> next) {
            node2 = new RandomListNode(node1 -> label);
            node2 -> next = node1 -> next;
            node1 -> next = node2;
        }

        RandomListNode* resNode = head -> next;
        for (node1 = head; node1 != NULL; node1 = node1 -> next -> next) {
            node2 = node1 -> next;
            node2 -> random = node1 -> random ? node1 -> random -> next : NULL;
        }

        for (node1 = head; node1 != NULL; node1 = node1 -> next) {
            node2 = node1 -> next;
            node1 -> next = node2 -> next;
            node2 -> next = node2 -> next ? node2 -> next -> next : NULL;
        }
        return resNode;
    }
};


int main() {
    RandomListNode *n1 = new RandomListNode(1);
    RandomListNode *n2 = new RandomListNode(2);
    RandomListNode *n3 = new RandomListNode(3);
    RandomListNode *n4 = new RandomListNode(4);
    n1 -> next = n2;
    n2 -> next = n3;
    n3 -> next = n4;
    RandomListNode *resNode = Solution().copyRandomList(n1);
    RandomListNode *node;
    for (node = resNode; node != NULL; node = node -> next) {
        cout << node -> label << " ";
    }
    cout << endl;
    delete(n1);
    delete(n2);
    delete(n3);
    delete(n4);
    node = resNode;
    while (node != NULL) {
        RandomListNode* tempNode = node;
        node = node -> next;
        delete(tempNode);
    }
    return 0;
}