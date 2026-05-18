#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;

void solve() {
    int n; int64_t k;
    cin >> n >> k;
    vector p(60, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        cin >> p[0][i], p[0][i]--;
    for (int j = 1; j < 60; j++)
        for (int i = 0; i < n; i++)
            p[j][i] = p[j-1][p[j-1][i]];
    for (int i = 0, v, j; i < n; i++) {
        for (j = 59, v = i; j >= 0; j--)
            if ((k >> j) & 1)
                v = p[j][v];
        cout << v + 1 << ' ';
    }
    cout << '\n';
}

main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // решение задачи
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
