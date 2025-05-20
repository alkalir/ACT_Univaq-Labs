#include <immintrin.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    const int N = 100000000;
    __m256i acc = _mm256_setzero_si256(); // [0, 0, 0, 0, 0, 0, 0, 0]

    for (int i = 0; i < N; i += 8) { //Loop in steps of 8
        __m256i idx = _mm256_set_epi32(i+7, i+6, i+5, i+4, i+3, i+2, i+1, i); // Load 8 consecutive integers into a SIMD register
        __m256i two = _mm256_set1_epi32(2); // [2, 2, 2, ..., 2]
        __m256i one = _mm256_set1_epi32(1); // [1, 1, ..., 1]
        __m256i tmp = _mm256_add_epi32(_mm256_mullo_epi32(idx, two), one);  // compute i * 2 + 1 for all 8 lanes
        acc = _mm256_add_epi32(acc, tmp);  // accumulate
    }

    // Horizontal sum of acc (8 x int32_t)
    int32_t result[8];
    _mm256_storeu_si256((__m256i*)result, acc); //Store vector acc to a memory array
    int32_t sum = 0;
    for (int j = 0; j < 8; ++j)
        sum += result[j];

    printf("Sum is %d\n", sum);
    return 0;
}

