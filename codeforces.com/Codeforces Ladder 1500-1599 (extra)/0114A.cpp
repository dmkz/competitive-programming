/*
    Problem: 114A. Cifera
    
    Solution: math, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

int main() {
    ll k, n; std::cin >> k >> n;
    ll res = k, p = 0;
    while (res < n) { res *= k; ++p; }
    if (n == res) { std::cout << "YES\n" << p; } else { std::cout << "NO"; }
    return 0;
}