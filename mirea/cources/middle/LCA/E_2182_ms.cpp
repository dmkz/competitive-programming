#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
const int NMAX = 100100, PMAX = 17;
int par[NMAX][PMAX], dep[NMAX];
void add(int u, int p) {
    par[u][0] = p;
    dep[u] = dep[p]+1;
    for (int p = 1; p < PMAX; p++)
        par[u][p] = par[par[u][p-1]][p-1];
}
int up(int u, int delta) {
    for (int bit = PMAX-1; bit >= 0; bit--)
        if ((delta >> bit) & 1)
            u = par[u][bit];
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
        int pu = par[u][bit];
        int pv = par[v][bit];
        if (pu != pv) {
            u = pu, v = pv;
        }
    }
    // возвращаем ответ
    return u == v ? u : par[u][0];
}
int main() {
    freopen("lca_rmq.in", "rt", stdin);
    freopen("lca_rmq.out", "wt", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q; cin >> n >> q;
    vvi next(n);
    for (int i = 1, p; i < n; i++) {
        cin >> p;
        next[p].push_back(i);
    }
    function<void(int,int)> dfs = [&](int u, int p)
    {
        add(u,p);
        for (int v : next[u])
            dfs(v,u);
    };
    for (int v : next[0])
        dfs(v,0);
    vector<int> a(4);
    cin >> a[0] >> a[1];
    int x, y, z;
    cin >> x >> y >> z;
    auto calcAndShift = [&]() {
        for (int i = 2; i < isz(a); i++) {
            a[i] = (x*1LL*a[i-2] + y*1LL*a[i-1] + z) % n;
        }
        a[0] = a[2];
        a[1] = a[3];
    };
    int64_t sum{};
    int v = 0;
    for (int i = 0; i < q; i++) {
        int x = (a[0]+v)%n;
        int y = a[1];
        v = get(x,y);
        sum += v;
        calcAndShift();
    }
    cout << sum << '\n';
}
