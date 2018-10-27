/*
    Problem: 348A. Mafia
    
    Solution: sorting, deque, math, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <deque>

typedef long long ll;

ll solve(std::vector<ll> arr) {
    ll n = (ll)arr.size();
    std::sort(arr.begin(), arr.end());
    std::deque<ll> deque;
    for (auto& it : arr) {
        deque.push_back(it);
    }
    ll nRounds = 0;
    while (deque.front() - nRounds > 0 && deque.front() != deque.back()) {
        ll curr = deque.back() - deque.front();
        nRounds += curr;
        deque.push_back(deque.back());
        deque.pop_front();
    }
    if (deque.front() - nRounds <= 0) {
        return nRounds + std::max(ll(0), deque.back() - nRounds);
    }
    ll minValue = deque.front() - nRounds;
    ll nOp = minValue / (n - 1);
    nRounds += nOp * n;
    minValue -= nOp * (n - 1);
    assert(minValue < n);    
    return nRounds + (minValue <= 0 ? 0 : minValue + 1);
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; 
    while (std::cin >> n) {
        std::vector<ll> arr(n);
        for (auto& it : arr) { std::cin >> it; }
        std::cout << solve(arr) << std::endl;
    }
    return 0;
}