#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using ll = long long;
const ll inf = (ll)1e18L;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void solve() {
    int n, m; cin >> n >> m;
    vector a(max(n,m), vector(2, 0));
    if (n <= m) {
        assert(n == 2);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                cin >> a[c][r];
    } else {
        assert(m == 2);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < m; c++)
                cin >> a[r][c];
    }
    n = max(n, m);
    vector dp(n, vector(2, -inf));
    dp[0][0] = a[0][0];
    dp[0][1] = a[0][0] + a[0][1];
    for (int i = 1; i < n; i++) {
        // переход в клетку (i, 0):
        setmax(dp[i][0], dp[i-1][0] + a[i][0]);
        setmax(dp[i][0], dp[i-1][1] + a[i][0] + a[i][1]);
        // переход в клетку (i, 1):
        setmax(dp[i][1], dp[i-1][1] + a[i][1]);
        setmax(dp[i][1], dp[i-1][0] + a[i][0] + a[i][1]);
    }
    cout << dp[n-1][1] << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
