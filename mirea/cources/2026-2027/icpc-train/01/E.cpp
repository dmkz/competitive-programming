#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// структура данных "система непересекающихся множеств": в каждом поддереве храним размер, представителя,
// а также флаг: есть ли электростанция в данном поддереве или нет. Ответ на задачу будем поддерживать
// и обновлять после каждого запроса.
struct DSU {
    vector<int> par, sz, enabled;
    int answ{};
    DSU(int n) : par(n+1), sz(n+1, 1), enabled(n+1, false)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    int getPar(int u) {
        return (u == par[u] ? u : (par[u] = getPar(par[u])));
    }
    // размещение электростанции:
    void enable(int i) {
        i = getPar(i);
        enabled[i] = true;
        answ += sz[i];
    }
    // проведение ребра и обновление ответа:
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v) return;
        if (sz[u] < sz[v]) swap(u, v);
        if (enabled[u]) answ -= sz[u];
        if (enabled[v]) answ -= sz[v];
        sz[u] += sz[v];
        par[v] = u;
        enabled[u] |= enabled[v];
        if (enabled[u]) answ += sz[u];
    }
};
void solve() {
    // чтение всех данных:
    int n, m, k; cin >> n >> m >> k;
    vector<int> p(k);
    for (auto &it : p) cin >> it;
    vector<pair<int,int>> edges(m);
    for (auto &[u, v] : edges)
        cin >> u >> v;
    int q; cin >> q;
    vector<int> queries(q), usedEdges(m);
    for (auto &it : queries) {
        cin >> it, it--;
        usedEdges[it] = 1;
    }
    // вместо удалений будем рассматривать запросы с конца в начало и добавлять рёбра в граф
    // используем структуру данных "система непересекающихся множеств", которая поддерживает
    // все операции, касающиеся добавления рёбер.
    DSU dsu(n);
    // устанавливаем электростанции:
    for (int i : p)
        dsu.enable(i);
    // проводим рёбра, которые никогда не будут удалены:
    for (int i = 0; i < m; i++)
        if (!usedEdges[i]) {
            auto [u, v] = edges[i];
            dsu.connect(u, v);
        }
    // теперь добавляем рёбра с конца в начало:
    vector<int> answ;
    for (int i = q-1; i >= 0; i--) {
        answ.push_back(dsu.answ);
        int id = queries[i];
        auto [u, v] = edges[id];
        dsu.connect(u, v);
    }
    // выводим ответ:
    for (int i = q-1; i >= 0; i--)
        cout << answ[i] << ' ';
    cout << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; // cin >> tt;
    while (tt --> 0) solve();
    return 0;
}