#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем изначальные количества монет:
    vector<ll> c(6);
    for (auto &it : c) cin >> it;
    const vector<ll> d = {1,2,5,10,20,50};
    // читаем и отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        // читаем i-й запрос:
        int p; vector<ll> u(6);
        cin >> p;
        for (auto &it : u) cin >> it;
        // считаем сумму. если суммы не хватает, то покупатель сразу уходит:
        ll s = 0;
        for (int i = 0; i < 6; i++)
            s += d[i] * u[i];
        if (s < p) {
            cout << "REFUSED\n";
            continue;
        }
        // сначала монеты попадают в автомат:
        vector<ll> saved = c;
        for (int i = 0; i < 6; i++)
            c[i] += u[i];
        // теперь мы должны выдать сдачу:
        ll r = s - p;
        vector<ll> answ(6);
        for (int i = 5; i >= 0; i--) {
            // выдаём максимальное количество монет, которое можем:
            ll cntI = std::min(c[i], r / d[i]);
            r -= d[i] * cntI;
            c[i] -= cntI;
            answ[i] = cntI;
        }
        if (r != 0) {
            // не получилось -> откатываем:
            c = saved;
            cout << "REFUSED\n";
            continue;
        }
        // тут всё получилось, выводим ответ:
        for (auto it : answ)
            cout << it << ' ';
        cout << '\n';
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; // cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
