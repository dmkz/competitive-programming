// перестановки, двоичные прыжки, O(n * log(k))
#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) {
        int n; int64_t k;
        cin >> n >> k;
        vector<int> perm(n);
        for (int i = 0; i < n; i++)
            cin >> perm[i], perm[i]--;
        // посчитаем next[p][x] = где окажется элемент x через 2^p шагов
        vector<int> next[60]{};
        next[0] = perm;
        for (int p = 1; p < 60; p++) {
            next[p].resize(n);
            for (int i = 0; i < n; i++)
                // чтобы сделать 2^p шагов:
                // 1) сначала делаем 2^(p-1) шагов -> предподсчитано
                // 2) затем ещё делаем 2^(p-1) шагов -> тоже предподсчитано
                next[p][i] = next[p-1][next[p-1][i]];
        }
        // находим, где окажется каждый элемент через k шагов, раскладывая
        // k в сумму степеней двоек:
        for (int i = 0; i < n; i++) {
            int curr = i;
            for (int bit = 59; bit >= 0; bit--)
                if ((k >> bit) & 1)
                    curr = next[bit][curr];
            cout << (curr+1) << ' ';
        }
        cout << '\n';
    }
}
