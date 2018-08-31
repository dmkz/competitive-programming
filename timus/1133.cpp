/*
    Problem: 1133. Fibonacci Sequence
    
    Solution: binary search, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <functional>
typedef long long ll;
int main() {
    ll i, fi, j, fj, k;
    std::cin >> i >> fi >> j >> fj >> k;
    if (i > j) std::swap(i,j), std::swap(fi,fj);
    std::function<bool(ll)> less_or_equal = [&](const ll value) {
        ll curr = value, prev = fi;
        for (ll id = i+2; id <= j; ++id) {
            ll next = curr + prev;
            prev = curr;
            curr = next;
            if (curr >=  (ll)2e14L) return false;
            if (curr <= -(ll)2e14L) return true;
        }
        return curr <= fj;
    };
    ll low = -2e9, high = 2e9;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (less_or_equal(mid)) {
            low = mid;
        } else high = mid;
    }
    if (k > i) {
        ll prev = fi, curr = low;
        for (ll id = i+2; id <= k; ++id) {
            ll next = prev + curr;
            prev = curr;
            curr = next;
        }
        std::cout << curr;
    } else {
        ll prev = low, curr = fi;
        for (ll id = i-1; id >= k; --id) {
            ll next = prev - curr;
            prev = curr;
            curr = next;
        }
        std::cout << curr;
    }
    return 0;
}