/**
 * Randomized queue. A randomized queue is similar to a stack or queue, except 
 * that the item removed is chosen uniformly at random from items in the data 
 * structure.
 * 
 * Exceptions:
 * 1. throw a java.lang.NullPointerException if the client attempts to add a 
 * null item;
 * 2. throw a java.util.NoSuchElementException if the client attempts to sample
 * or dequeue an item from an empty randomized queue;
 * 3. throw a java.lang.UnsupportedOperationException if the client calls the
 * remove() method in the iterator;
 * 4. throw a java.util.NoSuchElementException if the client calls the next()
 * method in the iterator and there are no more items to return.
 */
import java.util.Iterator;


public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item[] rqItems;
    private int capacity = 1;
    private int size = 0;
    
    /**
     * generate 
     */
    public RandomizedQueue() {
        rqItems = (Item[]) new Object[capacity];
    }
    
    /**
     * check if the RandomizedQueue is empty
     */
    public boolean isEmpty() {
        return size == 0;
    }
    
    /**
     * return the size of the RandomizedQueue
     */
    public int size() {
        return size;
    }
    
    private void resize(int capacity) {
        this.capacity = capacity;
        Item[] copy = (Item[]) new Object[capacity];
        for (int i = 0; i < size; i++)
            copy[i] = rqItems[i];
        rqItems = copy;
    }
    
    private void swap(int i, int j) {
        Item temp = rqItems[i];
        rqItems[i] = rqItems[j];
        rqItems[j] = temp;
    }
    
    /**
     * add the item
     * throw java.lang.NullPointerException when a null item is being inserted 
     */
    public void enqueue(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        if (size == capacity) resize(capacity * 2);
        rqItems[size++] = item;
    }
    
    /**
     * delete and return a random item
     * throw a java.util.NoSuchElementException if the client attempts to sample
     * or dequeue an item from an empty randomized queue;
     */
    public Item dequeue() {
        if (size == 0) throw new java.util.NoSuchElementException();
        int r = StdRandom.uniform(size);
        swap(size - 1, r);
        Item item = rqItems[--size];
        rqItems[size] = null;
        if (size > 8 && size == capacity / 4) resize(capacity / 2);
        return item;
    }
    
     /**
     * return (but do not delete) a random item
     * throw a java.util.NoSuchElementException if the client attempts to sample
     * or dequeue an item from an empty randomized queue;
     */
    public Item sample() {
        if (size == 0) throw new java.util.NoSuchElementException();
        int r = StdRandom.uniform(size);
        return rqItems[r];
    }
    
    /**
     * return an independent iterator over items in random order
     */
    public Iterator<Item> iterator() {
        return new RandomizedQueueIterator();
    }
    
    /**
     * inner iterator class
     * copy current rqItems[] and shuffle it, brute force hah
     */
    private class RandomizedQueueIterator implements Iterator<Item> {
        private int current = 0;
        private Item[] items;
        
        public RandomizedQueueIterator() {
            items = (Item[]) new Object[size];
            for (int i = 0; i < size; i++) items[i] = rqItems[i];
            StdRandom.shuffle(items);
        }
        public boolean hasNext() {
            return current != size;
        }
        public Item next() {
            if (!hasNext()) throw new java.util.NoSuchElementException();       
            return items[current++];
        }
        public void remove() {
            throw new java.lang.UnsupportedOperationException();
        }
    }
}