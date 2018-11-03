/*
    Problem: 689C. Mike and Chocolate Thieves
    
    Solution: binary search, math, number theory, O(log(m)*cbrt(m))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

ll count(ll limit) {
    ll answ = 0;
    for (ll i = 2; i * i * i <= limit; ++i) {
        answ += limit / (i * i * i);
    }
    return answ;
}

int main() {
    ll m;
    while (std::cin >> m) {
        ll low = 1, high = (ll)1e18L;
        while (high - low > 1) {
            ll mid = (high + low) / 2;
            if (count(mid) >= m) {
                high = mid;
            } else {
                low = mid;
            }
        }
        // answer is high
        std::cout << (count(high) == m ? high : -1) << std::endl;
    }
    return 0;
}