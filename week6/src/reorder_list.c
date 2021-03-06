#include <stdio.h>
#include <malloc.h>


struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;


// reverse linked list with head node
void reverseList(struct ListNode* head) {
    if (head == NULL || head -> next == NULL || head -> next -> next == NULL)
        return;

    ListNode *preNode = head -> next;
    ListNode *tail = preNode;
    ListNode *curNode = preNode -> next;
    ListNode *nextNode;
    while (curNode != NULL) {
        nextNode = curNode -> next;
        curNode -> next = preNode;
        preNode = curNode;
        curNode = nextNode;
    }

    head -> next = preNode;
    tail -> next = NULL;
}

void reorderList(struct ListNode* head) {
    if (head == NULL || head -> next == NULL || head -> next -> next == NULL)
        return;
    ListNode *mid = head, *tail = head -> next;
    while (tail && tail -> next) {
        mid = mid -> next;
        tail = tail -> next -> next;
    }
    reverseList(mid);
    ListNode *qNode = mid -> next, *qNextNode;
    mid -> next = NULL;
    ListNode *preNode = head;
    ListNode *curNode = preNode -> next;
    while (curNode != NULL) {
        preNode -> next = qNode;
        qNextNode = qNode -> next;
        qNode -> next = curNode;
        preNode = curNode;
        curNode = curNode -> next;
        qNode = qNextNode;
    }

    preNode -> next = qNode;
}

int main(int argc, char const *argv[])
{
    int listLen, i, temp;
    scanf("%d", &listLen);
    if (listLen <= 0)
        return -1;
    scanf("%d", &temp);
    ListNode* head = (ListNode*)malloc(sizeof(ListNode));
    head -> val = temp;
    head -> next = NULL;
    ListNode* curNode = head;
    for (i = 1; i < listLen; i++) {
        scanf("%d", &temp);
        curNode -> next = (ListNode*)malloc(sizeof(ListNode));
        curNode = curNode -> next;
        curNode -> val = temp;
        curNode -> next = NULL;
    }
    reorderList(head);
    curNode = head;
    while (curNode) {
        printf("%d ", curNode -> val);
        curNode = curNode -> next;
    }
    printf("\n");

    if (listLen == 1) {
        free(head);
        return 0;
    }
    ListNode* preNode = head;
    curNode = head -> next;
    while (curNode) {
        free(preNode);
        preNode = curNode;
        curNode = curNode -> next;
    }
    free(preNode);
    return 0;
}