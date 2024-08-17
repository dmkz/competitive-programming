#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;

struct DSU {
    vi sz, par;
    
    DSU(int n) : sz(n+1, 1), par(n+1)
    {
        for (int i = 1; i <= n; i++)
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
    
    int getSize(int u) {
        return sz[getPar(u)];
    }
   
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    // читаем рёбра
    std::vector<std::tuple<int,int,int>> edges(m);
    for (auto &[w, u, v] : edges)
        std::cin >> u >> v >> w;
    // сортируем по возрастанию весов
    std::sort(all(edges));
    // запускаем алгоритм поиска минимального остовного дерева:
    DSU dsu(n);
    int answ = 0;
    for (const auto &[w, u, v] : edges) {
        if (dsu.isConnected(u, v))
            continue;
        dsu.connect(u, v);
        if (dsu.getSize(1) == n) {
            answ = w;
            break;
        }
    }
    std::cout << answ << "\n";
}
