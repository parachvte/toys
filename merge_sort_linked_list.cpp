/*
 * File     :   merge_sort_linked_list.cpp
 * Author   :   Ryannnnnnn (ryannx6@gmail.com)
 * Date     :   2014/06/02
 *
 * 今天@whimsy在写某道某公司面试的题目，也就是用链表写个Merge-Sort。
 * 然后碰到了坑，说难怪当初手写没写对。
 *
 * 于是我就写了一下，大概花了40分钟吧= =，记一下：
 * 1. 首先太久没写C++了，一来就被指针给小坑了一下，也就是MData **head，这里用**才是对的...不然值不会变
 * 2. 然后顺着归并的思路调下来，碰到的坑就是divide的时候要顺手把两个链表给切断，参见有注释那里
 * 3. 接下来就是merge的时候，把某个链表的头扔到新链表中。那么要先fetch一下它的下一个。这个属于脑抽筋了，
 *    写的时候就啪啪啪根本没想，然后本来就几乎不写链表的自己作死 : (
 * 4. 最后答案正确了，但是输出会死循环，这是因为merge就直接调用push扔东西进链表了，但是扔的东西不像是
 *    一开始添加那样，item->next本来就是空的。所以在push有注释那里，需要保证加东西进来后，新的东西也是
 *    item->next为空。
 *
 * 总的来说，思路还算清晰不难写，主要就是一些细节的处理。而这些细节我不认为适合面试时用，面试的话相对
 * 思路更重要一些。
 *
 * Fin
 */

#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define MAXN 100
#define MAX_VALUE 10000

int data[MAXN];
int dataA[MAXN];
int nData;

struct MData {
    int value;
    MData *next;
};
MData *head;

void push(MData **head, MData *cur) {
    if (*head == NULL) {
        cur->next = NULL; // little trick, check that ``cur`` must be the only element of the link
        *head = cur;
    } else {
        cur->next = *head;
        *head = cur;
    }
}

MData* reversed(MData *head) {
    MData *p = head, *q, *last = NULL;
    while (p != NULL) {
        q = p->next;
        p->next = last;
        last = p;
        p = q;
    }
    return last;
}

void print(MData *head) {
    while (head != NULL) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void clean(MData *head) {
    if (head->next != NULL) clean(head->next);
    free(head);
}

MData* merge_sort(MData *head, int num) {
    if (num == 1) {
        return head;
    }

    int mid_num = num / 2;
    MData *mid, *p = head;

    for (int i = 0; i < mid_num - 1; i++) p = p->next;
    mid = p->next;
    p->next = NULL; // remember to split them to two different parts, the tail of the first part must be cleaned

    head = merge_sort(head, mid_num);
    mid = merge_sort(mid, num - mid_num);

    MData *new_head = NULL, *next_head, *next_mid;
    while (head != NULL || mid != NULL) {
        next_head = head ? head->next : NULL; // head->next will be rewrite later, so fetch it first
        next_mid = mid ? mid->next : NULL;
        if (mid == NULL || (head != NULL && head->value <= mid->value)) {
            push(&new_head, head);
            head = next_head;
        } else {
            push(&new_head, mid);
            mid = next_mid;
        }
    }
    return reversed(new_head);
}

int main() {
    srand((unsigned)time(NULL));

    // generate data
    int n = MAXN;
    for (int i = 0; i < n; i++) {
        data[i] = rand() % MAX_VALUE;
        printf("%d ", data[i]);
    }
    printf("\n");

    // qsort
    memcpy(dataA, data, sizeof(data[0]) * n);
    sort(dataA, dataA + n);
    for (int i = 0; i < n; i++) {
        printf("%d ", dataA[i]);
    }
    printf("\n");

    // merge sort
    for (int i = 0; i < n; i++) {
        MData *cur = (MData *) malloc(sizeof(data[0]));
        cur->value = data[i];
        push(&head, cur);
    }
    head = reversed(head);
    head = merge_sort(head, n);
    print(head);
    clean(head); // clean
    
    return 0;
}
