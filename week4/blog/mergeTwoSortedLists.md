# Merge Two Sorted Lists题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/merge-two-sorted-lists/description/

------

## Description

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.


## Solution
```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
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

```

------

## 解题描述
这道题还是算水题一道，只是单纯想用来复习下链表操作（第一次运行就段错误）。主要的思路也就是在两个链表中分别设置游标，比较游标位置上的数值然后将较小的数值插入到新的链表中。