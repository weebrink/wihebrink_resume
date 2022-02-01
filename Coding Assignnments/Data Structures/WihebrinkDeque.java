package WihebrinkDequeModule2Program;

/**
 * This program provides an implementation of the Deque interface
 * and demonstrates it.
 *
 * @author Matthew Wihebrink, Acuna
 * @version 2.0
 */
import java.util.NoSuchElementException;

public class WihebrinkDeque<Item> implements Deque {

    class Node<Item> {
        Item value;
        Node prev;
        Node next;

        public Node(int data) {
            value = data;
        }
    }

    Node head = null;

    Node tail = null;

    int value;
    Item element = value;
    Node deque;

    public WihebrinkDeque() {

        deque = element;
        Node head = null;
        Node tail = null;

        System.out.print(head);
    }
    /**
     * Adds one element to the front of this deque.
     * @param element the element to be added to the front of the deque
     */
    public void enqueueFront (Item element){

        Node newNode = new Node(element);
        newNode.next = head;
        newNode.prev = null;

        if (head != null) {
            head.prev = newNode;
        }

        head = newNode;
    }
    /**
     * Adds one element to the back of this deque.
     * @param element the element to be added to the back of the deque
     */
    public void enqueueBack (Item element){

        Node newNode = new Node(element);
        Node tail = head;
        newNode.next = null;

        if (head == null) {
            newNode.prev = null;
            head = newNode;
            return;
        }
        while (tail.next != null) {
            tail = tail.next;
        }

        tail.next = newNode;
        newNode.prev = tail;
    }
    /**
     * Removes and returns the element at the front of this deque.
     * Throws an exception if the deque is empty.
     * @return the element at the front of this deque
     * @throws NoSuchElementException if the deque is empty
     */
    public Item dequeueFront () {

        if (head.prev == null) {
            Item frontElement = head;
            head = head.prev = null;

            return frontElement;
        }

        if (isEmpty()) {
            throw new NoSuchElementException("Element does not exist");
        }
    }
    /**
     * Removes and returns the element at the back of this deque.
     * Throw an exception if the deque is empty.
     * @return the element at the back of the deque.
     * @throws NoSuchElementException if the deque is empty
     */
    public Item dequeueBack () {

        if (tail.next == null) {
            Item backElement = tail;
            tail = tail.next = null;

            return backElement;
        }
        if (deque == null) {
            throw new NoSuchElementException("Element does not exist");
        }
    }
    /**
     * Returns, without removing, the element at the front of this deque.
     * Should throw an exception if the deque is empty.
     * @return the first element in the deque
     * @throws NoSuchElementException if the deque is empty
     */
    public Item first () {

        Item firstElement = head;

        if (deque == null) {
            throw new NoSuchElementException("Element does not exist");
        }

        return firstElement;
    }
    /**
     * Returns, without removing, the element at the back of this deque.
     * Should throw an exception if the deque is empty.
     * @return the last element in the deque
     * @throws NoSuchElementException if the deque is empty
     */
    public Item last () {

        Item lastElement = tail;

        if (deque == null) {
            throw new NoSuchElementException("Element does not exist");
        }

        return lastElement;
    }
    /**
     * Returns true if this deque is empty and false otherwise.
     * @return if deque empty
     */
    public boolean isEmpty () {

        if (deque == null) {
            return true;
        } else {
            return false;
        }
    }
    /**
     * Returns the number of elements in this deque.
     * @return the number of elements in the deque
     */
    public int size () {

        int numberOfElements = 0;

        while (head.next != null) {
            numberOfElements++;
            head = head.next;
        }
        return numberOfElements;
    }
    /**
     * Returns a string representation of this deque. The back element
     * occurs first, and each element is separated by a space. If the
     * deque is empty, returns "empty".
     * @return the string representation of the deque
     */
    public String toString () {

        String output = "";
        if (deque.equals(null)) {
            System.out.println("Empty");
        }

        while (tail.prev != null) {
            output += element + " ";
            tail = tail.prev;
        }
        System.out.print(output);
    }

    public static void main(String[] args) {
        WihebrinkDeque deque = new WihebrinkDeque();

        //standard queue behavior
        deque.enqueueBack(3);
        deque.enqueueBack(7);
        deque.enqueueBack(4);
        deque.dequeueFront();
        deque.enqueueBack(9);
        deque.enqueueBack(8);
        deque.dequeueFront();
        System.out.println("size: " + deque.size());
        System.out.println("contents:\n" + deque.toString());

        //deque features
        System.out.println(deque.dequeueFront());
        deque.enqueueFront(1);
        deque.enqueueFront(11);
        deque.enqueueFront(3);
        deque.enqueueFront(5);
        System.out.println(deque.dequeueBack());
        System.out.println(deque.dequeueBack());
        System.out.println(deque.last());
        deque.dequeueFront();
        deque.dequeueFront();
        System.out.println(deque.first());
        System.out.println("size: " + deque.size());
        System.out.println("contents:\n" + deque.toString());
    }
}