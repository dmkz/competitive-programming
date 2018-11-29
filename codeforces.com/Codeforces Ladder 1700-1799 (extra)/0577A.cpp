/*
    Problem: 577A. Multiplication Table
    
    Solution: brute force, number theory, math, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n, x;
    while (std::cin >> n >> x) {
        int answ = 0;
        for (int i = 1; i <= n; ++i) {
            answ += x % i == 0 && x / i <= n;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}