#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем высоты платформ:
    int n; cin >> n;
    vector<ll> h(n);
    for (auto& it : h)
        cin >> it;
    // dp[i] — наименьшая цена, с которой лягушка приходит на i-ю платформу.
    const ll inf = (1LL << 60);
    vector<ll> dp(n, inf);
    dp[0] = 0;
    for (int i = 1; i < n; i++) {
        dp[i] = dp[i - 1] + abs(h[i] - h[i - 1]);
        if (i >= 2)
            dp[i] = min(dp[i], dp[i - 2] + abs(h[i] - h[i - 2]));
    }
    // Последняя ячейка содержит цену пути до последней платформы.
    cout << dp[n - 1] << '\n';
}