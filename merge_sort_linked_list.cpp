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
