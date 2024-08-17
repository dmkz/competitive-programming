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
        sz[u] += sz[v];
        par[v] = u;
    }
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m, q;
    std::cin >> n >> m >> q;
    // читаем бесполезные ребра
    int ignored;
    for (int i = 0; i < m; i++)
        std::cin >> ignored >> ignored;
    // читаем запросы
    std::vector<std::tuple<std::string,int,int>> queries(q);
    for (auto &[t, fi, se] : queries)
        std::cin >> t >> fi >> se;
    // отвечаем на запросы в обратном порядке
    std::reverse(all(queries));
    DSU dsu(n);
    std::vector<std::string> answ;
    for (const auto &[t, fi, se] : queries) {
        if (t == "ask") {
            answ.push_back((dsu.isConnected(fi,se) ? "YES" : "NO"));
        } else {
            assert(t == "cut");
            dsu.connect(fi, se);
        }
    }
    // выводим ответы
    std::reverse(all(answ));
    for (auto &it : answ)
        std::cout << it << '\n';
}
