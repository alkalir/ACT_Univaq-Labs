#include <stdio.h>
#include <stdlib.h>

int main() {
    int x = 0;
    srand(42);  // fixed seed for reproducibility
    for (int i = 0; i < 100000000; ++i) {
        if (rand() % 2)
            x += 1;
        else
            x -= 1;
    }
    printf("x = %d\n", x);
    return 0;
}

