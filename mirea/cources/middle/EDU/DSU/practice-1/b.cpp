#include <bits/stdc++.h>
struct DSU {
    
    std::vector<int> sz, par, min, max;
    
    DSU(int n)
        : sz(n+1, 1)
        , par(n+1)
        , min(n+1)
        , max(n+1)
    {
        for (int i = 1; i <= n; i++)
            min[i] = max[i] = par[i] = i;
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
        min[u] = std::min(min[u], min[v]);
        max[u] = std::max(max[u], max[v]);
    }
    
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n); // 1-индексакция
    while (q --> 0) {
        std::string s; std::cin >> s;
        int u, v;
        if (s[0] == 'u') {
            std::cin >> u >> v;
            dsu.connect(u, v);
        } else {
            assert(s[0] == 'g');
            std::cin >> u;
            u = dsu.getPar(u);
            int min = dsu.min[u];
            int max = dsu.max[u];
            int sz = dsu.sz[u];
            std::cout << min << ' ' << max << ' ' << sz << '\n';
        }
    }
}
