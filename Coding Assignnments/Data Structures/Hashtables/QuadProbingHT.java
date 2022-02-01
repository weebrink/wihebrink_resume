package WihebrinkHT;

/**
 * Implements a quadratic probing hash table.
 * Completion Time: 12 hours.
 *
 * @author Wihebrink
 * @version 1.0, 11/24/2020
 */

import java.util.LinkedList;
import java.util.Queue;

public class QuadProbingHT<Key, Value> extends LinearProbingHT implements SymbolTable {

    private class Entry<EntryKey, EntryValue> {

        Key key;
        Value value;
        final int hash;
        Entry next;

        Entry(int h, Key k, Value v, Entry node) {
            value = v;
            next = node;
            key = k;
            hash = h;

    }
    private static final int start_size = 997;

    private int N;
    private int M;
    private Key[] keys;
    private Value[] vals;

    public QuadProbingHT() {
        this(start_size);
    }

    public QuadProbingHashST(int size) {
        M = size;
        N = 0;
        keys = (Key[]) new Object[M];
        vals = (Value[]) new Object[M];
    }

    private int hash(Key key, int collision) {
        int i = collision;
        return ((key.hashCode() & 0x7fffffff) + i * i) % M;
    }

    @Override
    public int size() {
        return N;
    }

    private void resize(int size) {
        QuadProbingHT<Key, Value> temp_table = new QuadProbingHT<>(size);
        for (int i = 0; i < M; i++) {
            if (keys[i] != null) {
                temp_table.put(keys[i], vals[i]);
            }
        }
        keys = temp_table.keys;
        vals = temp_table.vals;
        M = temp_table.M;
    }

    @Override
    public void put(Key key, Value val) {

        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (val ==null) {
            delete(key);
            return;
        }
        if (N >= M/2) {
            resize(2*M);
        }
        int i;
        for (i = hash(key); keys[i] != null; i = (i * i) % M) {
            if (keys[i].equals(key)) {
                vals[i] = val;
                return;
            }
            keys[i] = key;
            vals[i] = val;
            N++;
        }
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public Value get(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        for (int i = hash(key); keys[i] != null; i = (i * i) % M) {
            if (keys[i].equals(key)) {
                return vals[i];
            }
            return null;
        }
    }

    @Override
    boolean contains(Key key) {
        return get(key) != null;
    }

    @Override
    public void delete(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (!contains(key)) {
            return;
        } else {
            int i = hash(key);
            while (!key.equals(keys[i])) {
                i = (i * i) % M;
                keys[i] = null;
                vals[i] = null;
                i = (i * i) % M;
            }
            while (keys[i] != null) {
                Key fixKey = keys[i];
                Value fixValue = vals[i];
                keys[i] = null;
                vals[i] = null;
                N--;
                put(fixKey, fixValue);
                i = (i * i) % M;
            }
            N--;
        }
        if (N > 0 && N <= M/8) {
            resize(M/2);
        }
    }

    @Override
    public Iterable<Key> keys() {
        Queue<Key> queue = new Queue<Key>();
        for (int i = 0; i < M; i++) {
            if (keys[i] != null) {
                queue.add(keys[i]);
            }
        }
        return queue;
    }
}
