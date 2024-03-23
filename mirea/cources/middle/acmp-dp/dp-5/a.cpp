#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем поле:
    int n, k; cin >> n >> k;
    vector a(1+n+1, string(1+n+1, '1'));
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= n; c++)
            cin >> a[r][c];
    // считаем динамику:
    // dp[k][r][c] = число способов попасть в клетку (r,c) за k шагов
    vector dp(k+1, vector(1+n+1, vector(1+n+1, 0LL)));
    dp[0][1][1] = 1;
    for (int steps = 1; steps <= k; steps++)
        for (int r = 1; r <= n; r++)
            for (int c = 1; c <= n; c++)
                if (a[r][c] == '0')
                    dp[steps][r][c] = dp[steps-1][r-1][c]
                                    + dp[steps-1][r+1][c]
                                    + dp[steps-1][r][c-1]
                                    + dp[steps-1][r][c+1];
    // выводим ответ:
    cout << dp[k][n][n] << endl;
}
