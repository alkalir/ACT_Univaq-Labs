# Welcome to MIMD Lab

In this lab you will learn how to exploit a MIMD (Multiple Instruction, Multiple Data) processor — the architecture behind virtually every modern CPU. You will do so using **OpenMP**, a widely adopted API for shared-memory parallel programming. OpenMP lets you parallelize existing C/C++ code incrementally, by adding compiler directives, with no need to rewrite your programs from scratch.

By the end of this lab you will be able to write, compile, and benchmark parallel programs and reason about speedup, thread synchronization, and data sharing.

---

## Requirements

To follow this lab you need a C/C++ compiler with OpenMP support. This is available out of the box on most systems:

- **Linux** — GCC is typically pre-installed. If not: `sudo apt install gcc`
- **macOS** — Install GCC via Homebrew: `brew install gcc`
- **Windows** — Use WSL2 with GCC, or install GCC via MSYS2

---

## Your working folder

Create a folder on your machine where you will write and save all your code:

- **Windows:** `C:\mylab`
- **macOS / Linux:** `~/mylab`

---

## Docker

If you are unsure whether your compiler supports OpenMP, or you want a clean and identical environment regardless of your OS, a ready-to-use Docker image is available. Follow the instructions in [docker/README.md](docker/README.md) and then come back here.

---

## Let's check your OpenMP compiler before we start

Using any text editor (Notepad, VSCode, gedit, etc.), create a file called `test.c` with the following content and save it inside your working folder:

```c
#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    printf("Thread %d of %d\n", omp_get_thread_num(), omp_get_num_threads());
    return 0;
}
```

### Compile and run

**If you are using your own compiler**, open a terminal in your working folder and run:

```bash
gcc -fopenmp -o test test.c && ./test
```

**If you are using Docker**, start the container as described in [docker/README.md](docker/README.md), then run the same command inside the container.

You should see one line per available core, printed in arbitrary order:

```
Thread 3 of 12
Thread 0 of 12
Thread 7 of 12
...
```

If you see this, your environment is working correctly.

### Control the number of threads

```bash
export OMP_NUM_THREADS=4
./test
```

Run the program again — you should now see exactly 4 lines.

---

## Labs

Once your environment is set up and the compiler check passes, work through the steps in order. Each step is self-contained in its own folder and has its own README with instructions. Start from `step1/` and proceed in order.
