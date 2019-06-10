/*
    Problem: 148E. Porcelain
    
    Solution: dynamic programming, O(n * m * mxSize)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
const int INF = (int)1e9+7;
template<typename X, typename Y> X& remax(X& x, Y y) { return x = (x > y) ? x : y; }
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, m; std::cin >> n >> m; ) {
        std::vector<int> dp(1+m, -INF);
        dp[0] = 0;
        while (n--) {
            int k; std::cin >> k;
            std::vector<int> arr(k), min(1+k, -INF);
            for (auto &it : arr) { std::cin >> it; }
            auto sum = arr;
            sum.push_back(0);
            for (int i = k-1; i >= 0; --i) {
                sum[i] += sum[i+1]; 
            }
            for (int len = 0; len <= k; ++len) {
                for (int l = 0; l + len - 1 < k; ++l) {
                    remax(min[k-len], sum[0] - (sum[l] - sum[l+len]));
                }
            }
            for (int was = m; was >= 0; --was) {
                for (int cnt = 0; cnt <= k && was + cnt <= m; ++cnt) {
                    remax(dp[was+cnt], dp[was]+min[cnt]);
                }
            }
        }
        std::cout << dp[m] << std::endl;
    }
    return 0;
}