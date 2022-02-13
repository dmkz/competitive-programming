#include <bits/stdc++.h>
using namespace std;
const int INF = (int)1e9;
using vi = vector<int>;
using vvi = vector<vi>;
void setmin(auto &x, auto y) { if (y < x) x = y; }
int main() {
    freopen("king2.in", "rt", stdin);
    freopen("king2.out", "wt", stdout);
    const int n = 8, m = 8;
    // читаем поле
    vvi a(n, vi(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
    // считаем динамику:
    vvi dp(n, vi(m, INF));
    dp[n-1][0] = 0;
    for (int i = n-1; i >= 0; i--)
        for (int j = 0; j < m; j++) {
            if (i+1 < n) setmin(dp[i][j], a[i][j]+dp[i+1][j]);
            if (j-1 >= 0) setmin(dp[i][j], a[i][j]+dp[i][j-1]);
            if (i+1 < n && j-1 >= 0)
                setmin(dp[i][j], a[i][j]+dp[i+1][j-1]);
        }
    cout << dp[0].back() << endl;
}