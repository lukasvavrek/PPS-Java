#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct Matrix {
    int **matrix;
    int m;
    int n;
};

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

void freeMatrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->m; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}

void printMatrix(struct Matrix *matrix) {
    if (matrix->m > 10 || matrix->n > 10)
        return; // :)
    for (int i = 0; i < matrix->m; i++) {
        for (int j = 0; j < matrix->n; j++)
            printf("%3d ", matrix->matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

struct Matrix* multiply(struct Matrix *m1, struct Matrix *m2) {
    assert(m1->n == m2->m);

    struct Matrix *m = generateMatrix(m1->m, m2->n);
    for (int i = 0; i < m1->m; i++)
        for (int j = 0; j < m2->n; j++) {
            int sum = 0;
            for (int k = 0; k < m2->m; k++)
                sum += m1->matrix[i][k] * m2->matrix[k][j];
            m->matrix[i][j] = sum;
        }
    return m;
}

int main(int argc, char **argv) {
    int m = 3, n = 2;
    if (argc == 3) {
        m = atoi(argv[1]);
        n = atoi(argv[2]);
    }
    srand(time(NULL));
    struct Matrix *a = generateMatrix(m, n);
    struct Matrix *b = generateMatrix(n, m);

    printMatrix(a);
    printMatrix(b);

    clock_t begin = clock();
    struct Matrix *c = multiply(a, b);
    clock_t end = clock();
    printMatrix(c);
    printf("\n%f\n", (double)(end-begin) / CLOCKS_PER_SEC);

    freeMatrix(a);
    freeMatrix(b);
    freeMatrix(c);

    return 0;
}
