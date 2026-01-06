#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>

#define MATRIX_SIZE 1024

/* assume matrix A (size m x n) multiply matrix B (size n x b) */
void naive_matmul(int *mat_a, int *mat_b, int *dest, int m, int n, int b)
{
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < b; ++j)
        {
            dest[i * b + j] = 0;
            for (int k = 0; k < n; ++k)
            {
                dest[i * b + j] += mat_a[i * n + k] *
                                   mat_b[k * b + j];
            }
        }
    }
}

bool verify_result(int *mat_a, int *mat_b, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (mat_a[i * w + j] != mat_b[i * w + j])
            {
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    /* first step is to verify calculation
     * the correctness of implementation
     */
    // input matrix with size m x n
    int input_mat_a[4][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11},
    };
    int input_mat_b[3][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
    };
    // output matrix with size n x b
    int output_mat[4][4] = {
        {20, 23, 26, 29},
        {56, 68, 80, 92},
        {92, 113, 134, 155},
        {128, 158, 188, 218},
    };

    int result[4][4] = {0};
    naive_matmul((int *)input_mat_a, (int *)input_mat_b, (int *)result, 4, 3, 4);

    if (verify_result((int *)result, (int *)output_mat, 4, 4))
    {
        printf("Verification passed\n");
    }
    else
    {
        printf("Verification failed\n");
    }

    /* second step is to calculate the execution time */
    struct timespec start, end;
    /* allocate matrices on the heap to avoid stack overflow */
    int *mat_a = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    int *mat_b = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    int *mat_result = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    if (!mat_a || !mat_b || !mat_result)
    {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    // use a fix random seed to generate matrix
    srand(0);
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            mat_a[i * MATRIX_SIZE + j] = rand() % 100;
            mat_b[i * MATRIX_SIZE + j] = rand() % 100;
        }
    }

    /* use of CLOCK_MONOTONIC to get execution time
     * instead of CLOCK_REALTIME, this will be skewed by NTP adjustments
     */
    clock_gettime(CLOCK_MONOTONIC, &start);
    naive_matmul(mat_a, mat_b, mat_result, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("naive: \t\t %ld us\n", (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000);

    free(mat_a);
    free(mat_b);
    free(mat_result);

    return 0;
}