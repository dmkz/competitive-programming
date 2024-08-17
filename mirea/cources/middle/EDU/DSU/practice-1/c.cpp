#include <bits/stdc++.h>
using vi = std::vector<int>;
struct DSU {
    
    vi sz, par, value;
    
    DSU(int n) : sz(n+1, 1), par(n+1), value(n+1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    int getPar(int u) const {
        return (par[u] == u ? u : getPar(par[u]));
    }
    
    int getVal(int u) const {
        int result = value[u];
        if (par[u] != u)
            result += getVal(par[u]);
        return result;
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
        value[v] -= value[u]; // самый важный момент
    }
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    DSU dsu(n);
    while (q --> 0) {
        std::string t;
        int x;
        std::cin >> t >> x;
        if (t == "join") {
            int y; std::cin >> y;
            dsu.connect(x, y);
        } else if (t == "add") {
            int v; std::cin >> v;
            x = dsu.getPar(x);
            dsu.value[x] += v;
        } else {
            assert("get" == t);
            std::cout << dsu.getVal(x) << "\n";
        }
    }
}
