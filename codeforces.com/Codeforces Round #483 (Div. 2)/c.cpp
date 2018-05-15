#pragma GCC diagnostic ignored "-Wunused-result"
#include <stdio.h>
#include <bits/stdc++.h>

typedef int64_t Int;

Int gcd(Int a, Int b) {
    while (b != 0) {
        auto rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

bool is_finite(Int p, Int q, Int b) {
    if (p == 0 || p % q == 0) {
        return true;
    }
    auto gcd = ::gcd(p, q);
    p /= gcd;
    q /= gcd;
    p %= q;
    b %= q;
    
    // b and q are have same prime divisors
    while (q > 1) {
        auto gcd = ::gcd(q, b);
        if (gcd == 1) return false;
        b = gcd;
        q /= gcd;
    }
    return true;    
}

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
    Int n; std::cin >> n;
    for (int i = 0; i < n; ++i) {
        Int p, q, b; std::cin >> p >> q >> b;
        std::cout << (is_finite(p, q, b) ? "Finite\n" : "Infinite\n");
    }
    return 0;
}