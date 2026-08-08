#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды и строку доступности клеток.
    int n; cin >> n;
    vector<ll> a(n);
    for (auto& it : a)
        cin >> it;
    string cells; cin >> cells;
    const ll inf = 1LL << 60;
    vector<ll> dp(n, -inf);
    // В первой клетке маршрут состоит только из неё самой.
    if (cells[0] == '.') dp[0] = a[0];
    for (int i = 1; i < n; i++) {
        if (cells[i] == '.') {
            // Последний прыжок мог быть только из одной из двух предыдущих клеток.
            ll best = dp[i - 1];
            if (i >= 2) best = max(best, dp[i - 2]);
            if (best != -inf) dp[i] = best + a[i];
        }
    }
    if (dp[n - 1] == -inf) cout << -1 << '\n';
    else cout << dp[n - 1] << '\n';
}