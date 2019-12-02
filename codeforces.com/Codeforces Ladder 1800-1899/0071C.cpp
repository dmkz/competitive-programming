/*
    Problem: 71C. Round Table Knights
    Solution: number theory, divisors, brute force, dynamic programming, O(n*sqrt(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
const int INF = (int)1e9+7;
int main() {
    for (int n; std::cin >> n; ) {
        vi good(n), dp(n);
        for (auto &it : good) std::cin >> it;
        vi divs;
        for (int i = 1; i * i <= n; i++) {
            int j = n / i;
            if (i * j == n) {
                divs.push_back(i);
                divs.push_back(j);
            }
        }
        std::sort(all(divs));
        bool ok = false;
        for (int step : divs) {
            const int need = n / step;
            for (int i = 0; i < n; i++) {
                if (good[i]) {
                    dp[i] = (i-step >= 0 ? dp[i-step] : 0) + 1;
                } else {
                    dp[i] = -INF;
                }
                ok = ok || (dp[i] == need && need >= 3);
            }
        }
        std::cout << (ok ? "YES\n" : "NO\n");
    }
    return 0;
}