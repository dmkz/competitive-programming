#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем данные
    int n, m; cin >> n >> m;
    vector a(n+1, vector(m+1, '.'));
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            cin >> a[r][c];
    // считаем динамику
    // dp[r][c] = кол-во путей из (1, 1) в (r, c)
    vector dp(n+1, vector(m+1, 0));
    for (int r = 1; r <= n; r++)
        for (int c = 1; c <= m; c++)
            if (r == 1 && c == 1)
                dp[1][1] = 1; // инициализация
            else if (a[r][c] == '.') // если клетка проходимая
                // переходы из (r-1,c) или из (r, c-1)
                dp[r][c] = (dp[r-1][c] + dp[r][c-1]) % mod;
    // выводим ответ:
    cout << dp[n][m] << endl;
}
