# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @param {ListNode} head
    # @return {boolean}
    def isPalindrome(self, head):
        p = q = head
        last_q = None
        while p and p.next:
            p = p.next.next

            q_next = q.next  # try to reverse list
            q.next = last_q
            last_q = q
            q = q_next

        if p:  # odd number
            p, q = last_q, q.next
        else:  # even number
            p, q = last_q, q

        while p and q:
            if p.val != q.val:
                return False
            p = p.next
            q = q.next

        return True


if __name__ == '__main__':
    # generate list
    head = last = None
    for i in range(5):
        node = ListNode(i)
        if not head:
            head = last = node
        else:
            last.next = node
            last = node
    for i in range(4, -1, -1):
        node = ListNode(i)
        last.next = node
        last = node

    i = head
    while i:
        print(i.val)
        i = i.next

    # solution
    s = Solution()
    print(s.isPalindrome(head))
