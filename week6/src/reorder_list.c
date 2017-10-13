#include <stdio.h>
#include <malloc.h>


struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode ListNode;

void reorderList(struct ListNode* head) {
    if (head == NULL || head -> next == NULL || head -> next -> next == NULL)
        return;

    ListNode *preNode = head, *curNode = head -> next;
    while (curNode -> next != NULL) {
        preNode = curNode;
        curNode = curNode -> next;
    }

    curNode -> next = head -> next;
    preNode -> next = NULL;
    head -> next = curNode;
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