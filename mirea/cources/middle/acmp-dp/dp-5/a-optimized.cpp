#include <bits/stdc++.h>
#define int ll
using namespace std;
using ll = long long;
const int mod = (int)1e9+7;
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем поле:
    int n; ll k; cin >> n >> k;
    vector a(1+n+1, string(1+n+1, '1'));
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++)
            cin >> a[r][c];
    // считаем динамику:
    // dp[k][r][c] = число способов попасть в клетку (r,c) за k шагов
    auto currDp = vector(1+n+1, vector(1+n+1, 0LL));
    currDp[1][1] = 1;
    for (int steps = 1; steps <= k; steps++) {
        auto nextDp = currDp;
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= n; c++)
                if (a[r][c] == '0')
                    nextDp[r][c] = (currDp[r-1][c]
                                    + currDp[r+1][c]
                                    + currDp[r][c-1]
                                    + currDp[r][c+1])%mod;
        swap(currDp, nextDp);
    }
    // выводим ответ:
    cout << currDp[n][n] << endl;
}
