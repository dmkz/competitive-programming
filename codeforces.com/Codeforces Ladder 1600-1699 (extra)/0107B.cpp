/*
    Problem: 107B. Basketball Team
    
    Solution: math, probability theory, O(m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

typedef long double Real;

Real C(int n, int k) {
    if (k > n) return 0;
    if (k > n - k) return C(n, n-k);
    Real res = 1;
    for (int i = 1; i <= k; ++i) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

int main() {
    std::cout << std::fixed << std::setprecision(6);
    int n, nF, id;
    while (std::cin >> n >> nF >> id) {
        int sumWithout = 0, sumWith = 0;
        for (int i = 1, v; i <= nF; ++i) {
            std::cin >> v;
            sumWithout += (i != id) * v;
            sumWith += v;
        }
        if (sumWith < n) {
            std::cout << -1 << "\n";
        } else {
            std::cout << 1 - C(sumWithout, n-1) / C(sumWith-1, n-1) << std::endl;
        }
    }
    return 0;
}