/*
 * Parallel numerical integration — SPMD with false sharing.
 *
 * Each thread computes a partial sum and stores it in sum[id],
 * where id is the thread index. The partial sums are then combined
 * into a single result after the parallel region.
 *
 * The loop is distributed cyclically: thread 0 handles steps 0, N, 2N, ...
 * thread 1 handles steps 1, N+1, 2N+1, ... and so on.
 *
 * WARNING — false sharing:
 * sum[] is an array where adjacent elements are likely to sit on the
 * same cache line. When thread 0 writes sum[0] and thread 1 writes sum[1],
 * the hardware sees two writes to the same cache line from different cores
 * and forces costly cache invalidations. This causes the threads to
 * interfere with each other even though they are writing to different
 * variables. The result: poor scalability. You may see little or no
 * speedup as you increase the number of threads.
 *
 * The program runs with 1, 2, 3, and MAX_THREADS threads in sequence
 * so you can observe the scaling behavior directly.
 */

#include <stdio.h>
#include <omp.h>

#define MAX_THREADS 4

static long num_steps = 100000000;
double step;

int main()
{
    int i, j;
    double pi, full_sum = 0.0;
    double start_time, run_time;
    double sum[MAX_THREADS];   /* partial sums — one per thread, but falsely shared */

    step = 1.0 / (double) num_steps;

    for (j = 1; j <= MAX_THREADS; j++) {

        omp_set_num_threads(j);
        full_sum = 0.0;
        start_time = omp_get_wtime();

        #pragma omp parallel
        {
            int i;
            int id         = omp_get_thread_num();
            int numthreads = omp_get_num_threads();
            double x;

            sum[id] = 0.0;

            if (id == 0)
                printf(" num_threads = %d", numthreads);

            /* cyclic distribution of iterations across threads */
            for (i = id; i < num_steps; i += numthreads) {
                x = (i + 0.5) * step;
                sum[id] = sum[id] + 4.0 / (1.0 + x*x);
            }
        }

        /* combine partial sums — done outside the parallel region */
        for (full_sum = 0.0, i = 0; i < j; i++)
            full_sum += sum[i];

        pi = step * full_sum;
        run_time = omp_get_wtime() - start_time;

        printf("\n pi is %f in %f seconds with %d thread(s)\n", pi, run_time, j);
    }
}
