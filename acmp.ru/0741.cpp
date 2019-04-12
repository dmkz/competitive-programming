/*
    Задача: 741. Замечательные дороги
    
    Решение: графы, поиск в глубину, точки сочления, компоненты вершинной двусвязности, O(n + m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define isz(x) (int)(x).size()

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

struct Edge {
    int u, v, c;
    Edge(int u_ = 0, int v_ = 0, int c_ = 0)
        : u(u_), v(v_), c(c_) { }
};

struct Graph {
    const int n;
    vvi adj;
    std::vector<Edge> edges;
    vi tin, fup, stack;
    int timer;
    Graph(int n_) : n(n_) {
        adj.resize(1+n);
    }
    void add_edge(int u, int v) {
        adj[u].push_back(isz(edges));
        adj[v].push_back(isz(edges));
        edges.push_back(Edge(u,v));
    }
    void dfs(int u, int p) {
        tin[u] = fup[u] = ++timer;
        bool isRoot = (p == 0);
        int nChildren = 0;
        for (auto eid : adj[u]) {
            const int v = edges[eid].u + edges[eid].v - u;
            if (v == p) { continue; }
            if (!tin[v]) {
                ++nChildren;
                if (nChildren > 1 && isRoot) {
                    for (int color = 1; !stack.empty(); stack.pop_back()) {
                        edges[stack.back()].c = color++;
                    }
                }
                stack.push_back(eid);
                dfs(v, u);
                if (!isRoot && tin[u] <= fup[v]) {
                    int color = 1;
                    edges[eid].c = color++;
                    while (stack.back() != eid) {
                        edges[stack.back()].c = color++;
                        stack.pop_back();
                    }
                    stack.pop_back();
                }
                fup[u] = std::min(fup[u], fup[v]);
            } else if (tin[u] > tin[v]) {
                stack.push_back(eid);
            }
            fup[u] = std::min(fup[u], tin[v]);
        }
    }
    int solve() {
        tin.assign(1+n,0);
        fup.assign(1+n,0);
        stack.clear();
        timer = 0;
        for (int u = 1; u <= n; ++u) {
            if (!tin[u]) {
                dfs(u, 0);
                for (int color = 1; !stack.empty(); stack.pop_back()) {
                    edges[stack.back()].c = color++;
                }
            }
        }
        int max = 0;
        for (auto &e : edges) { assert(e.c != 0); max = std::max(max, e.c); }
        return max;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int nV, nE;
    while (std::cin >> nV >> nE) {
        Graph graph(nV);
        for (int i = 0; i < nE; ++i) {
            int u, v; std::cin >> u >> v;
            graph.add_edge(u,v);
        }
        std::cout << graph.solve() << '\n';
        for (const auto &e : graph.edges) {
            std::cout << e.u << ' ' << e.v << ' ' << e.c << "\n";
        }
    }
    return 0;
}