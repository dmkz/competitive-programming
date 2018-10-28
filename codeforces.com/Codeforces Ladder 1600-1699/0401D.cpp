/*
    Problem: 401D. Roman and Numbers
    
    Solution: dynamic programming, subsets, bitmasks, O(n * m * 2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

ll solve(std::string s, int mod) {
    // Prepare table for dynamic programming:
    const int n = (int)s.size();
    static ll cnt[1 << 18][100];
    std::fill(&cnt[0][0], &cnt[0][0] + (100 << 18), ll(0));
    cnt[0][0] = 1;
    // Precalc factorials, powers of 10 and number of equal digits:
    std::vector<ll> pow10(1+n, 1 % mod), fact(1+n,1), nDigits(10);
    for (int i = 1; i <= n; ++i) {
        pow10[i] = pow10[i-1] * 10 % mod;
        fact[i] = fact[i-1] * i;
        nDigits[s[i-1]-'0']++;
    }
    // Run DP over subsets:
    for (int mask = 1; mask < (1 << n); ++mask) {
        auto pow = pow10[__builtin_popcount(mask)-1];
        for (int j = 0; j < n; ++j) {
            if (!((mask >> j) & 1)) continue; 
            auto fromMask = mask ^ (1 << j);
            for (int rem = 0; rem < mod; ++rem) {
                auto nRem = (rem + (s[j] - '0') * pow) % mod;
                cnt[mask][nRem] += cnt[fromMask][rem];
            }
        }
    }
    // Calculate answer:
    ll answ = 0;
    for (int j = 0; j < n; ++j) {
        if (s[j] == '0') continue;
        auto mask = ((1 << n) - 1) ^ (1 << j);
        auto pow = pow10[__builtin_popcount(mask)];
        auto rem = (mod - ((s[j] - '0') * pow) % mod) % mod;
        answ += cnt[mask][rem];
    }
    for (int d = 0; d < 10; ++d) {
        answ /= fact[nDigits[d]];
    }
    return answ;
}

int main() {
    std::string s; int mod;
    while (std::cin >> s >> mod) {
        std::cout << solve(s, mod) << std::endl;
    }
    return 0;
}