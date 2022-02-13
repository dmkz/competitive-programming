#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
int main() {
    freopen("knight.in", "rt", stdin);
    freopen("knight.out", "wt", stdout);
    // читаем размер поля:
    int n, m; cin >> n >> m;
    // считаем динамику:
    vvl dp(n, vl(m, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i - 2 >= 0 && j - 1 >= 0)
                dp[i][j] += dp[i-2][j-1];
            if (i - 1 >= 0 && j - 2 >= 0)
                dp[i][j] += dp[i-1][j-2];
        }
    }
    cout << dp.back().back() << endl;
}