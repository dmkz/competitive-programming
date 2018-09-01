/*
    Problem: 1329. Galactic History
    
    Solution: DFS, LCA, trees, Sparse Table, O((n+q)*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <functional>
#include <cassert>
int main() {
    // INPUT
    const int PMAX = 16, NMAX = 64*1024;
    static int parent[PMAX][NMAX];
    std::fill(&parent[0][0], &parent[0][0]+PMAX*NMAX, -1);
    int n, root = -1; scanf("%d", &n);
    std::vector<int> edges[NMAX];
    for (int i = 0; i < n; ++i) {
        int v, p; scanf("%d %d", &v, &p);
        if (p == -1) {
            root = v;
        } else {
            edges[p].push_back(v);
            edges[v].push_back(p);
        }
        parent[0][v] = p;
    }
    assert(root >= 0);
    // Precalc Sparse Table
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i < NMAX; ++i) {
            int prev = parent[p-1][i];
            if (prev == -1) continue;
            parent[p][i] = parent[p-1][prev];
        }
    }
    // DFS for calculate height:
    std::vector<int> height(NMAX);
    std::function<void(int,int,int)> dfs = [&](int u, int p, int h) {
        height[u] = h;
        for (int v : edges[u]) {
            if (v == p) continue;
            dfs(v,u,h+1);
        }
    };
    dfs(root,-1,0);
    // Function for answer to queries:
    std::function<int(int,int)> query = [&](int u, int v) {
        if (height[u] > height[v]) return (3-query(v,u)) % 3;
        int dh = height[v] - height[u];
        for (int p = PMAX - 1; p >= 0; --p) {
            if ((dh >> p) & 1) {
                v = parent[p][v];
            }
        }
        return u == v ? 1 : 0;
    };
    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d %d", &u, &v);
        printf("%d\n", query(u,v));
    }
    return 0;
}