// Для каждого x[j] нужно найти минимальный i такой, что x[j] < a[1] + a[2] + ... + a[i].
// Этот номер i будет равен первой доске, которую мы не сможем пробить. Чтобы быстро искать
// данный индекс, построим вектор префиксных-сумм и сделаем бинарный поиск в нём.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив:
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // считаем префиксные суммы:
    vector<int64_t> s = {0};
    for (auto it : a)
        s.push_back(s.back() + it);
    // отвечаем на запросы: для заданного x нужно найти ближайший s[i] > x
    // используем для этого бинарный поиск (upper_bound)
    while (q --> 0) {
        int64_t x; cin >> x;
        cout << int(upper_bound(s.begin(), s.end(), x) - s.begin() - 1) << ' ';
    }
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
