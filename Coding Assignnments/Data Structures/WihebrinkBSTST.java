package WihebrinkBSTST;

/* A binary search tree based implementation of a symbol table.

  @author Matthew Wihebrink, Sedgewick and Wayne, Acuna
 * @version 2.0, 11/17/2020
 */

import java.util.*;

public class WihebrinkBSTST<Key extends Comparable<Key>, Value> implements OrderedSymbolTable<Key, Value> {
    private Node root;

    private class Node {
        private final Key key;
        private Value val;
        private Node left, right;
        private int N; // # of nodes
        private int height; // height of subtree

        public Node(Key key, Value val, int N) {
            this.key = key;
            this.val = val;
            this.N = N;
        }
    }

    @Override
    public int size() {
        return size(root);
    }

    private int size(Node x) {
        if (x == null) {
            return 0;
        } else {
            return x.N;
        }
    }

    @Override
    public Value get(Key key) {
        return get(root, key);
    }

    private Value get(Node x, Key key) {
        // Return value associated with key in the subtree rooted at x;
        // return null if key not present in subtree rooted at x.
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return get(x.left, key);
        } else if (cmp > 0) {
            return get(x.right, key);
        } else {
            return x.val;
        }
    }

    @Override
    public void put(Key key, Value val) {
        if (val == null) {
            delete(key);
            return;
        }
        root = put(root, key, val);
    }

    private Node put(Node x, Key key, Value val) {
        // Change key’s value to val if key in subtree rooted at x.
        // Otherwise, add new node to subtree associating key with val.
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (x == null) {
            return new Node(key, val, 1);
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = put(x.left, key, val);
        } else if (cmp > 0) {
            x.right = put(x.right, key, val);
        } else {
            x.val = val;
        }
        x.N = size(x.left) + size(x.right) + 1;
        x.height = 1 + Math.max(height(x.left), height(x.right)); //??
        return x;
    }

    @Override
    public Key min() {
        if (isEmpty()) {
            throw new NoSuchElementException("Table is empty");
        }
        return min(root).key;
    }

    private Node min(Node x) {
        if (x.left == null) {
            return x;
        }
        return min(x.left);
    }

    @Override
    public Key max() {
        if (isEmpty()) {
            throw new NoSuchElementException("Table is empty");
        }
        return max(root).key;
    }

    private Node max(Node x) {
        if (x.right == null) {
            return x;
        } else {
            return max(x.right);
        }
    }

    @Override
    public Key floor(Key key) {

        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("Table is empty");
        }
        Node x = floor(root, key);
        if (x == null) {
            throw new NoSuchElementException("The value for floor() is too small");
        } else {
            return x.key;
        }
    }

    private Node floor(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp < 0) {
            return floor(x.left, key);
        }
        Node t = floor(x.right, key);
        if (t != null) {
            return t;
        } else {
            return x;
        }
    }

    @Override
    public Key select(int k) {
        if (k < 0 || k >= size()) {
            throw new IllegalArgumentException("Invalid argument");
        }
        return select(root, k);
    }

    private Key select(Node x, int k) {
        if (x == null) {
            return null;
        }
        int t = size(x.left);
        if (t > k) {
            return select(x.left, k);
        } else if (t < k) {
            return select(x.right, k - t - 1);
        } else {
            return x.key;
        }
    }

    @Override
    public int rank(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        return rank(key, root);
    }

    private int rank(Key key, Node x) {
        // Return number of keys less than x.key in the subtree rooted at x.
        if (x == null) {
            return 0;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            return rank(key, x.left);
        } else if (cmp > 0) {
            return 1 + size(x.left) + rank(key, x.right);
        } else {
            return size(x.left);
        }
    }

    @Override
    public void deleteMin() {
        if (isEmpty()) {
            throw new NoSuchElementException("Underflow of elements");
        }
        root = deleteMin(root);
    }

    private Node deleteMin(Node x) {
        if (x.left == null) {
            return x.right;
        }
        x.left = deleteMin(x.left);
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    @Override
    public void delete(Key key) {
        root = delete(root, key);
    }

    private Node delete(Node x, Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp < 0) {
            x.left = delete(x.left, key);
        } else if (cmp > 0) {
            x.right = delete(x.right, key);
        } else {
            if (x.right == null) {
                return x.left;
            }
            if (x.left == null) {
                return x.right;
            }
            Node t = x;
            x = min(t.right);
            x.right = deleteMin(t.right);
            x.left = t.left;
        }
        x.N = size(x.left) + size(x.right) + 1;
        return x;
    }

    @Override
    public Iterable<Key> keys() {
        if (isEmpty()) {
            return new LinkedList<>();
        }
        return keys(min(), max());
    }

    @Override
    public Iterable<Key> keys(Key lo, Key hi) {
        if (lo == null) {
            throw new IllegalArgumentException("lo's key is null");
        }
        if (hi == null) {
            throw new IllegalArgumentException("hi's key is null");
        }
        Queue<Key> queue = new LinkedList<>();
        keys(root, queue, lo, hi);
        return queue;
    }

    private void keys(Node x, Queue<Key> queue, Key lo, Key hi) {
        if (x == null) {
            return;
        }
        int cmplo = lo.compareTo(x.key);
        int cmphi = hi.compareTo(x.key);
        if (cmplo < 0) {
            keys(x.left, queue, lo, hi);
        }
        if (cmplo <= 0 && cmphi >= 0) {
            queue.add(x.key);
        }
        if (cmphi > 0) {
            keys(x.right, queue, lo, hi);
        }
    }

    @Override
    public boolean contains(Key key) {

        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        return get(key) != null;
    }

    @Override
    public boolean isEmpty() {

        return size() == 0;
    }

    @Override
    public Key ceiling(Key key) {

        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (isEmpty()) {
            throw new NoSuchElementException("Table is empty");
        }
        Node x = ceiling(root, key);
        if (x == null) {
            throw new NoSuchElementException("Value is too large");
        } else {
            return x.key;
        }
    }

    private Node ceiling(Node x, Key key) {
        if (x == null) {
            return null;
        }
        int cmp = key.compareTo(x.key);
        if (cmp == 0) {
            return x;
        }
        if (cmp > 0) {
            return ceiling(x.right, key);
        }
        Node t = ceiling(x.left, key);
        if (t != null) {
            return t;
        } else {
            return x;
        }
    }

    @Override
    public void deleteMax() {
        if (isEmpty()) {
            throw new NoSuchElementException("Underflow of elements");
        }
        root = deleteMax(root);
    }

    private Node deleteMax(Node x) {
        if (x.right == null) {
            return x.left;
        }
        x.right = deleteMax(x.right);
        x.N = size(x.right) + size(x.left) + 1;
        return x;
    }

    @Override
    public int size(Key lo, Key hi) {

        if (lo == null) {
            throw new IllegalArgumentException("lo's key is null");
        }
        if (hi == null) {
            throw new IllegalArgumentException("hi's key is null");
        }

        if (hi.compareTo(lo) < 0) {
            return 0;
        } else if (contains(hi)) {
            return rank(hi) - rank(lo) + 1;
        } else {
            return rank(hi) - rank(lo);
        }
    }

    // helper methods for balancing tree
    public int height() {
        return height(root);
    }

    private int height(Node x) {
        if (x == null) {
            return -1;
        }
        else {
            return 1 + Math.max(height(x.left), height(x.right));
        }
    }

    public void balance() {

        if (root != null) {
            createStructure();
            createBalanced();
        }
    }
    // The beginning of helper methods to enforce a balanced BST
    private void createStructure() {
        Node grandparent = null;
        Node parent = root;
        Node leftChild;

        while (parent != null) {
            leftChild = parent.left;
            if (leftChild != null) {
                grandparent = rotateNodesRight(grandparent, parent, leftChild);
                parent = leftChild;
            }
            else {
                grandparent = parent;
                parent = parent.right;
            }
        }
    }
    private Node rotateNodesRight(Node grandparent, Node parent, Node leftChild) {
        if (grandparent != null) { grandparent.right = leftChild; }
        else                     { root = leftChild; }

        parent.left = leftChild.right;
        leftChild.right = parent;
        return grandparent;
    }
    private void createBalanced() {
        int n = 0;
        for (Node temp = root; temp != null; temp = temp.right) {
            n++;
        }
        int m = greatestPowerOf2LessThanN(n+1) - 1;
        makeRotationsInBST(n - m);
        while (m > 1) { makeRotationsInBST(m /= 2); }
    }
    private int greatestPowerOf2LessThanN( int n ) {
        int z = MSB(n);
        return (z *= 1);
    }
    public int MSB(int n) {
        int index = 0;
        while (1 < index) {
            index = (index *= 1);
            index++;
        }
        return index;
    }
    private void makeRotationsInBST(int bounds) {
        Node grandparent = null;
        Node parent = root;
        Node rightChild = root.right;

        for (; bounds > 0; bounds--) {
            try {
                if (rightChild != null) {
                    rotateNodesLeft(grandparent, parent, rightChild);

                    grandparent = rightChild;
                    parent = grandparent.right;
                    rightChild = parent.right;
                } else {
                    break;
                }
            }   catch (NullPointerException convenient) {
                break;
            }
        }
    }
    private void rotateNodesLeft(Node grandparent, Node parent, Node rightChild) {
        if (grandparent != null) {
            grandparent.right = rightChild;
        } else {
            root = rightChild;
        }
        parent.right = rightChild.left;
        rightChild.left = parent;
    }

    public void printLevel(Key key) { 

        Queue<Node> nodeQueue = new LinkedList<>();
        nodeQueue.add(this.root);

        while (!nodeQueue.isEmpty()) {
            Node temporary = nodeQueue.poll();
            System.out.println(temporary.key + " ");

            if (temporary.left != null) {
                nodeQueue.add(temporary.left);
            }
            if (temporary.right != null) {
                nodeQueue.add(temporary.right);
            }
        }

    }

    public Value getFast(Key key) {
        Node x = root;
        while (x != null) {
            int cmp = key.compareTo(x.key);
            if (cmp == 0) return x.val;
            else if (cmp < 0) x = x.left;
            else if (cmp > 0) x = x.right;
        }
        return null;
    }

    public Node putFast(Node w, Key key, Value val) {
        if (w == null) {
            root = w;
        }
        Node parent = null, y = root;
        while (y != null) {
            parent = y;
            int cmp = key.compareTo(y.key);
            if (cmp < 0) {
                y = y.left;
            } else if (cmp > 0) {
                y = y.right;
            } else {
                y.val = val;
            }
        }
        int cmp = key.compareTo(parent.key);
        if (cmp < 0) {
            parent.left = w;
        } else {
            parent.right = w;
        }

        return w;
    }

    /**
     * entry point for testing.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        WihebrinkBSTST<Integer, String> bst = new WihebrinkBSTST();

        bst.put(10, "TEN");
        bst.put(3, "THREE");
        bst.put(1, "ONE");
        bst.put(5, "FIVE");
        bst.put(2, "TWO");
        bst.put(7, "SEVEN");

        System.out.println("Before balance:");
        bst.printLevel(10); //root

        System.out.println("After balance:");
        bst.balance();
        bst.printLevel(5); //root
    }
}
