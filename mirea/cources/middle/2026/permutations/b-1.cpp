#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;

void solve() {
    // читаем:
    int n; int64_t k;
    cin >> n >> k;
    vector p(60, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        cin >> p[0][i];
        p[0][i]--;
    }
    // считаем переходы по степеням двоек:
    for (int j = 1; j < 60; j++)
        for (int i = 0; i < n; i++)
            // где мы окажемся, сделав 2^j ходов из элемента i:
            // сначала сделаем 2^(j-1) ходов, затем ещё столько же
            p[j][i] = p[j-1][p[j-1][i]];
    // находим ответ:
    for (int i = 0; i < n; i++) {
        int currPos = i;
        int64_t steps = k;
        for (int j = 59; j >= 0; j--) {
            int64_t powJ = (1LL << j);
            if (steps >= powJ) {
                currPos = p[j][currPos];
                steps -= powJ;
            }
        }
        cout << currPos + 1 << ' ';
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
