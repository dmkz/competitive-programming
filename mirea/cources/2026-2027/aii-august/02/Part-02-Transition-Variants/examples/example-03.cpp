#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // Читаем конечную точку:
    int n; cin >> n;
    const int mod = 1000000007;
    // dp[i] — число последовательностей прыжков на 1 и 2 в точку i.
    vector<int> dp(n + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1];
        if (i >= 2) dp[i] = (dp[i] + dp[i - 2]) % mod;
    }
    // Выводим количество маршрутов в конечную точку.
    cout << dp[n] << '\n';
}