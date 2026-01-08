#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "implement.h"

bool verify_result(int *mat_a, int *mat_b, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            if (mat_a[i * w + j] != mat_b[i * w + j])
            {
                printf("Mismatch at (%d, %d): %d != %d\n", i, j, mat_a[i * w + j], mat_b[i * w + j]);
                return false;
            }
        }
    }
    return true;
}

int main(void)
{
    /* Data preparation */
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

    // return matrix
    int result[4][4] = {0};

    /* verify native implementation correctness */
    matmul((int *)input_mat_a, (int *)input_mat_b, (int *)result, 4, 3, 4);
    assert(verify_result((int *)result, (int *)output_mat, 4, 4) && "Implementation Verification ERROR !!!");

    printf("Implementation Verification PASSED !!!\n");

    return 0;
}