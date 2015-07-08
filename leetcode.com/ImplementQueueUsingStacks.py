class Queue:
    # initialize your data structure here.
    def __init__(self):
        self.s1 = []
        self.s2 = []

    # @param x, an integer
    # @return nothing
    def push(self, x):
        self.s1.append(x)

    # @return nothing
    def pop(self):
        self._maintain()
        del self.s2[-1]

    # @return an integer
    def peek(self):
        self._maintain()
        return self.s2[-1]

    # @return an boolean
    def empty(self):
        return not self.s2 and not self.s1

    def _maintain(self):
        if not self.s2:
            while self.s1:
                self.s2.append(self.s1[-1])
                del self.s1[-1]



if __name__ == '__main__':
    Q = Queue()
    Q.push(1)
    Q.pop()
    Q.empty()
