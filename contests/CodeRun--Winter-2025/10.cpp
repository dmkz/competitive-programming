#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using tiii = std::tuple<int,int,int>;
using vtiii = std::vector<tiii>;
const int inf = (int)1e9+7;
void setmax(auto &x, const auto &y) { if (x < y) x = y; }
void setmin(auto &x, const auto &y) { if (y < x) x = y; }
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
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v) return;
        if (sz[u] < sz[v])
            std::swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
    }
};
template<size_t id>
void readDataInTheStupidFormatEver( vtiii & edges) {
    for (auto &it : edges)
        std::cin >> std::get<id>(it);
}
void solve() {
    int nVert, nEdges;
    std::cin >> nVert >> nEdges;
    DSU dsu(nVert);
    vtiii edges(nEdges);
    readDataInTheStupidFormatEver<1>(edges);
    readDataInTheStupidFormatEver<2>(edges);
    readDataInTheStupidFormatEver<0>(edges);
    std::sort(all(edges));
    vi answ(nVert+1, inf);
    int k = 1;
    answ[1] = 0;
    for (int i = 0; i < isz(edges); i++) {
        // соединяем:
        auto [ci, ai, bi] = edges[i];
        ai--, bi--;
        dsu.connect(ai, bi);
        setmax(k, dsu.sz[dsu.getPar(ai)]);
        // обновляем ответ:
        if (i == isz(edges)-1 || ci != std::get<0>(edges[i+1])) {
            assert(0 <= k && k < isz(answ));
            setmin(answ[k], ci);
        }
    }
    for (int i = isz(answ)-2; i >= 1; i--)
        setmin(answ[i], answ[i+1]);
    for (int i = 1; i < isz(answ); i++) {
        if (answ[i] == inf)
            std::cout << ' ' << -1;
        else
            std::cout << ' ' << answ[i];
    }
    std::cout << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
