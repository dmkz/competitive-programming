/*
    Problem: 204A. Little Elephant and Interval
    
    Solution: math, binary search, number theory, O(log(n)^2 * |A|)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef long long ll;
ll solve(ll r) {
    if (r == 0) { return 1; }
    if (r < 10) { return r+1; }
    ll ret = 10;
    for (int digit = 1; digit <= 9; ++digit) {
        for (int len = 2; len <= 18; ++len) {
            ll pow10 = 1;
            for (int i = len-1; i--; pow10 *= 10);
            ll low = -1, high = pow10 / 10;
            while (high - low > 1) {
                ll mid = (high + low) / 2;
                if (10 * mid + pow10 * digit + digit <= r) {
                    low = mid;
                } else {
                    high = mid;
                }
            }
            ret += low+1;
        }
    }
    return ret;
}
int main() {
    for (ll l, r; std::cin >> l >> r; std::cout << solve(r) - solve(l-1) << std::endl);
    return 0;
}