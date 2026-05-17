#include <stdio.h>

int main() {
    long sum1 = 0, sum2 = 0;
    for (long i = 0; i < 100000000; i += 2) {
        sum1 += i * 2 + 1;
        sum2 += (i + 1) * 2 + 1;
    }
    long sum = sum1 + sum2;
    printf("Sum is %ld\n", sum);
    return 0;
}
