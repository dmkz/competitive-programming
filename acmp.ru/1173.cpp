#include <stdio.h>
#include <cassert>

void euclid(int a, int b, int& x, int& y, int& d) {
// Вычисление: a * x + b * y = gcd(a, b) = d
    if (a < b) {
        return euclid(b, a, y, x, d);
    }
    
    assert(a >= b && b >= 0);
    
    if (b == 0) {
        d = a, x = 1, y = 0;
        return;
    }

    int q, r, x2 = 1, x1 = 0, y2 = 0, y1 = 1;

    while (b > 0) {
        q = a / b;
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b; 
        b = r;
        x2 = x1, x1 = x, y2 = y1, y1 = y;
    }
    d = a, x = x2, y = y2;
}

int main() {
    int a, m; 
    scanf("%d %d", &a, &m);
    int x, y, d;
    euclid(a, m, x, y, d);
    if (x < 0) x += m;
    assert(0 <= x && x < m);
    if (1LL * a * x % m != 1) {
        printf("No solution");
    } else {
        printf("%d", x);
    }
    return 0;
}