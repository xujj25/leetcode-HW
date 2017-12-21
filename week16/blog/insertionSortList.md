# Insertion Sort List 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/insertion-sort-list/description/

------

## Description

Sort a linked list using insertion sort.

## Solution
```cpp

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

```

------

## 解题描述

这道题考察的是插入排序，我考虑的做法是遍历原来的链表，每次将取到的数值在新的链表中找到相应的位置，然后拆开新链表，将新的节点插入进去再接上前后的节点。