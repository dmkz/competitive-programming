// теория вероятностей, динамическое программирование, СЛАУ
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m; cin >> n >> m;
    m--;
    vector dp(n+1, vector<ld>(n, 0));
    dp[1][0] = 1;
    for (int k = 2; k <= n; k++) {
        // Уравнение для pos = 0:
        // dp[k][0] = 1.0L/6 + 3.0L/6 * dp[k][k-1];
        // Уравнения для pos > 0:
        // for (int pos = 1; pos < k; pos++)
        //     dp[k][pos] = 3.0L/6 * dp[k][pos-1] + 2.0L/6 * dp[k-1][pos-1];
        // Циклическая зависимость!
        // dp[0] = a[0] * dp[k-1] + b[0]
        // dp[i] = a[i] * dp[i-1] + b[i], 0 < i < k
        vector<ld> a(k), b(k);
        a[0] = 3.0L / 6;
        b[0] = 1.0L / 6;
        for (int i = 1; i < k; i++)
            a[i] = 3.0L / 6, b[i] = 2.0L/6 * dp[k-1][i-1];
        // Надо решить систему:
        // dp[0] = a[0] * dp[k-1] + b[0]
        // dp[1] = a[1] * dp[0] + b[1]
        // dp[2] = a[2] * dp[1] + b[2]
        // ...
        // dp[k-1] = a[k-1] * dp[k-2] + b[k-1]
        // Всё выразим через dp[k-1] сверху-вниз:
        for (int i = 1; i < k; i++) {
            b[i] += a[i] * b[i-1];
            a[i] *= a[i-1];
        }
        // Теперь найдём dp[k-1]:
        // dp[k-1] = a[k-1] * dp[k-1] + b[k-1]
        dp[k][k-1] = b[k-1] / (1.0L - a[k-1]);
        // Затем найдём все dp[i]:
        for (int i = k-2; i >= 0; i--)
            dp[k][i] = a[i] * dp[k][k-1] + b[i];
    }
    cout << fixed << setprecision(12);
    cout << dp[n][m] << endl;
}
