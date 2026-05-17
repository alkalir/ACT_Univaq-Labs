/*
 * Parallel numerical integration — SPMD without false sharing.
 *
 * This version fixes the false sharing problem from the previous program.
 * Instead of accumulating into sum[id] (a shared array), each thread
 * uses a private scalar (partial_sum) that lives in its own registers
 * or stack. There is no shared cache line to fight over.
 *
 * Once each thread has finished its portion of the loop, the partial
 * sums are combined into full_sum using a critical section, which
 * ensures that only one thread at a time updates the global result.
 *
 * Compare the timings from this version against the false sharing version.
 * You should see better scalability as the number of threads increases.
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
    double sum[MAX_THREADS];

    step = 1.0 / (double) num_steps;

    for (j = 1; j <= MAX_THREADS; j++) {

        omp_set_num_threads(j);
        full_sum = 0.0;
        start_time = omp_get_wtime();

        #pragma omp parallel private(i)
        {
            int id          = omp_get_thread_num();
            int numthreads  = omp_get_num_threads();
            double x;
            double partial_sum = 0;   /* private to each thread — no sharing */

            /* only one thread prints the thread count */
            #pragma omp single
                printf(" num_threads = %d", numthreads);

            /* cyclic distribution of iterations across threads */
            for (i = id; i < num_steps; i += numthreads) {
                x = (i + 0.5) * step;
                partial_sum += 4.0 / (1.0 + x*x);
            }

            /* one thread at a time adds its partial sum to the global total */
            #pragma omp critical
                full_sum += partial_sum;
        }

        pi = step * full_sum;
        run_time = omp_get_wtime() - start_time;

        printf("\n pi is %f in %f seconds with %d thread(s)\n", pi, run_time, j);
    }
}
