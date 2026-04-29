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
    
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    const int gsize = max(1, (int)sqrt(n/2.0));
    const int nGroups = (n+gsize-1)/gsize;
    vector<int> g(nGroups, -inf);
    for (int i = 0; i < n; i++)
        setmax(g[i / gsize], a[i]);

    // отвечаем на запросы:
    while (q --> 0) {
        int t; cin >> t;
        if (t == 2) {
            int x, l; cin >> x >> l;
            int answ = -1;
            // проверить элементы внутри блока для l
            int gl = l / gsize;
            const int gEnd = min((gl + 1) * gsize, n);
            for (int i = l; i < gEnd; i++)
                if (a[i] >= x) {
                    answ = i;
                    break;
                }
            if (answ == -1)
                for (int gi = gl+1; gi < nGroups; gi++)
                    if (g[gi] >= x) {
                        // нашли группу
                        for (int j = gi * gsize; j < min((gi+1)*gsize, n); j++)
                            if (a[j] >= x) {
                                answ = j;
                                break;
                            }
                        break;
                    }
            cout << answ << '\n';
        } else {
            assert(t == 1);
            int i, x; cin >> i >> x;
            int gi = i / gsize;
            a[i] = x;
            // пересчитаем всю группу заново
            g[gi] = -inf;
            for (int j = gi * gsize; j < min(n, (gi + 1) * gsize); j++)
                setmax(g[gi], a[j]);
        }
    }
}
