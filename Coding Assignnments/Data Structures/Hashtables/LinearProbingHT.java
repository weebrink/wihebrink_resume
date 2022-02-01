package WihebrinkHT;

/**
 * Implements a linear probing hash table.
 * Completion Time: 9 hours.
 *
 * @author Wihebrink
 * @version 1.0, 11/24/2020
 */

import java.util.LinkedList;
import java.util.Queue;

public class LinearProbingHT<Key, Value> implements SymbolTable {

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

    private static final int start_size = 16;

    private int N;
    private int M;
    private Key[] keys;
    private Value[] vals;

    public LinearProbingHT() {

        this(start_size);
    }

    public LinearProbingHT(int size) {
        M = size;
        N = 0;
        keys = (Key[]) new Object[M];
        vals = (Value[]) new Object[M];
    }

    private int hash(Key key) {
        int i = LinearProbingHT[];
        return ((key.hashCode() & 0x7fffffff) + i) % M;
    }

    @Override
    public void put(Key key, Value val) { // DONE

        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (val == null) {
            delete(key);
            return;
        }

        if (N >= M/2) {
            resize(2*M);
        }

        int i;
        for (i = hash(key); keys[i] != null; i = (i + 1) % M) {
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
    public Value get(Key key) { // DONE
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        for (int i = hash(key); keys[i] != null; i = (i + 1) % M) {
            if (keys[i].equals(key)) {
                return vals[i];
            }
        }
        return null;
    }

    @Override
    public boolean contains(Key key) { // DONE
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        return get(key) != null;
    }

    @Override
    public void delete(Key key) { // DONE
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (!contains(key)) {
            return;
        }

        int i = hash(key);
        while (!key.equals(keys[i])) {
            i = (i + 1) % M;
        }
        keys[i] = null;
        vals[i] = null;

        i = (i + 1) % M;

        while (keys[i] != null) {
            Key fixKey = keys[i];
            Value fixValue = vals[i];
            keys[i] = null;
            vals[i] = null;
            N--;
            put(fixKey, fixValue);
            i = (i + 1) % M;
        }
        N--;

        if (N > 0 && N <= M/8) {
            resize(M/2);
        }
    }

    @Override
    public int size() { // DONE
        return N;
    }

    private void resize(int size) {
        LinearProbingHT<Key, Value> temp_table = new LinearProbingHT<>(size);
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
    public boolean isEmpty() { // DONE
        return size() == 0;
    }

    @Override
    public Iterable<Key> keys() { // DONE
        Queue<Key> queue = new LinkedList<Key>();
        for (int i = 0; i < M; i++) {
            if (keys[i] != null) {
                queue.add(keys[i]);
            }
        }
        return queue;
    }
}
