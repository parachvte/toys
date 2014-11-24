/**
 * Class Deque
 * A double-ended queue or deque (pronounced "deck") is a generalization 
 * of a stack and a queue that supports inserting and removing items from
 * either the first or the last of the item structure.
 * 
 * Exceptions:
 * 1. throw a java.lang.NullPointerException if the client attempts to add
 * a null item;
 * 2. throw a java.util.NoSuchElementException if the client attempts to 
 * remove an item from an empty deque;
 * 3. throw a java.lang.UnsupportedOperationException if the client calls
 * the remove() method in the iterator;
 * 4. throw a java.util.NoSuchElementException if the client calls the 
 * next() method in the iterator and there are no more items to return.
 */
import java.util.Iterator;


public class Deque<Item> implements Iterable<Item> {
    private class Node {
        public Item item;
        public Node prev, next;
        Node(Item item, Node prev, Node next) {
            this.item = item;
            this.prev = prev;
            this.next = next;
        }
    }
    private Node first = null;
    private Node last = null;
    private int size = 0;
    
    /**
     * return true if deque is Empty
     */
    public boolean isEmpty() {
        return size == 0;
    }
    
    /**
     * return the size of deque
     */
    public int size() {
        return size;
    }
    
    /**
     * Add item to the first of deque
     * throw java.util.NullPointerException if a null item is being inserted
     */
    public void addFirst(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        Node oldFirst = first;
        first = new Node(item, null, oldFirst);
        if (last == null)
            last = first;
        else
            oldFirst.prev = first;
        size++;
    }
    
     /**
     * Add item to the last of deque
     * throw java.util.NullPointerException if a null item is being inserted
     */
    public void addLast(Item item) {
        if (item == null) throw new java.lang.NullPointerException();
        Node oldLast = last;
        last = new Node(item, oldLast, null);
        if (first == null)
            first = last;
        else
            oldLast.next = last;
        size++;
    }
    
    /**
     * delete and return the item at the first
     * throw java.util.NoSuchElementException if deque is empty
     */
    public Item removeFirst() {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        Item item = first.item;
        first = first.next;
        if (first == null)
            last = null;
        else
            first.prev = null;
        size--;
        return item;
    }
    
    /**
     * delete and return the item at the end
     * throw java.util.NoSuchElementException if deque is empty
     */
    public Item removeLast() {
        if (isEmpty()) throw new java.util.NoSuchElementException();
        Item item = last.item;
        last = last.prev;
        if (last == null)
            first = null;
        else
            last.next = null;
        size--;
        return item;
    }
    
    /**
     * return an iterator
     */
    public Iterator<Item> iterator() {
        return new DequeIterator();
    }
    
    private class DequeIterator implements Iterator<Item> {
        private Node current = first; // the item that behind the iterator
        
        /**
         * check if iterator has next item
         */
        public boolean hasNext() {
            return current != null;
        }
        /**
         * return next item
         * throw java.util.NoSuchElementException if no next item exist but calls next()
         */
        public Item next() {
            if (!hasNext()) throw new java.util.NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
        
        /**
         * throw java.lang.UnsupportedOperationException() if calls the method
         */
        public void remove() {
            throw new java.lang.UnsupportedOperationException();
        }
    }
}