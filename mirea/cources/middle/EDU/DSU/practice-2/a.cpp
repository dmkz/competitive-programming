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
    
};
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, q; std::cin >> n >> q;
    DSU dsu(n+1);
    while (q --> 0) {
        char ch; std::cin >> ch;
        if (ch == '?') {
            int x; std::cin >> x;
            x = dsu.getPar(x);
            int answ = dsu.right[x];
            if (answ > n)
                answ = -1;
            std::cout << answ << '\n';
        } else {
            assert(ch == '-');
            int x; std::cin >> x;
            dsu.connect(x, x+1);
        }
    }
}
