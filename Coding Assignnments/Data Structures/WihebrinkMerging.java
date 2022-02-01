package WihebrinkMerging;

import java.util.*;
import java.util.Queue;

/**
 * Implements various merge style algorithms.
 *
 * Last updated 10/14/2019.
 *
 * Completion time: 8 hours
 *
 * @author Wihebrink, Acuna, Sedgewick and Wayne
 * @verison 2.0, 11/04/2020
 */

public class WihebrinkMerging {

    public static Queue mergeQueues(Queue<Comparable> q1, Queue<Comparable> q2) {

        // base cases of merge if either are empty
        if (q1 == null) {
            return q2;
        }
        if (q2 == null) {
            return q1;
        }

        //creates our return value mergedQueue
        Queue mergedQueue = new LinkedList();

        // When both queues are not empty
        while ( !q1.isEmpty() && !q2.isEmpty() ) {

            Comparable left = q1.peek();
            Comparable right = q2.peek();

            if ( left.compareTo(right) < 0) {

                mergedQueue.add(q1.poll());

            } else {

                mergedQueue.add(q2.poll());

            }

        }

        // When either queue is not empty
        while ( !q1.isEmpty() ) {

            mergedQueue.add(q1.poll());

        }

        while ( !q2.isEmpty() ) {

            mergedQueue.add(q2.poll());

        }

        return mergedQueue;
    }

    public static void sort(Comparable[] a) {

        mergesort(a);

        assert isSorted(a);

    }
    public static Comparable[] mergesort (Comparable[] a) {

        if (a.length == 1) {
            return a; // BASE CASE
        } else {


            int mid = a.length / 2;
            int i = 0, j = mid + 1;

            Comparable[] leftHalf = mergesort(Arrays.copyOfRange(a, 0, mid));
            Comparable[] rightHalf = mergesort(Arrays.copyOfRange(a, mid + 1, a.length));

            int k = 0;

            while (i < leftHalf.length && j < rightHalf.length) {
                if (leftHalf[i] <= rightHalf[j]) {
                    a[k] = leftHalf[i];
                    i = i + 1;
                } else {
                    a[k] = rightHalf[j];
                    j = j + 1;
                }
                k = k + 1;
            }

            while (i < leftHalf.length) {
                a[k] = leftHalf[i];
                i = i + 1;
                k = k + 1;
            }

            while (j < rightHalf.length) {
                a[k] = rightHalf[j];
                j = j + 1;
                k = k + 1;
            }

            mergesort(leftHalf);
            mergesort(rightHalf);
            return merge(leftHalf, rightHalf);
        }
    }

    public static Comparable[] merge (Comparable[] a, Comparable[] b){ //merge

        assert isSorted(a);
        assert isSorted(b);

        Comparable[] merged = new Comparable[];
        ListQueue dummy_merged = new ListQueue();

        while (a != null && b != null) {
            if (a[0] > b[0]) {
                dummy_merged.enqueue(b[0]);
                b.dequeue(b[0]);
            } else {
                dummy_merged.enqueue(a[0]);
                a.dequeue(a[0]);
            }
        }

        while (a != null) {
            dummy_merged.enqueue(a[0]);
            a.dequeue(a[0]);
        }

        while (b != null) {
            dummy_merged.enqueue(b[0]);
            b.dequeue(b[0]);
        }

        merged = merged.clone(dummy_merged);

        return merged;
    }

    public static void shuffle(Object[] a) {

        Random random = new Random();

        int n = a.length;

        while (n > 1) {
            for (int i = 0; i < n; i += 2) {
                int r = i + random.nextInt(a.length - i);

                // randomize elements as loop progresses
                Object temp = a[i];
                a[i] = a[r];
                a[r] = temp;
            }
            n /= 2;
        }

        // In this algorithm, we are executing at O(nlog(n)) time. This is because we are running
        // a while loop at O(n) time, then halfing each run of the loop by 2 to allow our loop to process in
        // O(nlog(n)) time. After each call to the loop, it will recursively keep calling itself and halfing
        // the result for quick comparisons.
    }

    //sorting helper from text
    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }

    //sorting helper from text
    private static void show(Comparable[] a) {
        for (Comparable a1 : a)
            System.out.print(a1 + " ");

        System.out.println();
    }

    //sorting helper from text
    public static boolean isSorted(Comparable[] a) {
        for (int i = 1; i < a.length; i++)
            if (less(a[i], a[i-1]))
                return false;

        return true;
    }

    /**
     * Entry point for sample output.
     *
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Queue q1 = new ListQueue();
        q1.enqueue("T");
        q1.enqueue("R");
        q1.enqueue("O");
        q1.enqueue("L");
        q1.enqueue("E"); //contains E L O R T (front)
        Queue q2 = new ListQueue();
        q2.enqueue("X");
        q2.enqueue("S");
        q2.enqueue("P");
        q2.enqueue("M");
        q2.enqueue("E");
        q2.enqueue("A"); ///contains A E M P S X (front)
        Queue q3 = new ListQueue();
        q3.enqueue(20);
        q3.enqueue(17);
        q3.enqueue(15);
        q3.enqueue(12);
        q3.enqueue(5); //contains 5, 12, 15, 17, 20 (front)
        Queue q4 = new ListQueue();
        q4.enqueue(18);
        q4.enqueue(16);
        q4.enqueue(13);
        q4.enqueue(12);
        q4.enqueue(4);
        q4.enqueue(1); //contains 1, 4, 12, 13, 16, 18 (front)

        //Q1 - sample test cases
        Queue merged1 = mergeQueues(q1, q2);
        System.out.println(merged1.toString());
        Queue merged2 = mergeQueues(q3, q4);
        System.out.println(merged2.toString());

        //Q2 - sample test cases
        String[] a = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
        sort(a);
        assert isSorted(a);
        show(a);

        //Q3 - sample test cases
        String[] b = {"S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E"};
        shuffle(b);
        show(b);

        shuffle(b);
        show(b);
    }
}