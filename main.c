#include <stdio.h>
#include <stdbool.h>

void naive_matmul(int *mat_a, int *mat_b, int *dest,
                  int mat_a_w, int mat_a_h,
                  int mat_b_w, int mat_b_h)
{
    for (int i = 0; i < mat_a_h; ++i)
    {
        for (int j = 0; j < mat_b_w; ++j)
        {
            dest[i * mat_b_w + j] = 0;
            for (int k = 0; k < mat_b_h; ++k)
            {
                dest[i * mat_b_w + j] += mat_a[i * mat_a_w + k] *
                                         mat_b[k * mat_b_w + j];
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
    // input
    int input_mat[4][4] = {
        {0, 1, 2, 3},
        {4, 5, 6, 7},
        {8, 9, 10, 11},
        {12, 13, 14, 15},
    };
    // output
    int output_mat[4][4] = {
        {56, 62, 68, 74},
        {152, 174, 196, 218},
        {248, 286, 324, 362},
        {344, 398, 452, 506},
    };

    int result[4][4] = {0};
    naive_matmul((int *)input_mat, (int *)input_mat, (int *)result, 4, 4, 4, 4);

    if (verify_result((int *)result, (int *)output_mat, 4, 4))
    {
        printf("Verification passed\n");
    }
    else
    {
        printf("Verification failed\n");
    }

    return 0;
}