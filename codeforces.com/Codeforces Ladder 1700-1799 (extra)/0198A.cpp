/*
    Problem: 198A. About Bacteria
    
    Solution: geometry progression, math, binary search, number theory, O(log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;
typedef __float128 Real;

ll solve(ll k, ll b, ll n, ll t) {
    if (k == 1) {
        // 1 - t + b * (n - m) <= 0
        ll low = -1, high = n;
        while (high - low > 1) {
            ll mid = (low + high) / 2;
            if (1 - t + b * (n - mid) <= 0) {
                high = mid;
            } else {
                low = mid;
            }
        }
        return high;
    }
    // x(n, t) = k^n * t + b * (k^n - 1) / (k - 1)
    ll answ = n;
    Real pow = 1;
    while (answ > 0 && (k-1) * (pow * k - t) + b * (pow * k - 1) <= 0) {
        pow *= k;
        answ--;
    }
    return answ;
}


int main() {
    ll k, b, n, t;
    while (std::cin >> k >> b >> n >> t) {
        std::cout << solve(k, b, n, t) << std::endl;
    }
    return 0;
}