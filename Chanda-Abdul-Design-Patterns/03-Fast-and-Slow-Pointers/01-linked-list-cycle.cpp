// PROBLEM - 1
// 141. Linked List Cycle

// given head, the head of a linked list, determine if the linked list has a cycle in it

// approach
// use two pointers - slow and fast
// slow pointer moves one step at a time
// fast pointer moves two steps at a time
// if they ever meet, there is a cycle
// if they never meet, there is no cycle

// T.C - O(n)
// S.C - O(1)

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
    bool hasCycle(ListNode *head) {
        
        ListNode *slow = head;
        ListNode *fast = head;

        while(fast != nullptr && fast->next != nullptr) {

            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast) return true;
        }

        return false;
    }
};