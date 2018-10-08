/*
    Problem: 592C. The Big Race
    
    Solution: number theory, math, gcd, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef unsigned long long ull;

ull gcd(ull a, ull b) {
    return b == 0 ? a : gcd(b, a % b);
}

ull lcm(ull a, ull b) {
    return a / gcd(a, b) * b;
}

ull lcm_greater(ull a, ull b, ull limit) {
    a /= gcd(a, b);
    ull k = (limit + b - 1) / b;
    return a > k;
}

int main() {
    ull t, a, b, p;
    std::cin >> t >> a >> b;
    if (lcm_greater(a, b, t)) {
        p = std::min({a-1,b-1,t});
    } else {
        auto lm = lcm(a, b);
        auto x = std::min({a-1,b-1,t});
        p = t / lm * (1+x) + std::min({a-1,b-1,t % lm});
    }
    std::cout << p / gcd(p,t) << "/" << t / gcd(p, t);
    return 0;
}