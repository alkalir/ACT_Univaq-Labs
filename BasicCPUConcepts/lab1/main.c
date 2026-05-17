#include <stdio.h>

int main() {
    long sum = 0;
    for (long i = 0; i < 100000000; i++) {
        sum += i * 2 + 1;
    }
    printf("Sum is %ld\n", sum);
    return 0;
}
