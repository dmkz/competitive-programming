#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение:
    int n, q; cin >> n >> q;
    vvi t(30, vi(n+1));
    for (int i = 1; i <= n; i++)
        cin >> t[0][i];
    // строим таблицу двоичных прыжков:
    for (int k = 1; k < 30; k++)
        for (int i = 1; i <= n; i++)
            t[k][i] = t[k-1][t[k-1][i]];
    // ответим на запросы:
    while (q --> 0) {
        int x, k; cin >> x >> k;
        for (int i = 0; i < 30; i++)
            if ((k >> i) & 1)
                x = t[i][x];
        cout << x << '\n';
    }
}