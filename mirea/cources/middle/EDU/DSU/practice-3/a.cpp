#include <bits/stdc++.h>
struct DSU {
    
    std::vector<int> sz, par;
    
    int numSets;
    
    std::vector<std::pair<int *, int>> history;
    
    DSU(int n)
        : sz(n+1, 1)
        , par(n+1)
        , numSets(n)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    bool isConnected(int u, int v) const {
        return getPar(u) == getPar(v);
    }
    
    int getPar(int u) const {
        return (u == par[u] ? u : getPar(par[u]));
    }
    
    void addToHistory(int *pointer) {
        history.emplace_back(pointer, *pointer);
    }
    
    int getVersion() const {
        return (int)history.size();
    }
    
    void rollBack(int version) {
        while ((int)history.size() > version) {
            auto [pointer, value] = history.back();
            history.pop_back();
            *pointer = value;
        }
    }
    
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        // запомнить изменённые значения:
        addToHistory(&sz[u]);
        addToHistory(&par[v]);
        addToHistory(&numSets);
        // присоединять "v" к "u"
        sz[u] += sz[v];
        par[v] = u;
        numSets--;
    }
    
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n); // 1-индексакция
    std::vector<int> versions;
    while (q --> 0) {
        std::string s; std::cin >> s;
        if (s[0] == 'p') {
            versions.push_back(dsu.getVersion());
        } else if (s[0] == 'u') {
            int u, v;
            std::cin >> u >> v;
            dsu.connect(u, v);
            std::cout << dsu.numSets << "\n";
        } else { // rollback
            assert(s[0] == 'r');
            dsu.rollBack(versions.back());
            versions.pop_back();
            std::cout << dsu.numSets << "\n";
        }
    }
}
