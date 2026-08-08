#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем награды ступеней:
    int n; cin >> n;
    vector<ll> a(n + 1), dp(n + 1);
    vector<bool> ready(n + 1, false);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    function<ll(int)> solve = [&](int i) {
        if (i == 0) return 0LL;
        if (ready[i]) return dp[i];
        // Кэшируем лучший результат после рекурсивного вычисления предшественников.
        dp[i] = a[i] + solve(i - 1);
        if (i >= 2) dp[i] = max(dp[i], a[i] + solve(i - 2));
        ready[i] = true;
        return dp[i];
    };
    cout << solve(n) << '\n';
}