/*
    Problem: 478B. Random Teams
    
    Solution: math, combinatorics, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

int main() {
    ll n, m; std::cin >> n >> m;
    ll max = (n - m + 1) * (n - m) / 2;
    ll k = n / m;
    // a * k + b * (k+1) = n
    // a + b = m
    // a * k + (m - a) * (k+1) = n
    // a * k + m * k - a * k = n - m + a
    // m * k = n - m + a
    // a = m * (k+1) - n
    ll a = m * (k+1) - n;
    ll b = m - a;
    assert(a * k + b * (k+1) == n);
    ll min = a * k * (k-1) / 2 + b * (k+1) * k / 2;
    std::cout << min << ' ' << max;
    return 0;
}