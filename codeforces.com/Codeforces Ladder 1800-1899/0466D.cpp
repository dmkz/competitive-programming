/*
    Problem: 466D. Increase Sequence
    Solution: dynamic programming, combinatorics, O(n^2)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int mod = (int)1e9+7;
int& addto(int &a, int b) { return (a += b) >= mod ? a -= mod : a; }
int mul(int a, int b) { return int(1LL * a * b % mod); }
int main() {
    for (int n, h; std::cin >> n >> h; ) {
        std::vector<int> arr(1+n+1,h);
        for (int i = 1; i <= n; i++) {
            std::cin >> arr[i];
        }
        n += 1;
        vvi dp(n+10, vi(n+10, 0));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            const int need = h - arr[i];
            // ..
            need >= 0 && addto(dp[i][need], dp[i-1][need]);
            // [.
            need >= 1 && addto(dp[i][need], dp[i-1][need-1]);
            // .]
            need >= 1 && addto(dp[i][need-1], mul(need, dp[i-1][need]));
            // []
            need >= 1 && addto(dp[i][need-1], mul(need, dp[i-1][need-1]));
        }
        std::cout << dp[n][0] << std::endl;
    }
    return 0;
}