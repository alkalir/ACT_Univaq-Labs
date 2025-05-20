#include <stdio.h>

int main() {
    long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    for (long i = 0; i < 100000000; i += 4) {
        s1 += i * 2 + 1;
        s2 += (i + 1) * 2 + 1;
        s3 += (i + 2) * 2 + 1;
        s4 += (i + 3) * 2 + 1;
    }
    long sum = s1 + s2 + s3 + s4;
    printf("Sum is %ld\n", sum);
    return 0;
}

