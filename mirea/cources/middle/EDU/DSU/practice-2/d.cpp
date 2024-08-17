#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;

struct DSU {
    vi sz, par, dist;
    
    DSU(int n) : sz(n+1, 1), par(n+1), dist(n+1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
    }
    
    int getPar(int u) {
        return (par[u] == u ? u : 
            [&]()
            {   
                // эвристика сжатия путей
                int pu = getPar(par[u]);
                // dist[par[u]] = расстояние от старого предка вершины u
                // до корня. Мы переподвешиваем к этому корню
                // поэтому мы должны прибавить расстояние до этого корня
                if (pu != par[u]) // (если оно ещё не было прибавлено)
                    dist[u] += dist[par[u]];
                return par[u] = pu;
            }());
    }
    
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    
    void connect(int child, int parent) {
        par[child] = parent;
        dist[child]++; // расстояние у child до предка увеличивается на +1
    }
    
    int getDepth(int u) {
        int pu = getPar(u);
        int answ = dist[u];
        if (pu != u)
            answ += getDepth(pu);
        return answ;
    }
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n);
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) {
            int x, y; std::cin >> x >> y;
            dsu.connect(x, y);
        } else {
            assert(t == 2);
            int x; std::cin >> x;
            std::cout << dsu.getDepth(x) << "\n";
        }
    }
}
