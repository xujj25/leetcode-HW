# Linked List Cycle 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/linked-list-cycle/description/

------

## Description

Given a linked list, determine if it has a cycle in it.

Follow up:
Can you solve it without using extra space?



## Solution
```cpp
class Solution {
public:
    bool hasCycle(ListNode *head) {
        if (head == NULL)
            return false;
        ListNode *slow = head, *fast = head;
        slow = slow -> next;
        fast = fast -> next;
        if (fast == NULL || fast -> next == NULL)
            return false;
        else
            fast = fast -> next;
        while (slow != fast && slow != NULL && fast != NULL) {
            slow = slow -> next;
            fast = fast -> next;
            if (fast == NULL || fast -> next == NULL)
                return false;
            else
                fast = fast -> next;
        }

        return slow == fast;
    }
};
```

------

## 解题描述

这道题是要检查链表是否有环。通过设立两个游标，都从head开始，一个每次往后移动一个节点，一个每次往后移动两个节点。如果两个游标相遇则说明有环。这个问题借用网上的说法就是，在操场上有两个人在跑步，一个人速度是另一个人的两倍，那这两个人肯定会相遇。
