#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
struct DSU {
    
    vi sz, par, right;
    
    DSU(int n) : sz(n+1, 1), par(n+1), right(n+1)
    {
        for (int i = 1; i <= n; i++)
            right[i] = par[i] = i;
    }
    
    int getPar(int u) {
        return (par[u] == u ? u : par[u] = getPar(par[u]));
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    void connect(int L, int R) {
        L = getPar(L), R = getPar(R);
        if (R == L)
            return;
        if (sz[R] < sz[L])
            std::swap(R, L);
        sz[R] += sz[L];
        par[L] = R;
        right[R] = std::max(right[R], right[L]);
    }
    
    int getRight(int R) {
        return right[getPar(R)];
    }
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n; std::cin >> n;
    DSU dsu(n+1);
    for (int i = 0; i < n; i++) {
        // находит ближайшую справа незанятую позицию:
        int p; std::cin >> p;
        p = dsu.getRight(p);
        // если вышли за пределы круга, продолжаем с 1:
        if (p == n+1)
            p = dsu.getRight(1);
        // выводим ответ:
        std::cout << p << ' ';
        // занимаем эту позицию:
        dsu.connect(p, p+1);
    }
    std::cout << '\n';
}
