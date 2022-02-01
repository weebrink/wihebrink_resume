package WihebrinkHT;

/**
 * Implements a two probe seperate chain hash table.
 * Completion Time: 10 hours.
 *
 * @author Wihebrink
 * @version 1.0, 11/24/2020
 */

import java.util.LinkedList;
import java.util.Queue;

public class TwoProbeChainHT<Key, Value> implements SymbolTable {

    private class Entry {

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

    }
    private static final int start_size = 997;

    private int N; // key-value pairs
    private int M; // size of hash table
    private TwoProbeChainHT<Key, Value>[] TwoProbeST;

    public TwoProbeChainHT() {
        this(start_size);
    }

    public TwoProbeChainHT(int M) {
        this.M = M;
        TwoProbeST = (TwoProbeChainHT<Key, Value>[]) new TwoProbeChainHT[M];
        for (int i = 0; i < M; i++)
            TwoProbeST[i] = new TwoProbeChainHT<>();
    }

    private void resize(int chains) {
        TwoProbeST<Key, Value> temp = new TwoProbeChainHT<Key, Value>(chains);
        for (int i = 0; i < M; i++) {
            for (Key key: TwoProbeST[i].keys()) {
                temp.put(key, TwoProbeST[i].get(key));
            }
        }

        this.M = temp.M;
        this.N = temp.N;
        this.TwoProbeST = temp.TwoProbeST;
    }

    private int hash(Key key) {

        int HashPosition1 = ((key.hashCode() & 0x7fffffff) % M);
        int HashPosition2 = ((((key.hashCode() & 0x7fffffff) % M) * 31) % M);

        if (HashPosition1 < HashPosition2) {
            return HashPosition1;
        }
        else {
            return HashPosition2;
        }
    }

    @Override
    public Value get(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        int i = hash(key);
        return (Value) TwoProbeST[i].get(key);
    }

    @Override
    public void put(Key key, Value val) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }
        if (val == null) {
            delete(key);
            return;
        }

        if (N >= 10*M) {
            resize(2*M);
        }

        int i = hash(key);

        if (!TwoProbeST[i].contains(key)) {
            N++;
        }

        TwoProbeST[hash(key)].put(key,val);
    }

    @Override
    public Iterable<Key> keys() {

        Queue<Key> TwoProbeChainQueue = new LinkedList<Key>();
        for (int i = 0; i < M; i++) {
            for (Key key : TwoProbeST[i].keys()) {
                TwoProbeChainQueue.add(key);
            }
        }
        return TwoProbeChainQueue;
    }

    @Override
    public int size() {
        return N;
    }

    @Override
    public boolean isEmpty() {
        return size() == 0;
    }

    @Override
    public boolean contains(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }

        return get(key) != null;
    }

    @Override
    public void delete(Key key) {
        if (key == null) {
            throw new IllegalArgumentException("key is null");
        }

        int i = hash(key);

        if (!TwoProbeST[i].contains(key)) {
            N--;
        }

        TwoProbeST[i].delete(key);

        if (M > 0 && N <= 2*M) {
            resize(M/2);
        }
    }
}