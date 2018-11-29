/*
    Problem: 303A. Lucky Permutation Triple
    
    Solution: math, constructive, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cassert>

int main() {
    int n;
    while (std::cin >> n) {
        if (n % 2 == 0) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::vector<int> a(n), b(n), c(n), was(n);
        for (int i = 0; i < n; ++i) {
            a[i] = i;
            b[i] = (i+1)%n;
            c[i] = (a[i] + b[i]) % n;
            assert(!was[c[i]]);
            was[c[i]] = 1;
        }
        for (auto it : a) { std::cout << it << ' '; } 
        std::cout << std::endl;
        for (auto it : b) { std::cout << it << ' '; } 
        std::cout << std::endl;
        for (auto it : c) { std::cout << it << ' '; } 
        std::cout << std::endl;
    }
    return 0;
}

