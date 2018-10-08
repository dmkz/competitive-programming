/*
    Problem: 265B. Roadside Trees (Simplified Edition)
    
    Solution: greedy, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>

int main() {
    int n, prev = 1, answ = 0; std::cin >> n;
    while (n--) {
        int h; std::cin >> h;
        answ += 2 + std::abs(h-prev);
        prev = h;
    }
    std::cout << answ;
    return 0;
}