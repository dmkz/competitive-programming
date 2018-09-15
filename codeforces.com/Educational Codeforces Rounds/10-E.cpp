/*
    Problem: 652E. Pursuit For Artifacts
    
    Solution: graphs, trees, dfs, bfs, bridges, O(n * log(m) + m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
#include <queue>

struct Edge {
    int vert, cost, id;
    
    Edge(int vert_ = 0, int cost_ = 0, int id_ = 0) :
        vert(vert_), cost(cost_), id(id_) { }
};

int main() {
    // Input:
    int n, m; scanf("%d %d", &n, &m);
    std::vector<bool> is_bridge(m);
    std::vector<std::vector<Edge>> edges(1+n);
    for (int i = 0; i < m; ++i) {
        int u, v, c; scanf("%d %d %d", &u, &v, &c);
        edges[u].push_back(Edge(v, c, i));
        edges[v].push_back(Edge(u, c, i));
    }
    int s, t; scanf("%d %d", &s, &t);
    // Find bridges:
    int timer = 0; std::vector<int> tin(1+n), fup(1+n);
    std::function<void(int,int)> find_bridges = [&](int u, int p) {
        timer++;
        tin[u] = fup[u] = timer;
        for (auto& e : edges[u]) {
            int v = e.vert;
            if (v == p) continue;
            if (!tin[v]) {
                find_bridges(v,u);
                fup[u] = std::min(fup[u], fup[v]);
            } else {
                fup[u] = std::min(fup[u], tin[v]);
            }
            if (fup[v] > tin[u]) {
                is_bridge[e.id] = true;
            }
        }
    };
    find_bridges(1,0);
    // BFS for finding components:
    std::vector<int> part(1+n), value(1+n);
    std::function<void(int,int)> make_part = [&](int u, int color) {
        std::queue<int> queue;
        queue.push(u);
        part[u] = color;
        while (!queue.empty()) {
            u = queue.front(); queue.pop();
            for (auto& e : edges[u]) {
                if (is_bridge[e.id]) continue;
                value[color] |= e.cost;
                if (!part[e.vert]) {
                    part[e.vert] = color;
                    queue.push(e.vert);
                }
            }
        }
    };
    int nParts = 0;
    for (int u = 1; u <= n; ++u) {
        if (!part[u]) {
            make_part(u, ++nParts);
        }
    }
    value.resize(nParts+1);
    // Making tree on components between bridges:
    std::vector<std::vector<Edge>> tree(1+nParts);
    for (int u = 1; u <= n; ++u) {
        for (auto& e : edges[u]) {
            int v = e.vert;
            if (part[u] != part[v]) {
                int fi = part[u];
                int se = part[v];
                int cost = e.cost;
                tree[fi].push_back(Edge(se, cost));
                tree[se].push_back(Edge(fi, cost));
            }
        }
    }
    // Sorting edges and erase repeats:
    for (int u = 1; u <= nParts; ++u) {
        std::sort(tree[u].begin(), tree[u].end(), [](const Edge& a, const Edge& b) {
            return a.vert < b.vert || (a.vert == b.vert && a.cost > b.cost);
        });
        tree[u].erase(std::unique(tree[u].begin(), tree[u].end(), [](const Edge& a, const Edge& b) {
            return a.vert == b.vert;
        }), tree[u].end());
    }
    // DFS on tree with root = s:
    std::vector<int> can(1+nParts);
    std::function<void(int,int,int)> dfs = [&](int u, int p, int val) {
        val |= value[u];
        can[u] |= val;
        for (auto& e : tree[u]) {
            if (e.vert == p) continue;
            dfs(e.vert, u, e.cost | val);
        }
    };
    dfs(part[s],0,0);
    printf(can[part[t]] ? "YES\n" : "NO\n");
    return 0;
}