/*
    Problem: 165B. Burning Midnight Oil
    
    Solution: math, binary search, O(log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

ll sum(ll v, ll k) {
    ll pow = 1, res = 0;
    while (pow <= v) {
        res += v / pow;
        pow *= k;
    }
    return res;
}

ll solve(ll n, ll k) {
    ll low = 0, high = (k * n);
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (sum(mid,k) >= n) {
            high = mid;
        } else low = mid;
    }
    return high;
}

int main() {
    ll n, k; std::cin >> n >> k;
    std::cout << solve(n,k);
    return 0;
}