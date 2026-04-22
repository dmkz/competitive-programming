#include <bits/stdc++.h>
using namespace std;
int myGCD(int a, int b) {
    if (b == 0) return a;
    if (a < b) return myGCD(b, a);
    return myGCD(b, a % b);
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
    vector<int> g(nGroups, 0);
    for (int i = 0; i < n; i++) {
        int gi = i / gsize;
        g[gi] = myGCD(g[gi], a[i]);
    }
    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        char c; cin >> c;
        if (c == 'g') {
            // найти НОД
            int l, r; cin >> l >> r;
            l--, r--;
            int gl = l / gsize, gr = r / gsize;
            int answ = 0;
            if (gl == gr) {
                for (int i = l; i <= r; i++)
                    answ = myGCD(answ, a[i]);
            } else {
                // левая группа:
                for (int i = l; i <= (gl+1) * gsize - 1; i++)
                    answ = myGCD(answ, a[i]);
                // группы между ними
                for (int gi = gl + 1; gi < gr; gi++)
                    answ = myGCD(answ, g[gi]);
                // правая группа
                for (int i = gr * gsize; i <= r; i++)
                    answ = myGCD(answ, a[i]);
            }
            cout << answ << '\n';
        } else {
            assert(c == 'u');
            int i, x; cin >> i >> x;
            i--;
            a[i] = x;
            // с нуля пересчитывать НОД в этой группе
            int gi = i / gsize;
            g[gi] = x;
            for (int j = gi * gsize; j < min(n, (gi + 1) * gsize); j++)
                g[gi] = myGCD(g[gi], a[j]);
        }
    }
}
