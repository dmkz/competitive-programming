/*
    Problem: 808A. Lucky Year
    
    Solution: implementation, math, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int64_t n, pow = 1; std::cin >> n;
    if (n < 10) {std::cout << 1; return 0; }
    while (pow * 10 <= n) pow *= 10;
    std::cout << (n/pow+1)*pow - n;
    return 0;
}