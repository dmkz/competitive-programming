#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
#define int ll
using ll = long long;
using tiii = std::tuple<int,int,int>;
using vtiii = std::vector<tiii>;
using vi = std::vector<int>;

struct DSU {
    
    vi par, sz;
    
    DSU(int n) : par(n), sz(n, 1)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    
    int getPar(int u) {
        return u == par[u] ? u : par[u] = getPar(par[u]);
    }
    
    bool combine(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) std::swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        return true;
    }
};

void solveEasy(int numMinEdges = 1000) {
    std::string s;
    vtiii coords;
    auto dist = [&](int i, int j) {
        auto [x1, y1, z1] = coords[i];
        auto [x2, y2, z2] = coords[j];
        int dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
        return dx * dx + dy * dy + dz * dz;
    };
    while (std::getline(std::cin, s))
        if (s.size()) {
            int x, y, z;
            int code = sscanf(s.c_str(), "%lld,%lld,%lld", &x, &y, &z);
            assert(code == 3);
            coords.emplace_back(x, y, z);
        }
    vtiii edges;
    for (int i = 0; i < isz(coords); i++)
        for (int j = i+1; j < isz(coords); j++)
            edges.emplace_back(dist(i, j), i, j);
    std::sort(all(edges));
    DSU dsu(isz(coords));
    for (const auto &[w, u, v] : edges) {
        dsu.combine(u, v);
        numMinEdges--;
        if (numMinEdges == 0)
            break;
    }
    const int nVert = isz(coords);
    std::multiset<int> ms;
    for (int u = 0; u < nVert; u++)
        if (dsu.par[u] == u)
            ms.insert(dsu.sz[u]);
    std::vector res(ms.rbegin(), ms.rend());
    for (auto it : ms)
        std::cout << ' ' << it;
    std::cout << std::endl;
    res.resize(3);
    int prod = 1;
    for (auto it : res) prod *= it;
    std::cout << prod << std::endl;
}
void solveHard(int numMinEdges = 1000) {
    std::string s;
    vtiii coords;
    auto dist = [&](int i, int j) {
        auto [x1, y1, z1] = coords[i];
        auto [x2, y2, z2] = coords[j];
        int dx = x1 - x2, dy = y1 - y2, dz = z1 - z2;
        return dx * dx + dy * dy + dz * dz;
    };
    while (std::getline(std::cin, s))
        if (s.size()) {
            int x, y, z;
            int code = sscanf(s.c_str(), "%lld,%lld,%lld", &x, &y, &z);
            assert(code == 3);
            coords.emplace_back(x, y, z);
        }
    vtiii edges;
    for (int i = 0; i < isz(coords); i++)
        for (int j = i+1; j < isz(coords); j++)
            edges.emplace_back(dist(i, j), i, j);
    std::sort(all(edges));
    DSU dsu(isz(coords));
    int lastProd = -1;
    bool was = false;
    for (const auto &[w, u, v] : edges) {
        if (dsu.combine(u, v)) {
            lastProd = std::get<0>(coords[u]) *
                       std::get<0>(coords[v]);
            was = true;
        }
        numMinEdges--;
        if (numMinEdges == 0)
            break;
    }
    assert(was);
    std::cout << lastProd << std::endl;
}
main() {
    solveHard(INT_MAX);
}
