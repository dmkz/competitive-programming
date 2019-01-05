/*
    Problem: 7262. A coincidence
    
    Solution: dynamic programming, probability theory, expected value, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

typedef long double ld;

int main() {
    /* ------------------------------ Precalculation part ------------------------------ */
    const int NMAX = 1000;
    std::cout << std::fixed << std::setprecision(6);
    std::vector<ld> fact(1+NMAX), subfact(1+NMAX);
    fact[0] = 1; fact[1] = 1; fact[2] = 2;
    subfact[0] = 1; subfact[2] = 1;
    for (int i = 3; i <= NMAX; ++i) {
        fact[i] = (i-1)*(fact[i-1] + fact[i-2]);
        subfact[i] = (i-1)*(subfact[i-1] + subfact[i-2]);
    }
    std::vector<ld> expected(1+NMAX);
    for (int n = 1; n <= NMAX; ++n) {
        ld res = subfact[n] / fact[n];
        for (int k = 0; k < n; ++k) {
            res += (subfact[k] / fact[k] / fact[n-k] * (expected[k] + 1));
        }
        expected[n] = res / (1 - subfact[n] / fact[n]);
    }
    /* ------------------------------      Solution       ------------------------------ */
    int n, cnt = 0; std::cin >> n;
    for (int i = 1, v; i <= n; ++i) {
        std::cin >> v; cnt += (i != v);
    }
    std::cout << expected[cnt] << std::endl;
    return 0;
}