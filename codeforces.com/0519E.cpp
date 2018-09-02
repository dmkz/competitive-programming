/*
    Problem: 519E. A and B and Lecture Rooms
    
    Solution: DFS, LCA, trees, Sparse Table, O((n+q)*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    // Input tree:
    int n; scanf("%d", &n);
    vvi edges(1+n);
    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    // Run DFS for calculating height, parent and size:
    const int NMAX = 128*1024, PMAX = 17;
    static int parent[PMAX][NMAX];
    vi height(1+n), size(1+n);
    std::function<void(int,int,int)> visit = [&](int u, int p, int h) {
        parent[0][u] = p;
        height[u] = h;
        size[u] = 1;
        for (int v : edges[u]) {
            if (v == p) continue;
            visit(v, u, h+1);
            size[u] += size[v];
        }
    };
    visit(1,0,1);
    // Sparse Table:
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 1; i <= n; ++i) {
            int prev = parent[p-1][i];
            if (!prev) continue;
            parent[p][i] = parent[p-1][prev];
        }
    }
    // Function for answer to query:
    std::function<int(int,int)> query = [&](int u, int v) {
        if (u == v) return n;
        if (height[u] > height[v]) return query(v,u);
        // find dist to lca, `tu` and `tv` - subtree of `lca` which contain `u` and `v`:
        int tu = u, tv = v;
        int delta = height[tv] - height[tu];
        for (int p = PMAX-1; p >= 0; --p) {
            if ((delta >> p) & 1) {
                tv = parent[p][tv];
            }
        }
        for (int p = PMAX-1; p >= 0; --p) {
            int nu = parent[p][tu], nv = parent[p][tv];
            if (nu != nv) {
                tu = nu;
                tv = nv;
            }
        }
        // Get parent:
        int par;
        if (tu == tv) {
            par = tu;
        } else {
            assert(parent[0][tu] == parent[0][tv]);
            par = parent[0][tu];
        }
        int du = height[u] - height[par];
        int dv = height[v] - height[par];
        if ((du+dv)%2 == 1) return 0;
        if (du == dv) return n - size[tu] - size[tv];
        assert(du < dv);
        // up from vertix `v` to half of path:
        delta = (du + dv) / 2 - 1;
        for (int p = PMAX-1; p >= 0; --p) {
            if ((delta >> p) & 1) {
                v = parent[p][v];
            }
        }
        return size[parent[0][v]] - size[v];
    };
    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d %d", &u, &v);
        printf("%d\n", query(u,v));
    }
    return 0;
}