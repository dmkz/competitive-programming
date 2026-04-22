#include <bits/stdc++.h>
using namespace std;
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int n; cin >> n;
    vector<int64_t> a(n);
    for (int i = 0, ai; i < n; i++) {
        cin >> ai;
        a[i] = ai;
    }

    const int gsize = (int)sqrt(n/2.0);
    const int nGroups = (n+gsize-1)/gsize;
    vector<int64_t> g(nGroups, 0);

    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == 'a') {
            // прибавить на отрезке
            int l, r, x; cin >> l >> r >> x;
            l--, r--;
            int gl = l / gsize, gr = r / gsize;
            if (gl == gr) {
                for (int i = l; i <= r; i++)
                    a[i] += x;
            } else {
                // левая группа:
                for (int i = l; i <= (gl+1) * gsize - 1; i++)
                    a[i] += x;
                // группы между ними
                for (int gi = gl + 1; gi < gr; gi++)
                    g[gi] += x;
                // правая группа
                for (int i = gr * gsize; i <= r; i++)
                    a[i] += x;
            }
        } else {
            assert(c == 'g');
            int i; cin >> i;
            i--;
            cout << (a[i] + g[i / gsize]) << '\n';
        }
    }
}
