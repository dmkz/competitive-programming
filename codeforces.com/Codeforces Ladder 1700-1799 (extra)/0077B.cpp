/*
    Problem: 77B. Falling Anvils
    
    Solution: math, probability theory, O(t)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>

typedef long double Real;

Real solve(const int P, const int Q) {
    if (Q == 0) {
        return 1;
    }
    if (P == 0) {
        return 0.5;
    }
    Real p = std::min(P, 4 * Q);
    return 1 - (Q * p - p * p / 8) / P / (2 * Q);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    std::cout << std::fixed << std::setprecision(6);
    int nT;
    while (std::cin >> nT) {
        for (int i = 0; i < nT; ++i) {
            int P, Q; std::cin >> P >> Q;
            std::cout << solve(P, Q) << "\n";
        }
        std::cout << std::endl;
    }
    return 0;
}