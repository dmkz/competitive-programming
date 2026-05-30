#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // чтение:
    int n, q; cin >> n >> q;
    vector<vector<int>> t(30, vector<int>(n));
    for (int i = 0; i < n; i++) {
        cin >> t[0][i];
        t[0][i]--;
    }
    // строим таблицу двоичных прыжков:
    for (int k = 1; k < 30; k++)
        for (int i = 0; i < n; i++) {
            int mid = t[k-1][i];
            t[k][i] = t[k-1][mid];
        }
    // ответим на запросы:
    while (q --> 0) {
        int x, k; cin >> x >> k;
        x--;
        bitset<30> bs(k);
        for (int i = 0; i < 30; i++)
            if (bs[i])
                x = t[i][x];
        cout << x+1 << '\n';
    }
}