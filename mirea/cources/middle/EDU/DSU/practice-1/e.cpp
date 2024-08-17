#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
void setmin(auto &x, const auto &y) {
    if (x > y) x = y;
}
using vi = std::vector<int>;
using pii = std::pair<int, int>;
using vpii = std::vector<pii>;
const int inf = (int)1e9+7;
struct DSU {
    
    vi sz, par, minTime;
    
    DSU(int n)
        : sz(n+1, 1)
        , par(n+1)
        , minTime(n+1, inf)
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
    
    void connect(int u, int v, int currTime) {
        u = getPar(u), v = getPar(v);
        if (u == v)
            return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        // присоединять "v" к "u"
        // вот тут не соединены
        bool inU = isConnected(1, u);
        bool inV = isConnected(1, v);
        if (inU && !inV) {
            minTime[v] = currTime;
        }
        if (inV && !inU) {
            minTime[u] = currTime;
            std::swap(u, v);
        }
        sz[u] += sz[v];
        par[v] = u;
    }
    
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n); // 1-индексакция
    vi left(1+n), right(1+n);
    std::set<pii> allConnections;
    for (int i = 1; i <= n; i++) {
        std::cin >> left[i] >> right[i];
        if (left[i] != -1)
            allConnections.insert({i, 1});
        if (right[i] != -1)
            allConnections.insert({i, 2});
    }
    vpii queries(q);
    for (auto &[p,h] : queries) {
        std::cin >> p >> h;
        allConnections.erase({p, h});
    }
    for (auto &[p,h] : allConnections)
        dsu.connect(p, (h == 1 ? left[p] : right[p]), +inf);
    // начинаем обрабатывать запросы
    vi answer(1+n, inf);
    for (int u = 1; u <= n; u++)
        if (dsu.isConnected(1, u))
            answer[u] = -1;
    std::reverse(all(queries));
    int currTime = isz(queries);
    for (const auto &[p, h] : queries)
        dsu.connect(p, (h == 1 ? left[p] : right[p]), --currTime);
    for (int currVert = 1; currVert <= n; currVert++) {
        setmin(answer[currVert], dsu.minTime[currVert]);
        for (int u = currVert; dsu.par[u] != u; ) {
            u = dsu.par[u];
            setmin(answer[currVert], dsu.minTime[u]);
        }
        int answ = answer[currVert];
        std::cout << (answ == inf ? -1 : answ) << "\n";
    }
}
