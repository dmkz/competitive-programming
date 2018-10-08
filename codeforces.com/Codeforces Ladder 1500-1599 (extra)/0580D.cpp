/*
    Problem: 580D. Kefa and Dishes
    
    Solution: dynamic programming, bitmasks, O(n^2 * 2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

typedef long long ll;

int main() {
    // Input:
    int n, need, nRules;
    scanf("%d %d %d", &n, &need, &nRules);
    std::vector<int> coeff(n);
    for (auto& it : coeff) scanf("%d", &it);
    std::vector<std::vector<int>> extra(n, std::vector<int>(n));
    for (int i = 0; i < nRules; ++i) {
        int prev, curr, value;
        scanf("%d %d %d", &prev, &curr, &value);
        --prev, --curr;
        extra[prev][curr] = value;
    }
    // Init dp:
    std::vector<std::vector<ll>> dp(n, std::vector<ll>(1 << n));
    for (int i = 0; i < n; ++i) {
        dp[i][1 << i] = coeff[i];
    }
    // Calc dp table:
    for (int code = 1; code < (1 << n); ++code) {
        for (int curr = 0; curr < n; ++curr) {
            if (!((code >> curr) & 1)) continue;
            for (int prev = 0; prev < n; ++prev) {
                if (!((code >> prev) & 1) || curr == prev) continue;
                dp[curr][code] = std::max(dp[curr][code], coeff[curr] + dp[prev][code - (1 << curr)] + extra[prev][curr]);
            }
        }
    }
    // Getting answer:
    ll answ = 0;
    for (int code = 1; code < (1 << n); ++code) {
        if (__builtin_popcount(code) != need) continue;
        for (int i = 0; i < n; ++i) {
            answ = std::max(answ, dp[i][code]);
        }
    }
    std::cout << answ;
    return 0;
}