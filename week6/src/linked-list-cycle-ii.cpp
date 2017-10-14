#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(NULL) {}
};

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

int main(int argc, char const *argv[])
{
    
    return 0;
}