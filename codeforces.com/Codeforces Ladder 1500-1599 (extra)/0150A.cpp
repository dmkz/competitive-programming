/*
    Problem: 150A. Win or Freeze
    
    Solution: math, constructive, O(sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int main() {
    ll n; std::cin >> n;
    if (n == 1) { std::cout << "1\n0"; return 0; }
    ll prod = n;
    std::vector<ll> answ;
    for (ll i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            answ.push_back(i);
            n /= i;
        }
    }
    if (n > 1) {
        answ.push_back(n);
        std::sort(answ.begin(), answ.end());
    }
    if (answ.size() == 1u) {
        std::cout << "1\n0"; return 0;
    }
    if (answ.size() == 2u) {
        std::cout << "2"; return 0;
    }
    std::cout << "1\n" << answ.front() * answ.back() << std::endl;
    return 0;
}