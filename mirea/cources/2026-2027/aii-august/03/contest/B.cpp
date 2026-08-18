#include <bits/stdc++.h>
#include <cassert>
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
const ll inf = 1LL << 60;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a)
        cin >> it;
    // считаем динамику: dp[i][k] -> максимальная сумма, с которой мы пришли в i-ю ступеньку,
    // где текущая серия взятых положительных чисел равна k.
    vector dp(n, vector(3, -inf));
    // инициализация динамики:
    if (a[0] < 0)
        dp[0][0] = a[0];
    else {
        assert(a[0] > 0);
        dp[0][1] = a[0];
    }
    for (int i = 1; i < n; i++)
        if (a[i] < 0) // отрицательное число прерывает серию
            for (int k = 0; k <= 2; k++) {
                // прыжок на 1:
                if (i-1 >= 0) setmax(dp[i][0], a[i] + dp[i-1][k]);
                // прежок на 2:
                if (i-2 >= 0) setmax(dp[i][0], a[i] + dp[i-2][k]);
            }
        else if (a[i] > 0) // положительное число продолжает серию
            for (int k = 1; k <= 2; k++) {
                // прыжок на 1:
                if (i-1 >= 0) setmax(dp[i][k], a[i] + dp[i-1][k-1]);
                // прыжок на 2:
                if (i-2 >= 0) setmax(dp[i][k], a[i] + dp[i-2][k-1]);
            }
    // выводим ответ:
    ll answ = *max_element(dp[n-1].begin(), dp[n-1].end());
    const ll minPossibleAnswer = n * ll(*min_element(all(a)));
    if (answ < minPossibleAnswer) cout << "0\n";
    else cout << "1 " << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
