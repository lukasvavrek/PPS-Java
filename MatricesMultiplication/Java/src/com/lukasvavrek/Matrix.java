package com.lukasvavrek;

import java.util.Random;

public class Matrix {
    private int[][] matrix;
    private int m;
    private int n;

    public Matrix(int m, int n) {
        this(m, n, false);
    }

    public Matrix(int m, int n, boolean seed) {
        matrix = new int[m][n];
        this.m = m;
        this.n = n;

        if (seed) {
            generateData();
        }
    }

    private void generateData() {
        Random rand = new Random();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = rand.nextInt(20) - 10;
            }
        }
    }

    public int getM() {
        return m;
    }

    public int getN() {
        return n;
    }

    public int[][] getMatrix() {
        return matrix;
    }

    public void print() {
        if (m > 10 || n > 10) {
            return;
        }
        for(int[] row: matrix) {
            for(int num: row) {
                System.out.format("%5d", num);
            }
            System.out.println();
        }
        System.out.println();
    }
}
