package com.lukasvavrek;

public class MatrixMultiplicator {
    private int maxThreads;
    private Thread[] threads;

    public MatrixMultiplicator() {
        this(1); // sequential
    }

    public MatrixMultiplicator(int maxThreads) {
        if (maxThreads < 1) {
            throw new IllegalArgumentException("You have to have at least 1 thread.");
        }
        this.maxThreads = maxThreads;
        this.threads = new Thread[maxThreads];
    }

    public Matrix multiply(Matrix m1, Matrix m2) {
        if (m1.getN() != m2.getM()) {
            throw new IllegalArgumentException("Can only multiply matrices with dimensions MxN and NxP.");
        }

        Matrix result = new Matrix(m1.getM(), m2.getN());

        for (int i = 0; i < maxThreads; i++) {
            final int fi = i;
            threads[i] = new Thread(() -> multiply(m1, m2, result, fi));
            threads[i].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException ie) {
            }
        }
        return result;
    }

    private void multiply(Matrix m1, Matrix m2, Matrix result, int threadNum) {
        int[][] rm = result.getMatrix();
        int[][] m1m = m1.getMatrix();
        int[][] m2m = m2.getMatrix();

        int i = (m1.getM() / maxThreads) * threadNum;
        int m = Math.min((m1.getM() / maxThreads) * (threadNum + 1), m1.getM());
        int n = m2.getN();
        int o = m2.getM();

        System.out.format("%d threads: [ %d : %d ]\n", maxThreads, i, m);

        for (; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rm[i][j] = 0;
                for (int k = 0; k < o; k++) {
                    rm[i][j] += m1m[i][k] * m2m[k][j];
                }
            }
        }
    }
}
