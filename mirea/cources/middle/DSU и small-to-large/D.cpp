#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using namespace std;
struct DSU {
    vector<int> parent, sz;
    DSU(int n) : parent(1+n), sz(1+n,1)
    {
        for (int u = 1; u <= n; u++) parent[u] = u;
    }
    int getParent(int u) {
        return u == parent[u] ? u : parent[u] = getParent(parent[u]);
    }
    bool isConnected(int u, int v) {
        return getParent(u) == getParent(v);
    }
    void connect(int u, int v) {
        u = getParent(u), v = getParent(v);
        if (v == u) return;
        if (sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v];
        parent[v] = u;
    }
};
int main() {
    // гарантируется, что после всех удалений не будет никаких рёбер, значит
    // разворачиваем запросы и заменяем "cut" на "add" - будем добавлять в
    // пустой граф вместо удаления рёбер. Для проверки связности используем dsu
    freopen("cutting.in", "rt", stdin);
    freopen("cutting.out", "wt", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, e, q;
    cin >> n >> e >> q;
    while (e --> 0) {
        // рёбра не нужны, даже не сохраняем!
        int x, y; cin >> x >> y;
    }
    // читаем запросы и реверсим их
    vector<tuple<string,int,int>> queries(q);
    for (auto &[t, u, v] : queries) cin >> t >> u >> v;
    reverse(all(queries));
    // решаем задачу, сохраняя ответы:
    vector<string> answ;
    DSU dsu(n);
    for (auto &[t, u, v] : queries) {
        if (t == "cut") dsu.connect(u,v);
        else answ.push_back((dsu.isConnected(u,v) ? "YES" : "NO"));
    }
    reverse(all(answ));
    for (auto &it : answ) cout << it << '\n';
}