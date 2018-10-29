/*
    Problem: 287B. Pipeline
    
    Solution: math, greedy, binary search, O(log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

const ll INF = (ll)1e18L;

ll solve(ll res, ll need, ll k) {
    if (k == 0 && res < need) {
        return -INF;
    }
    if (res >= need) {
        return 0;
    }
    if (res - 1 + k >= need) {
        return 1;
    }
    // res - n + (k + k - n + 1) * n / 2
    ll low = 0, high = k+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (res - mid + (2 * k - mid + 1) * mid / 2 >= need) {
            high = mid;
        } else {
            low = mid;
        }
    }
    res = res - low + (2 * k - low + 1) * low / 2;
    k -= low;
    return low + solve(res, need, k);
}

int main() {
    ll n, k;
    while (std::cin >> n >> k) {
        ll ret = std::max(ll(-1), solve(1, n, k));
        std::cout << ret << std::endl;
    }
    return 0;
}