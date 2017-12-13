#include <iostream>
#include <string>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

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

void deleteList(ListNode *head) {
    ListNode* node = head;
    ListNode* temp;
    while (node != NULL) {
        temp = node;
        node = node -> next;
        if (temp != NULL)
            delete temp;
    }
}

int main() {
    string num1, num2;
    cin >> num1 >> num2;
    ListNode *l1 = new ListNode(num1.back() - '0');
    ListNode *l2 = new ListNode(num2.back() - '0');
    ListNode* curNode;
    int i;

    curNode = l1;
    for (i = num1.length() - 2; i >= 0; i--) {
        curNode -> next = new ListNode(num1[i] - '0');
        curNode = curNode -> next;
    }

    curNode = l2;
    for (i = num2.length() - 2; i >= 0; i--) {
        curNode -> next = new ListNode(num2[i] - '0');
        curNode = curNode -> next;
    }

    ListNode* resNode = Solution().addTwoNumbers(l1, l2);
    string res = "";
    curNode = resNode;
    while (curNode != NULL) {
        res += static_cast<char>(curNode -> val + '0');
        curNode = curNode -> next;
    }

    for (i = res.length() - 1; i >= 0; i--) {
        cout << res[i];
    }
    cout << endl;

    deleteList(l1);
    deleteList(l2);
    deleteList(resNode);

    return 0;
}
