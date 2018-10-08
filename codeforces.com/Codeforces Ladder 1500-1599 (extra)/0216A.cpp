/*
    Problem: 216A. Tiling with Hexagons
    
    Solution: math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

int main() {
    int a, b, c; std::cin >> a >> b >> c;
    if (b > c) std::swap(b,c);
    int answ = 0;
    for (int i = 1; i < b; ++i) {
        answ += a++;
    }
    answ *= 2;
    for (int i = b; i <= c; ++i) {
        answ += a;
    }
    std::cout << answ;
    return 0;
}