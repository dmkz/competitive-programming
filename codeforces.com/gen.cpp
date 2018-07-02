#include <stdio.h>

int main() {
    int n = 500, k = 1000;
    printf("%d %d\n", n, k);
    for (int i = 1; i <= n; ++i) {
        printf("%d ", 2 * i);
    }
    return 0;
}