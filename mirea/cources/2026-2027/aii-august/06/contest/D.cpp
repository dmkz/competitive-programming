#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> x(n), y(n);
    for (auto &it : x) cin >> it;
    for (auto &it : y) cin >> it;
    // переберём точку, в которую встанем: для неё ответом является количество уникальных
    // направляющих векторов из неё до других точек множества.
    const int inf = (int)1e9;
    auto answ = make_pair(inf, -1);
    for (int i = 0; i < n; i++) {
        set<pair<int,int>> vectors;
        for (int j = 0; j < n; j++)
            if (i != j) {
                // Вектор из точки (x[i], y[i]) в точку (x[j], y[j]):
                int dx = x[j] - x[i], dy = y[j] - y[i];
                // Нормализуем, сокращая на gcd:
                int g = gcd(abs(dx), abs(dy));
                dx /= g;
                dy /= g;
                // Вставляем в set:
                vectors.insert({dx, dy});
            }
        answ = min(answ, make_pair((int)vectors.size(), i+1));
    }
    // выводим ответ:
    auto [count, index] = answ;
    cout << index << ' ' << count << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
