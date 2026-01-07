#include "implement.h"

/* this is a naive implementation of matrix multiplication
 */
void matmul(int *mat_a, int *mat_b, int *dest, int m, int n, int b)
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
