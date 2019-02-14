#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

// stores all info about the matrix
struct Matrix {
    int **matrix;
    int m;
    int n;
};

// generates new matrix (with proper memmory allocations) of given size with random content
struct Matrix* generateMatrix(int m, int n) {
    struct Matrix *matrix = (struct Matrix *)malloc(sizeof (struct Matrix));
    matrix->m = m;
    matrix->n = n;

    matrix->matrix = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++)
        matrix->matrix[i] = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            matrix->matrix[i][j] = (rand() % 20) - 10;
    return matrix;
}

// release matrix content from memmory
void freeMatrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->m; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}

// pretty print matrix
void printMatrix(struct Matrix *matrix) {
    if (matrix->m > 10 || matrix->n > 10)
        return; // avoid printing large matrices :)
    for (int i = 0; i < matrix->m; i++) {
        for (int j = 0; j < matrix->n; j++)
            printf("%3d ", matrix->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

// multiply two matrices using standard serial algorithm and store result in new one
void multiply(struct Matrix *m1, struct Matrix *m2, struct Matrix *result) {
    assert(m1->n == m2->m);
    assert(m1->m == result->m);
    assert(m2->n == result->n);

    for (int i = 0; i < m1->m; i++)
        for (int j = 0; j < m2->n; j++) {
            int sum = 0;
            for (int k = 0; k < m2->m; k++)
                sum += m1->matrix[i][k] * m2->matrix[k][j];
            result->matrix[i][j] = sum;
        }
}

int main(int argc, char **argv) {
    int m = 2000, n = 2000;
	// we can provide matrix size directly from command line
    if (argc == 3) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    srand(time(NULL));
    struct Matrix *a = generateMatrix(m, n);
    struct Matrix *b = generateMatrix(n, m);

    printMatrix(a);
    printMatrix(b);

	// final matrix allocated and generated outside the stopwatch
	struct Matrix *c = generateMatrix(a->m, b->n);
    clock_t begin = clock();
    multiply(a, b, c);
    clock_t end = clock();

    printMatrix(c);
    printf("\n%f\n", (double)(end-begin) / CLOCKS_PER_SEC);

    freeMatrix(a);
    freeMatrix(b);
    freeMatrix(c);

	// just for VS users, wait before closing terminal
	getchar(); 

    return 0;
}
