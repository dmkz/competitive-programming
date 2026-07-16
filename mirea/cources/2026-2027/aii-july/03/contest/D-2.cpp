#include <bits/stdc++.h>
using namespace std;
void solve() {
    set<int> s = {-1000000000, 1000000000};
    int q; cin >> q;
    while (q --> 0) {
        // читаем икс и ищем соседа слева и справа:
        int x; cin >> x;
        auto rightIter = s.lower_bound(x);
        auto leftIter = prev(rightIter);
        // расстояние до ближайшего - это минимум из расстояний до соседей:
        cout << min(x - *leftIter, *rightIter - x) << '\n';
        // вставляем:
        s.insert(x);
    }
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
