#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
struct DSUSegments {
    
    vi sz, par, right;
    
    DSUSegments(int n) : sz(n+1, 1), par(n+1), right(n+1)
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
struct DSU {
    vi sz, par;
    
    DSU(int n) : sz(n+1, 1), par(n+1)
    {
        for (int i = 1; i <= n; i++)
            par[i] = i;
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
    }
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSUSegments dsuSegments(n+1);
    DSU dsu(n+1);
    while (q --> 0) {
        int t, x, y; std::cin >> t >> x >> y;
        if (t == 1) {
            // просто соединить два множества
            dsu.connect(x, y);
        } else if (t == 2) {
            // соединить отрезки от x до y:
            while (dsuSegments.getRight(x) < y) {
                int nextSegmentStart = dsuSegments.getRight(x)+1;
                dsuSegments.connect(x, nextSegmentStart);
                dsu.connect(x, nextSegmentStart);
            }
        } else {
            assert(t == 3);
            bool ok = dsu.isConnected(x, y);
            std::cout << (ok ? "YES\n" : "NO\n");
        }
    }
}
