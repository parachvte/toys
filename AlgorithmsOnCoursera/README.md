# Algorithms

### About this repo

My solutions for the algorithm course on [Coursera.org](https://www.coursera.org/).

Course: <b>[Algorithms, Part I](https://class.coursera.org/algs4partI-003/class)</b> by Kevin Wayne, Robert Sedgewick


### Week 1: Percolation

[Specification](http://coursera.cs.princeton.edu/algs4/assignments/percolation.html)

Use <b>Union-Find</b> data structure to complete it. 

A problem occured that the '<b>backwash</b>' didn't count, see the assignment [checklist](http://coursera.cs.princeton.edu/algs4/checklists/percolation.html).

To solve this problem, I use another Union-Find data structure `fullUnionFind` to avoid 'backwash', here `fullUnionFind` is used for checking whether a grid is full, and the usual Union-Find data structure `unionFind` is used for checking whether the whole system percolates.

### Week 2: queues

[Specification](http://coursera.cs.princeton.edu/algs4/assignments/queues.html)

Implement:

* <b>Deque</b>: double end queue
* <b>RandomizedQueue</b>:

```
      dequeue(): return and delete a random item
      sample(): return (but not delete) a random item
```
* Implement <b>Iterator</b> interface for Deque and RandomizedQueue 
* <b>Subset</b>: little test program for RandomizedQueue

Having trouble to deal with

    Test 9: Create two independent iterators to same randomized queue

An copy of the whole item array to Iterator class can pass this test(but too BF!)
