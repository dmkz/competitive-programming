#include <bits/stdc++.h>
#include <cassert>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
const ll inf = 1LL << 60;
void setmin(auto &x, const auto &y) { if (x > y) x = y; }
void solve() {
    // читаем данные:
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // сортируем участников по возрастанию их результатов:
    sort(all(a));
    // делим участников на группы
    vector dp(1+n, vector(k+1, +inf));
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        for (int sz = 2; sz <= 4; sz++) {
            int j = i - sz + 1;
            if (j < 0) continue;
            // группа [j, i] стоимостью a[i] - a[j]
            for (int wasGroups = 0; wasGroups < k; wasGroups++)                
                setmin(dp[i+1][wasGroups+1], dp[j][wasGroups] + a[i] - a[j]);
        }
    }
    // выводим ответ:
    cout << dp[n][k] << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
