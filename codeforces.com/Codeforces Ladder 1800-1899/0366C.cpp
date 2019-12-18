/*
    Problem: 366C. Dima and Salad
    Solution: dynamic programming, O(AMAX * n^2)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using pii = std::pair<int,int>;
const int INF = (int)1e9+7;
template<typename A, typename B> A& remax(A& a, B b) { return a = (b > a ? b : a); }
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    for (int n, k; std::cin >> n >> k; ) {
        const int SMAX = 10000;
        vi dp(2*SMAX+1, -INF), next(2*SMAX+1,-INF);
        dp[SMAX] = 0;
        vi w(n), c(n), a(n), b(n);
        for (auto &it : a) std::cin >> it;
        for (auto &it : b) std::cin >> it;
        for (int i = 0; i < n; i++) {
            w[i] = a[i] - k * b[i];
            c[i] = a[i];
        }
        for (int i = 0; i < n; i++) {
            next = dp;
            for (int s = 0; s < isz(dp); s++) {
                if (0 <= s - w[i] && s - w[i] < isz(dp)) {
                    remax(next[s], dp[s-w[i]] + c[i]);
                }
            }
            dp = next;
        }
        std::cout << (dp[SMAX] == 0 ? -1 : dp[SMAX]) << std::endl;
    }
    return 0;
}