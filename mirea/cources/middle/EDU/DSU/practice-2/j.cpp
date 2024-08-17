#include <bits/stdc++.h>
using vi = std::vector<int>;

struct DSU {
    vi sz, par;
    
    DSU(int n) : sz(n, 1), par(n)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    
    int getPar(int u) {
        return (par[u] == u ? u : par[u] = getPar(par[u])); 
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
    }
   
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    DSU dsu(2 * n); // каждую вершину дублируем
    int answ = -1;
    for (int i = 1; i <= m; i++) {
        int u, v; std::cin >> u >> v;
        // переходим в 0-индексацию:
        u--, v--;
        // соединяем (u, 0) с (v, 1)
        dsu.connect((u << 1) | 0, (v << 1) | 1);
        // соединяем (u, 1) с (v, 0)
        dsu.connect((u << 1) | 1, (v << 1) | 0);
        // если (u, 0) находится в одной компоненте с (u, 1)
        // тогда двудольность ломается
        if (dsu.isConnected((u << 1) | 0, (u << 1) | 1)) {
            answ = i;
            break;
        }
    }
    std::cout << answ << "\n";
}
