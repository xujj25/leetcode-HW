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

int main(int argc, char const *argv[])
{
    
    return 0;
}