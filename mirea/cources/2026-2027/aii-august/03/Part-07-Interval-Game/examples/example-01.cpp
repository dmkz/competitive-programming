#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Считываем числа, лежащие на столе:
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& it : a)
        cin >> it;
    // dp[i][j] хранит наибольшую разность для игрока, который ходит на отрезке [i, j].
    vector<vector<ll>> dp(n, vector<ll>(n));
    // На отрезке из одного числа текущий игрок забирает это число целиком.
    for (int i = 0; i < n; i++)
        dp[i][i] = a[i];
    // Перебираем длины по возрастанию, чтобы меньшие отрезки уже были обработаны.
    for (int length = 2; length <= n; length++) {
        for (int i = 0; i + length <= n; i++) {
            // Правая граница определяется левой границей и длиной отрезка.
            int j = i + length - 1;
            // После выбора ход переходит к сопернику, который играет на меньшем отрезке.
            dp[i][j] = max(a[i] - dp[i + 1][j], a[j] - dp[i][j - 1]);
        }
    }
    cout << dp[0][n - 1] << '\n';
}