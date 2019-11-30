/*
    Problem: 312B. Archer
    Solution: math, probability theory, O(eps)
*/
#include <bits/stdc++.h>
typedef long double ld;
int main() {
    ld a, b, c, d; std::cin >> a >> b >> c >> d;
    ld p = a / b, q = c / d;
    ld res = p, coeff = (1-p)*(1-q), pow = 1;
    for (int i = 1; i < (int)1e6; i++) {
        pow *= coeff;
        res += pow * p;
    }
    std::cout << std::fixed << std::setprecision(6) << res << std::endl;
}