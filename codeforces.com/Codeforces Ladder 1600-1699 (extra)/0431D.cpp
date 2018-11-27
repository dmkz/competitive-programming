/*
    Problem: 431D. Random Task
    
    Solution: binary search, math, combinatorics, dynamic programming, O(log(n)^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

typedef long long ll;

const ll INF = (ll)1e18L+10;

ll bin[64][64];

void precalc() {
    bin[0][0] = 1;
    for (int n = 1; n < 64; ++n) {
        for (int k = 0; k <= n; ++k) {
            bin[n][k] = std::min(INF, bin[n-1][k] + (k == 0 ? 0 : bin[n-1][k-1]));
        }
    }
}

ll count(ll limit, int n1) {
    ll answ = 0;
    for (int bit = 60; n1 >= 0 && bit >= 0; --bit) {
        if ((limit >> bit) & 1) {
            answ = std::min(INF, answ+bin[bit][n1]);
            n1--;
        }
    }
    return answ;
}

ll solve(ll need, int n1) {
    ll low = 0, high = (ll)1e18L+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        ll cnt = count(2*mid, n1)-count(mid, n1);
        if (need <= cnt) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return high;
}

int main() {
    precalc();
    ll need; int n1;
    while (std::cin >> need >> n1) {
        std::cout << solve(need, n1) << std::endl;
    }
    return 0;
}