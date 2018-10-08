/*
    Problem: 268B. Buttons
    
    Solution: implementation, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n; std::cin >> n;
    int r = n;
    for (int i = 1; i < n; ++i) {
        r += i * (n-i);
    }
    std::cout << r;
    return 0;
}