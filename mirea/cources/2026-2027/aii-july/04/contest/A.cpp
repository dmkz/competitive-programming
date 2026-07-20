// Построим префиксные суммы отдельно для чётных и отдельно для нечётных чисел,
// а затем ответим на запросы.
#include <bits/stdc++.h>
using namespace std;
void solve() {
    // читаем массив
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    // строим префиксные суммы: отдельно для чётных и отдельно для нечётных чисел
    vector<int64_t> s0(n+1, 0), s1(n+1, 0);
    for (int i = 0; i < n; i++) {
        s0[i+1] = s0[i], s1[i+1] = s1[i];
        if (a[i] % 2 == 0) s0[i+1] += a[i];
        else s1[i+1] += a[i];
    }
    // отвечаем на запросы:
    while (q --> 0) {
        int l, r;
        cin >> l >> r;
        cout << (s0[r] - s0[l-1]) << " " << (s1[r] - s1[l-1]) << '\n';
    }
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
