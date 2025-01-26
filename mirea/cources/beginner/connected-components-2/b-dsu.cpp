#include <bits/stdc++.h>
using namespace std;
struct DSU {
    std::vector<int> par, sz;
    DSU(int n) : par(n+1, 0), sz(n+1, 1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    int getPar(int u) {
        return par[u] == u ? u : par[u] = getPar(par[u]);
    }
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v) return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
    }
    int getSize(int u) {
        return sz[getPar(u)];
    }
};
void solve() {
    int nUsers, nGroups;
    cin >> nUsers >> nGroups;
    DSU dsu(nUsers);
    while (nGroups --> 0) {
        // мы прочитаем элементы группы g[0], g[1], g[2], ..., g[k-1]
        // и соединим рёбрами соседей: g[0]<-->g[1]<-->g[2]<-->...<-->g[k-1]
        int groupSize; cin >> groupSize;
        vector<int> group(groupSize);
        for (int i = 0; i < groupSize; i++) {
            cin >> group[i];
            if (i-1 >= 0) {
                int u = group[i-1], v = group[i];
                dsu.connect(u, v);
            }
        }
    }
    for (int i = 1; i <= nUsers; i++)
        cout << dsu.getSize(i) << ' ';
    cout << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0)
        solve();
}

