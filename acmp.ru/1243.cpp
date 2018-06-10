#include <stdio.h>

int main() {
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    b += 100 * a;
    b *= n;
    a = b / 100;
    b %= 100;
    printf("%d %d", a, b);
    return 0;
}