# Reorder List 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/reorder-list/description/

------

## Description

Given a singly linked list L: L0?L1?…?Ln-1?Ln,
reorder it to: L0?Ln?L1?Ln-1?L2?Ln-2?…

You must do this in-place without altering the nodes' values.

For example,
Given {1,2,3,4}, reorder it to {1,4,2,3}.



## Solution
```c
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
```

------

## 解题描述

这道题刚拿上手还是有点不知所措。想得清楚怎么画图，就是不知道怎么实现。后面才慢慢想出，在原来的链表中间的地方截断成2个链表，将后半截用带头节点链表反转的方式进行反转，之后再合并这两个量表。主要还是考验了链表的操作，包括：
1. 快速找到链表中间节点
2. 反转链表
3. 链表合并
