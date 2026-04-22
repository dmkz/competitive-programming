#include <bits/stdc++.h>
using namespace std;
const int inf = (int)1e9+7;
void setmax(auto &x, const auto &y) {
    if (x < y)
        x = y;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    const int gsize = (int)sqrt(n/2.0);
    const int nGroups = (n+gsize-1)/gsize;
    vector<int> g(nGroups, -inf);
    for (int i = 0; i < n; i++)
        setmax(g[i / gsize], a[i]);

    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == 'm') {
            // найти сумму
            int l, r; cin >> l >> r;
            l--, r--;
            int gl = l / gsize, gr = r / gsize;
            int answ = -inf;
            if (gl == gr) {
                for (int i = l; i <= r; i++)
                    setmax(answ, a[i]);
            } else {
                // левая группа:
                for (int i = l; i <= (gl+1) * gsize - 1; i++)
                    setmax(answ, a[i]);
                // группы между ними
                for (int gi = gl + 1; gi < gr; gi++)
                    setmax(answ, g[gi]);
                // правая группа
                for (int i = gr * gsize; i <= r; i++)
                    setmax(answ, a[i]);
            }
            cout << answ << '\n';
        } else {
            assert(c == 'u');
            int i, x; cin >> i >> x;
            i--;
            int gi = i / gsize;
            a[i] = x;
            // пересчитаем всю группу заново
            g[gi] = -inf;
            for (int j = gi * gsize; j < min(n, (gi + 1) * gsize); j++)
                setmax(g[gi], a[j]);
        }
    }
}