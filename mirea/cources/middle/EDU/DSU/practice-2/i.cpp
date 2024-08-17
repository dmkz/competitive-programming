#include <bits/stdc++.h>

using vi = std::vector<int>;

struct DSU {
    vi sz, par;
    
    DSU(int n) : sz(n, 1), par(n)
    {
        for (int i = 0; i < n; i++)
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
   
};

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; std::cin >> n >> m;
    DSU dsu(2 * n); // каждую вершину дублируем
                    // таким образом вводим пары (вершина, цвет)
    int shift = 0;
    for (int i = 1; i <= m; i++) {
        int t, a, b; std::cin >> t >> a >> b;
        // переходим в ноль-индексацию:
        a--, b--;
        // вычисляем искомые номера соединяемых вершин:
        int x = (a+shift) % n;
        int y = (b+shift) % n;
        if (t == 0) { // объединение: соединяем пары с противопложными цветами
            dsu.connect((x << 1) | 0, (y << 1) | 1);
            dsu.connect((x << 1) | 1, (y << 1) | 0);
        } else { // проверка: проверяем пары с противопложными цветами
            assert(t == 1);
            bool differentColors = dsu.isConnected((x << 1) | 0, (y << 1) | 1);
            bool yes = !differentColors;
            std::cout << (yes ? "YES\n" : "NO\n");
            shift = (shift + yes) % n;
        }
    }
}
