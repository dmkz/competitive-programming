/*
    Problem: 439B. Devu, the Dumb Guy
    
    Solution: sorting, greedy, math, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;

int main() {
    ll n, x; std::cin >> n >> x;
    std::vector<ll> cnt(n);
    for (auto& it : cnt) std::cin >> it;
    std::sort(cnt.begin(), cnt.end());
    ll answ = 0;
    for (int i = 0; i < n; ++i) {
        answ += cnt[i] * std::max(ll(1), (x - i));
    }
    std::cout << answ;
    return 0;
}