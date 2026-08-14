// На ступеньку i мы можем попасть только из ступенек от left[i] до right[i]. Значит, формула
// перехода суммирует независимые способы добраться до них:
// dp[i] = dp[l] + dp[l+1] + ... + dp[r].
// Чтобы вычислять сумму быстро, нам нужно хранить префиксные суммы поверх ответов динамики.
// Теперь считаем dp[i] = pref[r+1] - pref[l], а затем обновляем префиксные суммы вот так:
// pref[i+1] = dp[i] + pref[i]. Работаем с остатками по простому модулю 10^9+7.
#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9+7;
void solve() {
    // читаем данные:
    int n; cin >> n;
    string s; cin >> s;
    vector<int> left(n), right(n);
    for (int i = 1; i < n; i++)
        cin >> left[i], left[i]--;
    for (int i = 1; i < n; i++)
        cin >> right[i], right[i]--;
    // считаем динамику и префиксные суммы для неё:
    vector<int> dp(n, 0), pref(n+1);
    dp[0] = 1, pref[1] = 1;
    for (int i = 1; i < n; i++) {
        // количество способов - сумма на отрезке [l, r]:
        if (s[i] == '.')
            dp[i] = (pref[right[i]+1] - pref[left[i]] + mod) % mod;
        // обновляем префиксные суммы:
        pref[i+1] = (pref[i] + dp[i]) % mod;
    }
    cout << dp.back() << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
