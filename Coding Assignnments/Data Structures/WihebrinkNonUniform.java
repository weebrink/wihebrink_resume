package WihebrinkNonUniform;

import java.lang.*;
import java.lang.Math;
import java.text.DecimalFormat;
import java.util.Random;

/**
 * Description: This program will create 3 different data set types in arrays.
 *              These sets are benchmark tested by 2 different sorting algorithms,
 *              Insertion Sort and Shellsort. Creates B-values to display back to
 *              the user.
 *
 * Completion time: 4 hours
 *
 * @author Wihebrink, Acuna, Sedgewick
 * @version 2.0, 10/27/2020
 */

public class WihebrinkNonUniform implements SER222_02_01_HW02_Submission {

    /***************************************************************************
     * START - SORTING UTILITIES, DO NOT MODIFY (FROM SEDGEWICK)               *
     **************************************************************************/

    public static void insertionSort(Comparable[] a) {
        int N = a.length;

        for (int i = 1; i < N; i++) {
            // Insert a[i] among a[i-1], a[i-2], a[i-3]... ..
            for (int j = i; j > 0 && less(a[j], a[j - 1]); j--)
                exch(a, j, j - 1);
        }
    }


    public static void shellsort(Comparable[] a) {
        int N = a.length;
        int h = 1;

        while (h < N / 3) h = 3 * h + 1; // 1, 4, 13, 40, 121, 364, 1093, ...

        while (h >= 1) {
            // h-sort the array.
            for (int i = h; i < N; i++) {
                // Insert a[i] among a[i-h], a[i-2*h], a[i-3*h]... .
                for (int j = i; j >= h && less(a[j], a[j - h]); j -= h)
                    exch(a, j, j - h);
            }
            h = h / 3;
        }
    }


    private static boolean less(Comparable v, Comparable w) {
        return v.compareTo(w) < 0;
    }


    private static void exch(Comparable[] a, int i, int j) {
        Comparable t = a[i];
        a[i] = a[j];
        a[j] = t;
    }

    /***************************************************************************
     * END - SORTING UTILITIES, DO NOT MODIFY                                  *
     **************************************************************************/

    /**
     * Generates an array of integers where half the data is 0s, half 1s.
     *
     * @param size number of elements in the array.
     * @return generated test set.
     */
    public Integer[] generateTestDataBinary(int size) {

        Integer[] data_binary = new Integer[size];

        int limit = (size + 1) / 2;

        int start = 0;
        int value = 0;
        int index = 0;

        do {
            for (int i = start; i < start + limit && index < size; ++i) {
                data_binary[index++] = value;
            }
            start += limit;
            limit = (limit + 1) / 2;
            value = 1;
        } while (index < size);

        return data_binary;
    }

    /**
     * Generates an array of integers where half the data is 0s, half the
     * remainder is 1s, half the reminder is 2s, half the reminder is 3s, and so
     * forth.
     *
     * @param size number of elements in the array.
     * @return generated test set.
     */
    public Integer[] generateTestDataHalfs(int size) {

        Integer[] data_halfs = new Integer[size];

        int limit = (size + 1) / 2;

        int start = 0;
        int value = 0;
        int index = 0;

        do {
            for (int i = start; i < start + limit && index < size; ++i) {
                data_halfs[index++] = value;
            }
            start += limit;
            limit = (limit + 1) / 2;
            ++value;
        } while (index < size);

        return data_halfs;
    }

    /**
     * Generates an array of integers where half the data is 0s, and half random
     * int values.
     *
     * @param size
     * @return
     */
    public Integer[] generateTestDataHalfRandom(int size) {

        Random rand = new Random();
        Integer[] data_random_halfs = new Integer[size];

        int limit = (size + 1) / 2;

        int start = 0;
        int value = 0;
        int index = 0;

        do {
            for (int i = start; i < start + limit && index < size; ++i) {
                data_random_halfs[index++] = value;

                if (i > limit) {
                    value = rand.nextInt();
                }
            }
            start += limit;
            limit = (limit + 1) / 2;
            value = rand.nextInt();
            value++;
        } while (index < size);

        return data_random_halfs;
    }

    /**
     * Computes the double formula value for two run times.
     *
     * @param t1 first time
     * @param t2 second time
     * @return b value
     */
    public double computeDoublingFormula(double t1, double t2) {
        double b = ((Math.log(t2) / Math.log(t1)) / Math.log(2));
        // log(2) T(2N)/T(N) = b
        return b;
    }

    /**
     * Computes an empirical b value for insertion sort by running it on a pair
     * of inputs and using the doubling formula.
     *
     * @param small small test data array
     * @param large large test data array. twice the same of small array.
     * @return b value
     */
    public double benchmarkInsertionSort(Integer[] small, Integer[] large) {

        Stopwatch stopwatch1 = new Stopwatch();
        insertionSort(small);
        double b_insertion_small = stopwatch1.elapsedTime();

        Stopwatch stopwatch2 = new Stopwatch();
        insertionSort(large);
        double b_insertion_large = stopwatch2.elapsedTime();

        double b_value = computeDoublingFormula(b_insertion_small, b_insertion_large);
        return b_value;
    }

    /**
     * Computes an empirical b value for shellsort sort by running it on a pair
     * of inputs and using the doubling formula.
     *
     * @param small small test data array
     * @param large large test data array. twice the same of small array.
     * @return b value
     */
    public double benchmarkShellsort(Integer[] small, Integer[] large) {

        Stopwatch stopwatch3 = new Stopwatch();
        shellsort(small);
        double b_shell_small = stopwatch3.elapsedTime();

        Stopwatch stopwatch4 = new Stopwatch();
        shellsort(large);
        double b_shell_large = stopwatch4.elapsedTime();

        double b_shell_value = computeDoublingFormula(b_shell_small, b_shell_large);
        return b_shell_value;
    }

    /**
     * Runs the two sorting algorithms on the three types of test data to
     * produce six different b values. B values are displayed to the user.
     *
     * @param size size of benchmark array. to be doubled later.
     */
    public void runBenchmarks(int size) {

        DecimalFormat output = new DecimalFormat("0.000");

        // DATA BINARY CODE BLOCK
        Integer[] binary_insertion_small = generateTestDataBinary(size);
        Integer[] binary_insertion_large = generateTestDataBinary(size * 2);
        double binary_insertion_time = benchmarkInsertionSort(binary_insertion_small, binary_insertion_large);

        Integer[] binary_shell_small = generateTestDataBinary(size);
        Integer[] binary_shell_large = generateTestDataBinary(size * 2);
        double binary_shellsort_time = benchmarkShellsort(binary_shell_small, binary_shell_large);

        // DATA HALFS CODE BLOCK
        Integer[] halfs_insertion_small = generateTestDataHalfs(size);
        Integer[] halfs_insertion_large = generateTestDataHalfs(size * 2);
        double halfs_insertion_time = benchmarkInsertionSort(halfs_insertion_small, halfs_insertion_large);

        Integer[] halfs_shell_small = generateTestDataHalfs(size);
        Integer[] halfs_shell_large = generateTestDataHalfs(size * 2);
        double halfs_shellsort_time = benchmarkShellsort(halfs_shell_small, halfs_shell_large);

        // DATA HALF RANDOM CODE BLOCK
        Integer[] halfRand_insertion_small = generateTestDataHalfRandom(size);
        Integer[] halfRand_insertion_large = generateTestDataHalfRandom(size * 2);
        double halfRand_insertion_time = benchmarkInsertionSort(halfRand_insertion_small, halfRand_insertion_large);

        Integer[] halfRand_shell_small = generateTestDataHalfRandom(size);
        Integer[] halfRand_shell_large = generateTestDataHalfRandom(size * 2);
        double halfRand_shellsort_time = benchmarkShellsort(halfRand_shell_small, halfRand_shell_large);

        // OUTPUT CODE BLOCK
        System.out.println("                Insertion    Shellsort");
        System.out.println("Bin                " + output.format(binary_insertion_time)
                + "    " + output.format(binary_shellsort_time));
        System.out.println("Half               " + output.format(halfs_insertion_time)
                + "    " + output.format(halfs_shellsort_time));
        System.out.println("RanInt             " + output.format(halfRand_insertion_time)
                + "    " + output.format(halfRand_shellsort_time));
    }

    public static void main(String args[]) {
        SER222_02_01_HW02_Submission me = new WihebrinkNonUniform();
        int size = 4096;

        me.runBenchmarks(size);
    }
}