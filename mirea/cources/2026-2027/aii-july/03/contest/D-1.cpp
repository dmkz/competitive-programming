#include <bits/stdc++.h>
using namespace std;
void solve() {
    set<int> s = {-1000000000, 1000000000};
    int q; cin >> q;
    while (q --> 0) {
        // читаем + вставляем + запоминаем итератор на вставленный элемент:
        int x; cin >> x;
        auto [iter, wasInserted] = s.insert(x);
        if (!wasInserted) // данный x уже есть
            cout << "0\n";
        else // расстояние до ближайшего - это минимум из расстояний до соседей:
            cout << min(*iter - *prev(iter), *next(iter) - *iter) << '\n';
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
