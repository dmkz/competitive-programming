#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        // если мы возьмём фигуру, симметрично её отобразим,
        // то она должна совпасть с оригинальной фигурой (сделай рисунок)
        // проверим, что она совпадает
        // допустим, что мы симметрично отображаем (i, a[i])
        // это будет прямоугольник на высоте a[i] длины i
        // надо проверить, что префикс длины a[i] имеет высоту >= i
        int n; cin >> n;
        vector<int> a(n);
        vector<int> mn(n);
        for (auto &it : a)
            cin >> it, --it;
        mn[0] = a[0];
        for (int i = 1; i < n; i++)
            mn[i] = min(mn[i-1], a[i]);
        bool ok = 1;
        for (int i = 0; i < n; i++) {
            ok &= (a[i] < n && mn[a[i]] >= i);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
