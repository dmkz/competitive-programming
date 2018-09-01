/*
    Problem: 1471. Distance in the Tree
    
    Solution: DFS, LCA, trees, Sparse Table, O((n+q)*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
struct Edge {int vert, cost;};
int main() {
    // INPUT:
    const int NMAX = 64*1024, PMAX = 16;
    int n; scanf("%d", &n);
    std::vector<Edge> edges[NMAX];
    for (int i = 1; i < n; ++i) {
        int u, v, w; scanf("%d %d %d", &u, &v, &w);
        edges[u].push_back(Edge{v,w});
        edges[v].push_back(Edge{u,w});
    }
    // DFS:
    static int parent[PMAX][NMAX], dist[PMAX][NMAX];
    std::fill(&parent[0][0], &parent[0][0] + PMAX * NMAX, -1);
    std::vector<int> height(NMAX);
    std::function<void(int,int,int,int)> dfs = [&](int u, int p, int w, int h) {
        parent[0][u] = p;
        dist[0][u] = w;
        height[u] = h;
        for (auto& e : edges[u]) {
            if (e.vert == p) continue;
            dfs(e.vert, u, e.cost, h+1);
        }
    };
    dfs(0,-1,0,0);
    // Sparse Table:
    for (int p = 1; p < PMAX; ++p) {
        for (int i = 0; i < n; ++i) {
            int prev = parent[p-1][i];
            if (prev == -1) continue;
            parent[p][i] = parent[p-1][prev];
            dist[p][i] = dist[p-1][i] + dist[p-1][prev];
        }
    }
    // Queries:
    std::function<int(int,int)> query = [&](int u, int v) {
        if (height[u] > height[v]) return query(v, u);
        int answ = 0, dh = height[v] - height[u];
        for (int p = PMAX - 1; p >= 0; --p) {
            if ((dh >> p) & 1) {
                answ += dist[p][v];
                v = parent[p][v];
            }
        }
        for (int p = PMAX - 1; p >= 0; --p) {
            int nu = parent[p][u];
            int nv = parent[p][v];
            if (nu == nv) continue;
            answ += dist[p][u] + dist[p][v];
            u = nu, v = nv;
        }
        if (u != v) {
            answ += dist[0][u] + dist[0][v];
        }
        return answ;
    };
    int q; scanf("%d", &q);
    while (q--) {
        int u, v; scanf("%d %d", &u, &v);
        printf("%d\n", query(u,v));
    }
    return 0;
}