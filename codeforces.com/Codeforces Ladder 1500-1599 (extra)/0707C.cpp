/*
    Problem: 707C. Pythagorean Triples
    
    Solution: math, constructive, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int main() {
    ll a; std::cin >> a;
    if (a == 1 || a == 2) { std::cout << -1; return 0; }
    if (a == 3) { std::cout << "4 5"; return 0; }
    if (a % 4 == 0) { std::cout << 3 * (a / 4) << ' ' << 5 * (a / 4); return 0; }
    if (a % 2 == 0) {
        // c = a^2/4+1, b=a^2/4-1
        // a^2 = c^2-b^2 = (c - b) * (c + b) = 2 * (a^2 / 2) = a^2
        std::cout << a*a/4-1 << ' ' << a*a/4+1; return 0;
    }
    if (a % 2 == 1) {
        // a = 2*k+1
        // a^2 = 4*k^2+4*k+1 = (2*k^2+k+1) * (2*k^2-k-1)
        // c = k+1, b = k;
        // (c-b)(c+b) = 2*k+1
        // c = a^2/2+1, b = a^2/2
        // (c-b)(c+b)
        std::cout << a*a/2 << ' ' << a * a/2+1; return 0;
    }
    return 0;
}