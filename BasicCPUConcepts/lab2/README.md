# Lab 2: Introduction to OpenMP Programming

## Objective

This lab introduces to parallel programming using **OpenMP**. You will analyze and experiment with C programs to:

- Understand thread creation and management.
- Explore performance impact of parallelization.
- Learn how to avoid common pitfalls like **false sharing**.
- Estimate the value of π using numerical integration in a parallel context.

---

## Programs to Test and Analyze

### 1. `hello.c`
- A basic sequential Hello World program.
- **Goal**: Understand how output is generated without parallelism.

### 2. `hello_par.c`
- A multithreaded version using OpenMP.
- **Goal**: Learn how `#pragma omp parallel` spawns threads.
- Observe how multiple threads print concurrently.
- Check how many threads are actually created and used.

### 3. `pi.c`
- A sequential program that computes pi using numerical integration.
- **Goal**: Understand the midpoint rule and performance without parallelism.


### 4. `pi_spmd_simple.c`
- A simple **SPMD (Single Program, Multiple Data)** OpenMP implementation.
- Each thread computes part of the sum in `sum[id]`.
- **Goal**: Observe how work is divided among threads.
- Discuss the **false sharing problem** caused by the shared array.

### 5. `pi_spmd_final.c`
- Improved version of the previous program.
- Uses `partial_sum` inside each thread to avoid false sharing.
- Combines results using `#pragma omp critical`.
- **Goal**: Understand how cache line conflicts can hurt performance and how to fix them.

---

## How to Compile

Use `gcc` with OpenMP support:
```bash
gcc -fopenmp filename.c -o output_name
