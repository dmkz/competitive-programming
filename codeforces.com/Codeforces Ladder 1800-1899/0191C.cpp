/*
    Problem: 191C. Fools and Roads
    Solution: trees, dfs, queries offline, lca, O(n*log(n) + q)
*/
#include <bits/stdc++.h>
const auto is_sync_off = [](){std::ios_base::sync_with_stdio(0); std::cin.tie(0); return 0;}();
#define isz(x) (int)(x).size()
struct Edge { int u, v; };
using vi = std::vector<int>;
using vvi = std::vector<vi>;
const int NMAX = 128*1024, PMAX = 18;
int main() {
    for (int n; std::cin >> n;) {
        std::vector<Edge> edges;
        vvi adj(1+n);
        vi answ, depth(1+n);
        for (int i = 1; i < n; i++) {
            int u, v; std::cin >> u >> v;
            edges.push_back(Edge{u,v});
            answ.push_back(0);
            adj[u].push_back(isz(edges)-1);
            adj[v].push_back(isz(edges)-1);
        }
        static int parent[PMAX][NMAX];
        std::fill(&parent[0][0], &parent[0][0]+PMAX*NMAX,0);
        std::function<void(int,int,int)> dfs = [&](int u, int p, int d) {
            parent[0][u] = p;
            depth[u] = d;
            for (int id : adj[u]) {
                const auto &e = edges[id];
                int v = e.u + e.v - u;
                if (v == p) continue;
                dfs(v,u,d+1);
            }
        };
        dfs(1,0,0);
        for (int p = 1; p < PMAX; p++) {
            for (int u = 0; u < NMAX; u++) {
                parent[p][u] = parent[p-1][parent[p-1][u]];
            }
        }
        std::function<int(int,int)> lca = [&](int u, int v) {
            if (depth[u] < depth[v]) std::swap(u,v);
            int delta = depth[u] - depth[v];
            for (int bit = PMAX - 1; bit >= 0; --bit) {
                if (delta & (1 << bit)) {
                    u = parent[bit][u];
                }
            }
            for (int bit = PMAX - 1; bit >= 0; --bit) {
                int pu = parent[bit][u];
                int pv = parent[bit][v];
                if (pu != pv) {
                    u = pu;
                    v = pv;
                }
            }
            return u == v ? u : parent[0][u];
        };
        vi inc(1+n);
        int q; std::cin >> q;
        while (q--) {
            int u, v; std::cin >> u >> v;
            int p = lca(u,v);
            inc[p] -= 2;
            inc[u]++;
            inc[v]++;
        }
        std::function<int(int,int)> calc = [&](int u, int p) {
            int sum = 0;
            for (int id : adj[u]) {
                const auto &e = edges[id];
                int v = e.u + e.v - u;
                if (v == p) continue;
                int curr = calc(v,u);
                answ[id] = curr;
                sum += curr;
            }
            return sum + inc[u];
        };
        calc(1,0);
        for (auto it : answ) std::cout << it << ' ';
        std::cout << std::endl;
    }
}