#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int NMAX = 200200, PMAX = 20;
int par[PMAX][NMAX], dep[NMAX];
void add(int u, int p) {
    par[0][u] = p;
    dep[u] = dep[p]+1;
    for (int p = 1; p < PMAX; p++)
        par[p][u] = par[p-1][par[p-1][u]];
}
int up(int u, int delta) {
    for (int bit = PMAX-1; bit >= 0; bit--)
        if ((delta >> bit) & 1)
            u = par[bit][u];
    return u;
}
int get(int u, int v) {
    // пусть u будет ниже, чем v
    if (dep[u] < dep[v])
        swap(u,v);
    // поднимаем u на уровень v
    u = up(u, dep[u] - dep[v]);
    // делаем двоичный поиск
    for (int bit = PMAX-1; bit >= 0; bit--) {
        int pu = par[bit][u];
        int pv = par[bit][v];
        if (pu != pv)
            u = pu, v = pv;
    }
    // возвращаем ответ
    return u == v ? u : par[0][u];
}
bool onPath(int u, int v, int what) {
    if (dep[u] > dep[v]) swap(u,v);
    if (dep[what] < dep[u] || dep[what] > dep[v])
        return false;
    return up(v, dep[v] - dep[what]) == what;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем списки смежности
    int n; cin >> n;
    vvi adj(1+n);
    for (int i = 1, u, v; i < n; i++) {
        cin >> u >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    // строим lca:
    function<void(int,int)> dfs = [&](int u, int p) {
        add(u,p);
        for (int v : adj[u])
            if (v != p)
                dfs(v,u);
    };
    dfs(1,0);
    // отвечаем на запросы
    int q; cin >> q;
    while (q --> 0) {
        // читаем запрос
        int nRed, nBlue; cin >> nRed >> nBlue;
        vi red(nRed), blue(nBlue);
        for (auto &it : red) cin >> it;
        for (auto &it : blue) cin >> it;
        // находим lca всех синих и красных
        int blueLCA = blue.front(), redLCA = red.front();
        for (int i = 1; i < nBlue; i++)
            blueLCA = get(blueLCA, blue[i]);
        for (int i = 1; i < nRed; i++)
            redLCA = get(redLCA, red[i]);
        // если всё фигово, то либо синий lca лежит на красном
        // пути, либо наоборот
        bool ok = true;
        for (int x : red)
            ok &= !onPath(x,redLCA,blueLCA);
        for (int x : blue)
            ok &= !onPath(x,blueLCA,redLCA);
        cout << (ok ? "YES\n" : "NO\n");
    }
}
