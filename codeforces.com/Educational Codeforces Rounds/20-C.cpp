/*
    Problem: 803C. Maximal GCD
    
    Solution: math, greedy, O(sqrt(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

typedef long long ll;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll n, k; std::cin >> n >> k;
    
    ll last = (ll)std::sqrt(2*n);
    while ((last+1)*(last+2)/2 <= n) ++last;
    while (last*(last+1)/2 > n) --last;
    if (k > last) { std::cout << -1; return 0; }
    
    std::vector<ll> div{1}, stack{n};
    for (ll i = 2; i * i <= n; ++i) {
        ll j = n / i;
        if (i * j == n) {
            div.push_back(i);
            stack.push_back(j);
        }
    }
    if (stack.back() == div.back()) stack.pop_back();
    while (!stack.empty()) { div.push_back(stack.back()); stack.pop_back(); }
    
    ll max = 0;
    for (ll gcd : div) {
        ll rem = n / gcd;
        if (k * (k+1) / 2 <= rem) {
            max = std::max(gcd, max);
        }
    }
    assert(max != 0);
    std::vector<ll> answ;
    ll rem = n / max;
    for (ll a = 1; a < k; ++a) {
        answ.push_back(a * max);
        rem -= a;
    }
    answ.push_back(rem * max);
    for (auto it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}