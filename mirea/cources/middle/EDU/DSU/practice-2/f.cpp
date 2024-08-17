#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void setmin(auto &x, const auto &y) { if (x > y) x = y; }

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
    // перебираем минимальное ребро и начиная от него
    // соединяем всеми рёбрами пока не получим что все
    // вершины соединены
    int answ = INT_MAX;
    for (int i = 0; i < isz(edges); i++) {
        DSU dsu(n);
        const int minEdge = std::get<0>(edges[i]);
        int maxEdge = minEdge;
        int j = i;
        while (j < isz(edges) && dsu.getSize(1) < n) {
            auto [currEdge, u, v] = edges[j++];
            dsu.connect(u, v);
            setmax(maxEdge, currEdge);
        }
        if (dsu.getSize(1) == n)
            setmin(answ, maxEdge - minEdge);
    }
    if (answ == INT_MAX) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
        std::cout << answ << "\n";
    }
}
