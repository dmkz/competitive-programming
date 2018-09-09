/*
    Problem: 762A. k-th divisor
    
    Solution: math, number theory, divisors, O(sqrt(n)+k)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll n, k;
    std::cin >> n >> k;
    std::vector<ll> answ{1}, stack{n};
    for (ll i = 2; i * i <= n; ++i) {
        ll j = n / i;
        if (i * j == n) {
            answ.push_back(i);
            stack.push_back(j);
        }
    }
    if (stack.back() == answ.back()) stack.pop_back();
    while (!stack.empty()) { answ.push_back(stack.back()); stack.pop_back(); }
    if (k-1 >= (ll)answ.size()) {
        std::cout << -1;
        return 0;
    }
    std::cout << answ[k-1];
    return 0;
}