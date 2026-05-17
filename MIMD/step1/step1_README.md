# Step 1 — Hello World with OpenMP

In this step you will write and run your first parallel program. The goal is simple: understand what happens when you take a sequential program and hand it over to multiple threads.

You will work with two programs. The first is a plain sequential hello world. The second adds a single OpenMP directive and runs the same code in parallel. Comparing the two outputs will show you immediately what OpenMP does and how threads interact.

---

## Part 1 — Sequential

Open `hello_seq.c`. It prints a hello and a world message using a single thread with ID hardcoded to 0.

Compile and run:

```bash
gcc -o hello_seq hello_seq.c
./hello_seq
```

The output is predictable — one hello, one world, always in order.

---

## Part 2 — Parallel

Open `hello_par.c`. The only differences from the sequential version are:
- `#include <omp.h>` to access OpenMP functions
- `#pragma omp parallel` to launch a team of threads
- `omp_get_thread_num()` to let each thread know its own ID

Compile and run:

```bash
gcc -fopenmp -o hello_par hello_par.c
./hello_par
```

Look at the output carefully. You will notice two things:
- Each thread prints its own ID instead of 0
- The order of the lines is not guaranteed — hello and world from different threads can interleave

Run it a few times. Does the output change?

### Control the number of threads

```bash
export OMP_NUM_THREADS=4
./hello_par
```

Try different values and observe how the output changes.

---

## What to think about

- Why can hello and world from the same thread end up separated in the output?
- What does this tell you about how threads execute independently?
- What would happen if the two printf calls needed to stay together?
