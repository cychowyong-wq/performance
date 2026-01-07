#ifndef MATMUL_H
#define MATMUL_H

/* assume matrix A (size m x n) multiply matrix B (size n x b)
 * Dest = A * B (size m x b)
 */
void matmul(int *A, int *B, int *Dest, int m, int n, int b);

#endif