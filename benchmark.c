#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// perf profiling used headers
#include <fcntl.h>
#include <unistd.h>

// implementation header
#include "implement.h"

#define MATRIX_SIZE 512
#define WARMUP_ITER 5
#define TIMING_ITER 20

int get_clock(struct timespec start, struct timespec end)
{
    return (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
}

static void compute_stats(unsigned long long *samples, int count, double *mean, double *stddev)
{
    double sum = 0.0;
    for (int i = 0; i < count; i++)
    {
        sum += samples[i];
    }
    *mean = sum / count;

    double var = 0.0;
    for (int i = 0; i < count; i++)
    {
        var += (samples[i] - *mean) * (samples[i] - *mean);
    }
    *stddev = sqrt(var / count);
}

int main(void)
{
    /* allocate matrices */
    int *mat_a = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    int *mat_b = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    int *mat_result = malloc(sizeof(int) * MATRIX_SIZE * MATRIX_SIZE);
    if (!mat_a || !mat_b || !mat_result)
    {
        fprintf(stderr, "malloc failed\n");
        return 1;
    }

    /* initialize matrices with fix random values */
    srand(0); // use a fix random seed to generate matrix
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
        {
            mat_a[i * MATRIX_SIZE + j] = rand() % 100;
            mat_b[i * MATRIX_SIZE + j] = rand() % 100;
        }
    }

    /* run profile for perf cache */
    printf("Start Profile\n");
    int ctl_fd = open("perf_ctl.fifo", O_WRONLY);
    write(ctl_fd, "enable\n", 7); // START
    matmul(mat_a, mat_b, mat_result, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE);
    write(ctl_fd, "disable\n", 8); // STOP
    close(ctl_fd);

    /* warmup cache */
    printf("Warming up cache...\n");
    for (int i = 0; i < WARMUP_ITER; i++)
    {
        matmul(mat_a, mat_b, mat_result, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE);
    }

    /* use of CLOCK_MONOTONIC to get execution time
     * instead of CLOCK_REALTIME, this will be skewed by NTP adjustments
     */
    printf("Start Benchmark\n");
    struct timespec start, end;
    unsigned long long total_time[TIMING_ITER] = {0};

    for (int i = 0; i < TIMING_ITER; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        matmul(mat_a, mat_b, mat_result, MATRIX_SIZE, MATRIX_SIZE, MATRIX_SIZE);
        clock_gettime(CLOCK_MONOTONIC, &end);
        total_time[i] = get_clock(start, end);
    }

    double mean, stddev;
    compute_stats(total_time, TIMING_ITER, &mean, &stddev);

    printf("RESULT: \n");
    printf("  mean    = %.3f us\n", mean);
    printf("  stddev  = %.3f us\n", stddev);
    printf("  rel-var = %.2f %%\n", (stddev / mean) * 100.0);

    free(mat_a);
    free(mat_b);
    free(mat_result);

    return 0;
}