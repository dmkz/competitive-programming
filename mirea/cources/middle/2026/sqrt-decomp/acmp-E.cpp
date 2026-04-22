#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int inf = (int)1e9+7;
// {значение; индекс}
void update(pii &curr, const pii &next) {
    if (curr.first < next.first)
        curr = next;
    else if (curr.first == next.first)
        curr.second = min(curr.second, next.second);
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
    vector<pii> g(nGroups, {-inf, -inf});
    for (int i = 0; i < n; i++)
        update(g[i / gsize], pii(a[i], i));

    // отвечаем на запросы:
    int q; cin >> q;
    while (q --> 0) {
        //char c; cin >> c;
        int l, r; cin >> l >> r;
        l--, r--;
        int gl = l / gsize, gr = r / gsize;
        pii answ = {-inf, -inf};
        if (gl == gr) {
            for (int i = l; i <= r; i++)
                update(answ, pii(a[i], i));
        } else {
            // левая группа:
            for (int i = l; i <= (gl+1) * gsize - 1; i++)
                update(answ, pii(a[i], i));
            // группы между ними
            for (int gi = gl + 1; gi < gr; gi++)
                update(answ, g[gi]);
            // правая группа
            for (int i = gr * gsize; i <= r; i++)
                update(answ, pii(a[i], i));
        }
        cout << answ.first << ' ' << answ.second + 1 << '\n';
    }
}
