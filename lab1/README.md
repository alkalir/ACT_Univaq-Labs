# CPU Microarchitecture Lab - Performance Exploration

## Overview

This lab introduces fundamental concepts in CPU microarchitecture by analyzing how a program executes on modern superscalar out-of-order processors. It uses performance counters to measure real effects of instruction-level parallelism (ILP), branch prediction, SIMD usage, and CPU features such as Simultaneous Multi-Threading (hyper-threading in Intel terminology) and cache behavior.

While the examples here are run on a workstation with:

* Intel Xeon E5-1650 v3 (Haswell-E)
* 6 physical cores, 12 threads (Hyper-Threading enabled)
* 15MB L3 cache (shared across cores)
* 6x L1D (32KB) and 6x L2 (256KB)

you can **run this lab on your own computer**, even if it's different. If you're on **Windows or macOS**, you can:

* Use Windows Performance Analyzer (or Intel VTune if you have an Intel processor)
* Use Apple Instruments on macOS
* Use Linux in a VM or WSL with `perf`

## CPU Basics for Haswell-E

* Can retire up to 4 instructions per cycle
* 8 execution ports (ALUs, branch, load/store)
* Fetch: 16 bytes/cycle
* Decode: 4 instructions/cycle
* Out-of-order execution based on Tomasulo-style pipeline

Haswell-E includes 8 execution ports, each connected to one or more types of functional units. The CPU can issue multiple micro-operations per cycle as long as they use different ports. Here's a simplified mapping:

- **Port 0**: Integer ALU, floating-point multiply, branch execution
- **Port 1**: Integer ALU, integer multiply, LEA (address calculation)
- **Port 2**: Load address generation (used for memory reads)
- **Port 3**: Load address generation (used for memory reads)
- **Port 4**: Store address and data generation (used for memory writes)
- **Port 5**: Integer ALU, floating-point addition
- **Port 6**: Branch unit (used for jumps, calls, returns)
- **Port 7**: SIMD/floating-point operations, shuffle, logic

Workloads that rely heavily on one type of instruction (e.g., many integer multiplications) may saturate a single port (like port 1), becoming a bottleneck even if other ports are underutilized.


## Branch Prediction (Haswell-E)

* Multi-level, dynamic predictor
* 2-bit saturating counters
* Gshare-style + TAGE-like logic
* Branch Target Buffer (BTB)
* Return Stack Buffer (RSB)

---

## Lab Outline

1. Studying IPC (Instruction Per Cycle)

   * Loop unrolling
   * SIMD (AVX2) optimization
2. Branch prediction
3. Investigating cache behavior (L1/L2/L3)
4. Compiler flags effect
5. SMT (Simultaneous Multithreading) interference

---

## 1. Studying IPC

### Baseline scalar loop

```c
long sum = 0;
for (long i = 0; i < 100000000; ++i) {
    sum += i * 2 + 1;
}
```

Compile and run:

```bash
gcc -O2 -o simple_compute simple_compute.c
taskset -c 0 perf stat -e cycles,instructions ./simple_compute
```

Observed IPC: \~0.65

### Why isn't IPC = 4?

* **Loop-carried dependency** on `sum`
* Integer-only operations saturate ALU ports
* Backend-limited (not enough ILP)

### Unrolling

* 2-way: \~0.7 IPC
* 4-way: \~0.8 IPC
* Still backend bound due to integer port pressure

### SIMD Version

Using AVX2:

* 256-bit SIMD = 8x int32 in one instruction
* Achieved IPC \~1.55

```c
__m256i idx = _mm256_set_epi32(...);
__m256i tmp = _mm256_add_epi32(...);
acc = _mm256_add_epi32(acc, tmp);
```

#### Warning:

SIMD version used int32\_t — caused **integer overflow**
Correct scalar sum: `10000000000000000`
SIMD result: incorrect due to overflow

---

## 2. Branch Prediction

### Predictable Branch

```c
if (i < 50000000) x++; else x--;
```

* Branch miss rate: \~0.005%
* Predictor learns quickly
* IPC observed: **5.25** (inflated)

**Why IPC > 4?**

* Turbo Boost increases clock rate
* perf reports base-frequency cycles
* SMT may add noise

### Unpredictable Branch

```c
if (rand() % 2) x++; else x--;
```

* Branch miss rate: \~0.19%
* IPC \~1.25

**Why not worse?**

* `rand()` is pseudorandom, deterministic
* CPU still learns some patterns

For truly hard-to-predict branches:

```c
int toggle = 0;
toggle = 1 - toggle;
if (toggle) x++; else x--;
```

---

Stay tuned for parts 3–5 (Cache, Compiler flags, SMT) in the next labs!
