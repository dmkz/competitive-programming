#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем элементы и запоминаем их позиции в map:
    int n, q; cin >> n >> q;
    map<int, int> firstPos, lastPos;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        // ищем последнюю позицию
        auto iter = lastPos.find(x);
        if (iter == lastPos.end()) {
            // не найдена - элемент ещё не встречался
            firstPos[x] = i;
            lastPos[x] = i;
        } else {
            // найдена - меняем только последнюю позицию
            iter->second = i;
        }
    }
    // читаем и отвечаем на запросы:
    while (q --> 0) {
        int x; cin >> x;
        auto iter = lastPos.find(x);
        if (iter == lastPos.end())
            cout << "-1\n";
        else // найден:
            cout << firstPos[x] << ' ' << iter->second << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
