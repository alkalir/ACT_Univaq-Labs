#include <immintrin.h> //provides intrinsics for AVX, AVX2, SSE
#include <stdio.h>

int main() {
    const long N = 100000000;
    __m256i acc = _mm256_setzero_si256(); //256-bit AVX2 register of 4 x 64-bit integers, acts as accumulator [0,0,0,0]

    for (long i = 0; i < N; i += 4) { //each iteration now processes 4 values at once using AVX2
        __m256i idx = _mm256_set_epi64x(i+3, i+2, i+1, i);     // Load 4 consecutive long values into a SIMD register
        __m256i two = _mm256_set1_epi64x(2); // [2, 2, 2, 2]
        __m256i one = _mm256_set1_epi64x(1); // [1, 1, 1, 1]
        __m256i tmp = _mm256_add_epi64(_mm256_mullo_epi64(idx, two), one);  // Perform i * 2 + 1 for all 4 values in parallel
        acc = _mm256_add_epi64(acc, tmp);                    // Accumulate the results
    }

    // Horizontal sum of acc (4 x 64-bit integers)
    long result[4];
    _mm256_storeu_si256((__m256i*)result, acc); //Store the SIMD register back to memory
    long sum = result[0] + result[1] + result[2] + result[3]; //Final reduction to a scalar

    printf("Sum is %ld\n", sum);
    return 0;
}

