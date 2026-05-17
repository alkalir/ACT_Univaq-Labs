# Step 2 — Parallel Performance and False Sharing

In this step you will measure the performance of a parallel program and discover that adding more threads does not always mean going faster. You will see a concrete example of **false sharing** — a subtle but devastating performance problem that arises from the way modern CPUs manage their caches — and then fix it.

The program computes an approximation of pi by numerically integrating the function `4/(1+x*x)` from 0 to 1. This is a well-known result from calculus: the integral equals pi exactly, so it gives us an easy way to verify correctness while doing a meaningful amount of computation.

---

## Part 1 — Sequential baseline

Open `pi_seq.c`. It computes the integral using a single loop over 100 million steps and prints the result along with the elapsed time.

Compile and run:

```bash
gcc -fopenmp -o pi_seq pi_seq.c -lm
./pi_seq
```

Note the time. This is your baseline — all parallel versions will be compared against it.

---

## Part 2 — Parallel with false sharing

Open `pi_spmd_false_sharing.c`. The computation is now split across multiple threads using an SPMD (Single Program Multiple Data) approach: each thread handles a subset of the steps and stores its partial sum in `sum[id]`, where `id` is the thread index. The partial sums are combined after the parallel region.

The program runs automatically with 1, 2, 3, and 4 threads so you can observe scaling directly.

Compile and run:

```bash
gcc -fopenmp -o pi_false pi_spmd_false_sharing.c -lm
./pi_false
```

Look at the timings as the number of threads increases. Does performance improve as you would expect?

**What is going wrong:** `sum[]` is an array where adjacent elements share a cache line. When thread 0 writes `sum[0]` and thread 1 writes `sum[1]`, the CPU sees two cores writing to the same cache line and forces expensive cache invalidations — even though the threads are writing to different variables. This is false sharing, and it can eliminate all the benefit of parallelism.

---

## Part 3 — Fixed: no false sharing

Open `pi_spmd_fixed.c`. The fix is straightforward: instead of accumulating into `sum[id]`, each thread uses a local scalar `partial_sum` that lives entirely in its own stack. There is no shared cache line. Once the loop is done, each thread adds its result to the global total using a `critical` section.

Compile and run:

```bash
gcc -fopenmp -o pi_fixed pi_spmd_fixed.c -lm
./pi_fixed
```

Compare the timings against Part 2. You should now see meaningful speedup as the number of threads increases.

---

## What to think about

- How much speedup did you observe going from 1 to 4 threads in the fixed version?
- Why does the false sharing version perform poorly even though each thread writes to a different index?
- The `critical` section in the fixed version serializes part of the work. Why is this not a problem here?
