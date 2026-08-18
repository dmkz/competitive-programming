#include <bits/stdc++.h>
using namespace std;
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
void setmax(auto &x, const auto &y) { if (y > x) x = y; }
using ll = long long;
const ll inf = 1LL << 60;
void solve() {
    // читаем входные данные:
    int n, q; cin >> n >> q;
    vector<int> w(n), v(n), x(q);
    for (auto &it : w) cin >> it;
    for (auto &it : v) cin >> it;
    for (auto &it : x) cin >> it;
    // считаем максимальную сумму:
    const int S = *max_element(x.begin(), x.end());
    // строим два рюкзака:
    // dpMin[n][s] = минимальный суммарный вес для набора стоимостью s
    // dpMax[n][s] = максимальный суммарный вес для набора стоимостью s
    vector dpMin(n+1, vector(S+1, +inf));
    vector dpMax(n+1, vector(S+1, -inf));
    // инициализация:
    dpMin[0][0] = 0;
    dpMax[0][0] = 0;
    // считаем переходы:
    for (int i = 0; i < n; i++) {
        // копируем предыдущий слой - здесь мы не берём i-й предмет:
        dpMin[i+1] = dpMin[i];
        dpMax[i+1] = dpMax[i];
        // обновляем варианты, если i-й предмет выбран:
        for (int s = v[i]; s <= S; s++) {
            // Сейчас стоимость s, взяли предмет (v[i], w[i]), значит до этого
            // стоимость была s - v[i], и нам нужен мин и макс вес для предыдущего рюкзака
            setmin(dpMin[i+1][s], w[i] + dpMin[i][s-v[i]]);
            setmax(dpMax[i+1][s], w[i] + dpMax[i][s-v[i]]);
        }
    }
    // отвечаем на запросы:
    for (int i = 0; i < q; i++)
        if (dpMin[n][x[i]] >= +inf)
            cout << "-1\n";
        else
            cout << dpMin[n][x[i]] << ' ' << dpMax[n][x[i]] << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
