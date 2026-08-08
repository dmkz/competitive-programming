#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды ступеней:
    int n; cin >> n;
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    // dp[i] — наибольшая сумма на маршруте до ступени i.
    vector<ll> dp(n + 1);
    if (n >= 1) dp[1] = a[1];
    for (int i = 2; i <= n; i++)
        dp[i] = a[i] + max(dp[i - 1], dp[i - 2]);
    cout << dp[n] << '\n';
}