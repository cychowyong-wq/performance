#include "implement.h"

#include <string.h>

#define SUB_MATRIX_SIZE 4

/* this is implementation of matrix multiplication
 * will calculate submatrix of a and b and store result in dest
 * this expect to reuse cache as much as possible
 */
void matmul(int *mat_a, int *mat_b, int *dest, int m, int n, int b)
{
    memset(dest, 0, sizeof(int) * m * b);

    for (int i = 0; i < m; i += SUB_MATRIX_SIZE)
    {
        for (int j = 0; j < b; j += SUB_MATRIX_SIZE)
        {
            int max_i = (m - i) < SUB_MATRIX_SIZE ? (m - i) : SUB_MATRIX_SIZE;
            int max_j = (b - j) < SUB_MATRIX_SIZE ? (b - j) : SUB_MATRIX_SIZE;
            for (int k = 0; k < n; k += SUB_MATRIX_SIZE)
            {
                int max_k = (n - k) < SUB_MATRIX_SIZE ? (n - k) : SUB_MATRIX_SIZE;

                /* Fast path: full tiles where all dimensions equal SUB_MATRIX_SIZE.
                 * Branch once and run loops with constant bounds to avoid extra checks
                 * inside the inner-most loops. */
                if (max_i == SUB_MATRIX_SIZE && max_j == SUB_MATRIX_SIZE && max_k == SUB_MATRIX_SIZE)
                {
                    for (int i2 = 0; i2 < SUB_MATRIX_SIZE; ++i2)
                    {
                        for (int j2 = 0; j2 < SUB_MATRIX_SIZE; ++j2)
                        {
                            int acc = dest[(i + i2) * b + (j + j2)];
                            for (int k2 = 0; k2 < SUB_MATRIX_SIZE; ++k2)
                            {
                                acc += mat_a[(i + i2) * n + (k + k2)] *
                                       mat_b[(k + k2) * b + (j + j2)];
                            }
                            dest[(i + i2) * b + (j + j2)] = acc;
                        }
                    }
                }
                else
                {
                    /* General (tail) path: handle smaller tiles safely. */
                    for (int i2 = 0; i2 < max_i; ++i2)
                    {
                        for (int j2 = 0; j2 < max_j; ++j2)
                        {
                            for (int k2 = 0; k2 < max_k; ++k2)
                            {
                                dest[(i + i2) * b + (j + j2)] +=
                                    mat_a[(i + i2) * n + (k + k2)] *
                                    mat_b[(k + k2) * b + (j + j2)];
                            }
                        }
                    }
                }
            }
        }
    }
}
