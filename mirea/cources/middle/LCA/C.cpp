#include <bits/stdc++.h>
using namespace std;
const int NMAX = 500500, PMAX = 20;
int par[PMAX][NMAX], dep[NMAX];
void add(int u, int p) {
    par[0][u] = p;
    dep[u] = dep[p]+1;
    for (int p = 1; p < PMAX; p++)
        par[p][u] = par[p-1][par[p-1][u]];
}
int up(int u, int delta) {
    for (int bit = PMAX-1; bit >= 0; bit--)
        if ((delta >> bit) & 1)
            u = par[bit][u];
    return u;
}
int get(int u, int v) {
    // пусть u будет ниже, чем v
    if (dep[u] < dep[v])
        swap(u,v);
    // поднимаем u на уровень v
    u = up(u, dep[u] - dep[v]);
    // делаем двоичный поиск
    for (int bit = PMAX-1; bit >= 0; bit--) {
        int pu = par[bit][u];
        int pv = par[bit][v];
        if (pu != pv)
            u = pu, v = pv;
    }
    // возвращаем ответ
    return u == v ? u : par[0][u];
}
int main() {
    freopen("lca.in", "rt", stdin);
    freopen("lca.out", "wt", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> q;
    while (q --> 0) {
        string s; int u, v;
        cin >> s >> u >> v;
        if (s == "ADD") add(v,u);
        else cout << get(u,v) << '\n';
    }
}
