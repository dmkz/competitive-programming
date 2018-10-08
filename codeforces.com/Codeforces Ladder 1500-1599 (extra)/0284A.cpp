/*
    Problem: 284A. Cows and Primitive Roots
    
    Solution: math, number theory, implementation, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>

bool is_primitive_root(int x, int mod) {
    int res = 1;
    for (int pow = 1; pow < mod-1; ++pow) {
        res = (res * x) % mod;
        if (res == 1) return false;
    }
    res = (res * x) % mod;
    return (res == 1);
}

int main() {
    int p, answ = 0; scanf("%d", &p);
    for (int x = 0; x < p; ++x) {
        answ += is_primitive_root(x, p);
    }
    printf("%d", answ);
    return 0;
}