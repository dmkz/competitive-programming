#include <bits/stdc++.h>
struct DSU {
    
    std::vector<int> sz, par;
    
    DSU(int n)
        : sz(n+1, 1)
        , par(n+1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    int getPar(int u) {
        return (u == par[u] ? u : par[u] = getPar(par[u]));
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        // присоединять "v" к "u"
        sz[u] += sz[v];
        par[v] = u;
    }
    
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n); // 1-индексакция
    while (q --> 0) {
        std::string s; std::cin >> s;
        int u, v; std::cin >> u >> v;
        if (s[0] == 'u') {
            dsu.connect(u, v);
        } else {
            assert(s[0] == 'g');
            bool ok = dsu.isConnected(u, v);
            std::cout << (ok ? "YES\n" : "NO\n");
        }
    }
}
