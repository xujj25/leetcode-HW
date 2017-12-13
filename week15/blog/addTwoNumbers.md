# Add Two Numbers 题解

*原创文章，拒绝转载*

题目来源：https://leetcode.com/problems/add-two-numbers/description/

------

## Description

You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order** and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

## Example

```

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

```

## Solution
```cpp
class Solution {
private:
    ListNode* copyList(ListNode* listHeadNode) {
        if (listHeadNode == NULL)
            return NULL;
        ListNode* resHeadNode = new ListNode(listHeadNode -> val);
        ListNode* resCurNode = resHeadNode;
        ListNode* listCurNode = listHeadNode -> next;
        while (listCurNode != NULL) {
            resCurNode -> next = new ListNode(listCurNode -> val);
            resCurNode = resCurNode -> next;
            listCurNode = listCurNode -> next;
        }
        return resHeadNode;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == NULL)
            return copyList(l2);
        if (l2 == NULL)
            return copyList(l1);
        bool isOverflow = false;
        int curVal = l1 -> val + l2 -> val;
        if (curVal >= 10) {
            isOverflow = true;
        }
        ListNode* resHeadNode = new ListNode(curVal % 10);
        ListNode* resPreNode = resHeadNode;
        ListNode* l1CurNode = l1 -> next;
        ListNode* l2CurNode = l2 -> next;
        while (l1CurNode != NULL && l2CurNode != NULL) {
            curVal = l1CurNode -> val + l2CurNode -> val;
            if (isOverflow)
                curVal++;
            resPreNode -> next = new ListNode(curVal % 10);
            isOverflow = (curVal / 10 > 0);

            resPreNode = resPreNode -> next;
            l1CurNode = l1CurNode -> next;
            l2CurNode = l2CurNode -> next;
        }
        if (l1CurNode == NULL)
            resPreNode -> next = copyList(l2CurNode);
        else
            resPreNode -> next = copyList(l1CurNode);

        if (isOverflow) {
            if (resPreNode -> next == NULL) {
                resPreNode -> next = new ListNode(1);
            } else {
                while (true) {
                    if (resPreNode -> next == NULL) {
                        resPreNode -> next = new ListNode(1);
                        break;
                    } else {
                        curVal = resPreNode -> next -> val + 1;
                        if (curVal >= 10) {
                            resPreNode -> next -> val = curVal % 10;
                            resPreNode = resPreNode -> next;
                        } else {
                            resPreNode -> next -> val = curVal;
                            break;
                        }
                    }
                }
            }
        }
        return resHeadNode;
    }
};
```

------

## 解题描述

这道题可以说解决的是数字相加的问题，但是由于数字的长度不确定，输入的数字可能是现有的内置数据类型无法存储的，所以像题目中给出的方法是，利用链表来记录数字，然后针对链表中的每一个节点的值进行相加。

明确了题目的要求之后，很快就可以清楚，题目最需要解决的问题就是链表边界和相加进位的问题。我的做法算是简单的对特殊情况打补丁。