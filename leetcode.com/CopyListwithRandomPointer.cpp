/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     RandomListNode *next, *random;
 *     RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
 * };
 */
class Solution {
public:
    RandomListNode *copyRandomList(RandomListNode *head) {
        map<RandomListNode*, int> ptr2id;
        map<int, RandomListNode*> new_id2ptr;
        RandomListNode *new_head = NULL;
        
        int size = 0;
        RandomListNode *p, *q, *last_q;
        
        p = head;
        while (p != NULL) {
            ptr2id[p] = size++;
            q = new RandomListNode(p->label);
            if (new_head == NULL) {
                new_head = q;
            } else {
                last_q->next = q;
            }
            new_id2ptr[size - 1] = q;
            last_q = q;
            p = p->next;
        }
        
        p = head;
        q = new_head;
        while (p != NULL) {
            if (p->random != NULL) {
                int ranId = ptr2id[p->random];
                q->random = new_id2ptr[ranId];
            }
            p = p->next;
            q = q->next;
        }

        return new_head;
    }
};