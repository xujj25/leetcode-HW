# Linked List Cycle II 题解

题目来源：https://leetcode.com/problems/linked-list-cycle-ii/description/

------

## Description

Given a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

**Note:** Do not modify the linked list.

**Follow up:**
Can you solve it without using extra space?



## Solution
```cpp
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == NULL)
            return NULL;
        ListNode *slow = head, *fast = head;
        slow = slow -> next;
        fast = fast -> next;
        if (fast == NULL || fast -> next == NULL)
            return NULL;
        else
            fast = fast -> next;
        while (slow != fast && slow != NULL && fast != NULL) {
            slow = slow -> next;
            fast = fast -> next;
            if (fast == NULL || fast -> next == NULL)
                return NULL;
            else
                fast = fast -> next;
        }

        if (slow != fast)
            return NULL;
        
        slow = head;
        while (slow != fast) {
            slow = slow -> next;
            fast = fast -> next;
        }
        return slow;
    }
};
```

------

## 解题描述

这道题同样是带环链表系列的题目，是找到链表环的起点。在判断链表是否有环的基础上要增加对环的起点的判断，这就需要搞清楚其中的数学关系：

设链表环起点距离链表头StartLen，链表环的长度为CycleLen，快慢游标第一次相遇的位置距离链表环起点长度为d（不必求出），则有

对慢游标，s1 = StartLen + n * CycleLen + d，

对快游标，s2 = StartLen + m * CycleLen + d

而s2 = 2 * s1

则有 StartLen = (m - 2 * n) * CycleLen - d

所以当第一次相遇之后，将慢游标设为head，然后快慢游标每次只向后移动一个节点，则再次相遇的位置会在链表环的起点

具体参考博客：[判断单向链表是否有环，环起点，环长，链表长](http://www.cnblogs.com/huanyou/p/5944296.html)
