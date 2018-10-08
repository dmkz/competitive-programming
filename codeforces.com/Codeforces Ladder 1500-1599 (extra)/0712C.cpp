/*
    Problem: 712C. Memory and De-Evolution
    
    Solution: greedy, math, number theory, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <cassert>
#include <algorithm>

int solve(int a, int b, int c, int need) {
    if (a > b) return solve(b, a, c, need);
    if (b > c) return solve(a, c, b, need);
    assert(a <= b && b <= c && c <= need);
    if (a == need && b == need && c == need) return 0;
    assert(a+b > c);
    assert(a+c > b);
    assert(b+c > a);
    // increase minimal side of triangle:
    // a + b > c --> a > c - b
    // a + c > b --> a > b - c
    // b + c > a
    int na = std::min(need, b+c-1);
    assert(na > a);
    return 1+solve(na,b,c,need);
}

int main() {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d", solve(y,y,y,x));
    return 0;
}