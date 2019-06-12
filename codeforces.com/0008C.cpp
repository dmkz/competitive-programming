/*
    Problem: 8C. Looking for Order
    
    Solution: dynamic programming, bitmasks, O(n * 2^n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
int xc, yc, n, x[24], y[24], dp[1 << 24], di[24], dij[24][24];
int main() {
    std::cin >> xc >> yc >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; i++) {
        di[i] = (x[i] - xc) * (x[i] - xc) + (y[i] - yc) * (y[i] - yc);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dij[i][j] = (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]) + di[i] + di[j];
        }
    }
    for (int mask = 1; mask < (1 << n); mask++) {
        int i = 0; while (!(mask & (1 << i))) i++;
        dp[mask] = dp[mask ^ (1 << i)] + 2 * di[i];
        for (int j = i+1; j < n; ++j) {
            if (mask & (1 << j)) {
                dp[mask] = std::min(dp[mask], dp[mask ^ (1 << i) ^ (1 << j)] + dij[i][j]);
            }
        }
    }
    int mask = (1 << n) - 1;
    std::cout << dp[mask] << std::endl;
    std::vector<int> answ{0};
    while (mask > 0) {
        int i = 0; while (!(mask & (1 << i))) i++;
        if (dp[mask] == dp[mask ^ (1 << i)] + 2 * di[i]) {
            answ.push_back(i+1);
            answ.push_back(0);
            mask ^= (1 << i);
            continue;
        }
        for (int j = i+1; j < n; ++j) {
            if (mask & (1 << j)) {
                if (dp[mask] == dp[mask ^ (1 << i) ^ (1 << j)] + dij[i][j]) {
                    answ.push_back(i+1);
                    answ.push_back(j+1);
                    answ.push_back(0);
                    mask ^= (1 << i) | (1 << j);
                    break;
                }
            }
        }
    }
    for (auto it : answ) { std::cout << it << ' '; }
    std::cout << std::endl;
    return 0;
}