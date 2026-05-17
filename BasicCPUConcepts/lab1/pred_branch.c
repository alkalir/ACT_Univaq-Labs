#include <stdio.h>

int main() {
    int x = 0;
    for (int i = 0; i < 100000000; ++i) {
        if (i < 50000000)
            x += 1;
        else
            x -= 1;
    }
    printf("x = %d\n", x);
    return 0;
}

