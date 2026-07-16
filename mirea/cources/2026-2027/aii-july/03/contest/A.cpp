#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем элементы и добавляем их в set:
    int n; cin >> n;
    set<int> s;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }
    // вывод уникальных элементов на экран:
    for (auto item : s)
        cout << item << ' ';
    cout << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
