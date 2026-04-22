#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    const int gsize = (int)sqrt(n/2.0);
    const int nGroups = (n+gsize-1)/gsize;
    vector<long long> g(nGroups, 0);
    for (int i = 0; i < n; i++)
        g[i / gsize] += a[i];

    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == 's') {
            // найти сумму
            int l, r; cin >> l >> r;
            l--, r--;
            int gl = l / gsize, gr = r / gsize;
            long long answ = 0;
            if (gl == gr) {
                for (int i = l; i <= r; i++)
                    answ += a[i];
            } else {
                // левая группа:
                for (int i = l; i <= (gl+1) * gsize - 1; i++)
                    answ += a[i];
                // группы между ними
                for (int gi = gl + 1; gi < gr; gi++)
                    answ += g[gi];
                // правая группа
                for (int i = gr * gsize; i <= r; i++)
                    answ += a[i];
            }
            cout << answ << '\n';
        } else {
            assert(c == 'u');
            int i, x; cin >> i >> x;
            i--;
            int gi = i / gsize;
            g[gi] += (x - a[i]);
            a[i] += (x - a[i]);
        }
    }
}
