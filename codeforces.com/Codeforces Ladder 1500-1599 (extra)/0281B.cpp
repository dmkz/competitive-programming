/*
    Problem: 281B. Nearest Fractione
    
    Solution: number theory, math, gcd, fractions, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>
#include <cassert>

typedef long long ll;

bool less(ll x, ll y, ll p1, ll q1, ll p2, ll q2) {
    return std::abs(x * q1 - y * p1) * q2 < std::abs(x * q2 - y * p2) * q1;
}

ll gcd(ll p, ll q) {
    return q == 0 ? p : gcd(q, p % q);
}

int main() {
    ll x, y, n; std::cin >> x >> y >> n;
    ll p = 0, q = 1;
    for (ll q1 = 1; q1 <= n; ++q1) {
        ll p1 = std::max(x * q1 / y - 2, ll(0));
        for (int i = 0; i < 5; ++i, ++p1) {
            if (less(x,y,p1,q1,p,q)) {
                p = p1, q = q1;
            }
        }
    }
    std::cout << p << "/" << q;
    return 0;
}