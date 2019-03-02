package com.lukasvavrek;

public class ParallelMergeSorter {
    public void sort(float[] a, int threads) {
        parallelMergeSort(a, 0, a.length-1, threads);
    }

    private void mergeSort(float[] a, int from, int to) {
        if (from == to) {
            return;
        }
        if (to - from > 0) {
            int mid = (from + to) / 2;

            mergeSort(a, from, mid);
            mergeSort(a, mid + 1, to);

            merge(a, from, mid, to);
        }
    }

    private void parallelMergeSort(float[] a, int from, int to, int availableThreads){
        if (to - from > 0){
            if (availableThreads <=1) {
                mergeSort(a, from, to);
            }
            else {
                int middle = to/2;

                //TODO:Initialize 2 new threads which will run parallelMergeSort function, each using half of the a[] array and start them both


                //TODO: Synchronize both threads with the main thread

                merge(a, from, middle, to);
            }
        }
    }

    private void merge(float[] a, int from, int mid, int to) {
        int n = to - from + 1;

        float[] b = new float[n];

        int i1 = from;
        int i2 = mid + 1;
        int j = 0;

        while (i1 <= mid && i2 <= to) {
            if (a[i1] < a[i2]) {
                b[j] = a[i1];
                i1++;
            } else {
                b[j] = a[i2];
                i2++;
            }
            j++;
        }

        while (i1 <= mid) {
            b[j] = a[i1];
            i1++;
            j++;
        }

        while (i2 <= to) {
            b[j] = a[i2];
            i2++;
            j++;
        }

        for (j = 0; j < n; j++) {
            a[from + j] = b[j];
        }
    }
}
