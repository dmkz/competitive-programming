/*
    Problem: 813B. The Golden Age
    
    Solution: math, number theory, O(log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

typedef long long ll;

std::vector<ll> get_powers(ll x, ll limit) {
    std::vector<ll> xp{1};
    while (xp.back() <= limit / x) {
        xp.push_back(xp.back() * x);
    }
    return xp;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    ll x, y, l, r; std::cin >> x >> y >> l >> r;
    
    auto xp = get_powers(x, r);
    auto yp = get_powers(y, r);
    
    std::vector<ll> res;
    for (auto& it_x : xp) {
        for (auto& it_y : yp) {
            res.push_back(it_x + it_y);
        }
    }
    std::sort(res.begin(), res.end());
    res.erase(std::unique(res.begin(), res.end()), res.end());
    while (!res.empty() && res.back() > r) res.pop_back();
    std::reverse(res.begin(), res.end());
    while (!res.empty() && res.back() < l) res.pop_back();
    if (res.empty()) {
        std::cout << r - l + 1; return 0;
    }
    res.push_back(l-1);
    std::reverse(res.begin(), res.end());
    res.push_back(r+1);

    ll answ = 0;
    for (int i = 1; i < (int)res.size(); ++i) {
        answ = std::max(answ, res[i] - res[i-1] - 1);
    }
    std::cout << answ;
    return 0;
}