/*
    Problem: 160D. Edges in MST
    
    Solution: MST, DSU, DFS, graphs, bridges, O(n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()
#define unique(x) (x).erase(std::unique(all(x)), (x).end())
#define binpos(x, y) int(std::lower_bound(all(x), (y)) - (x).begin())

const int WMAX = (int)1e6, INF = (int)1e9+7;

struct Edge {
    int u, v, id;
    
    Edge(int u_ = 0, int v_ = 0, int id_ = 0) : u(u_), v(v_), id(id_) { }
};

struct Pair {
    int fi, se;
};

bool operator<(const Pair &lhs, const Pair &rhs) {
    return lhs.fi < rhs.fi || (lhs.fi == rhs.fi && lhs.se < rhs.se);
}

bool operator<(const Edge &lhs, const Edge& rhs) {
    return lhs.u < rhs.u || (lhs.u == rhs.u && (lhs.v < rhs.v || (lhs.v == rhs.v && lhs.id < rhs.id)));
}

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<std::string> vs;
typedef std::vector<Edge> ve;
typedef std::vector<ve> vve;

struct DSU {
    vi parent, size;
    DSU(int n) : parent(1+n,0), size(1+n,1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    int get_parent(int u) {
        return u == parent[u] ? u : parent[u] = get_parent(parent[u]);
    }
    void union_sets(int u, int v) {
        u = get_parent(u);
        v = get_parent(v);
        if (u != v) {
            if (size[u] < size[v]) std::swap(u,v);
            size[u] += size[v];
            parent[v] = u;
        }
    }
};

struct BridgesFinder {

    int nVert;
    
    vvi next;
    
    ve edges;
    
    vi isBridge, tin, fup;
    
    int timer;
    
    BridgesFinder() { }
    
    void init(int nVert_) {
        nVert = nVert_;
        next.resize(1+nVert);
    }
    
    void clear() {
        nVert = 0, timer = 0;
        isBridge.clear();
        tin.clear();
        fup.clear();
        edges.clear();
        next.clear();
    }
    
    void add_edge(const Edge& e) {
        edges.push_back(e);
        isBridge.push_back(0);
    }
    
    void dfs(int u, int p) {
        timer++;
        tin[u] = std::min(tin[u], timer);
        fup[u] = std::min(fup[u], timer);
        for (int id : next[u]) {
            const auto &e = edges[id];
            int v = e.u + e.v - u;
            if (v == p) {
                continue;
            }
            if (tin[v] == INF) {
                dfs(v, u);
            }
            fup[u] = std::min(fup[u], fup[v]);
            if (tin[u] < fup[v]) {
                isBridge[id] = true;
            }
        }
    }
    
    vi find_bridges() {
        for (int id = 0; id < (int)edges.size(); ++id) {
            const auto &e = edges[id];
            next[e.u].push_back(id);
            next[e.v].push_back(id);
        }
        timer = 0;
        tin.assign(1+nVert, INF);
        fup.assign(1+nVert, INF);
        for (int u = 1; u <= nVert; ++u) {
            if (tin[u] == INF) {
                dfs(u, 0);
            }
        }
        vi answ;
        for (int i = 0; i < (int)edges.size(); ++i) {
            if (isBridge[i]) {
                answ.push_back(edges[i].id);
            }
        }
        return answ;
    }
};

vs solve(const int nVert, const int nEdges, const vve& edges) {
    DSU dsu(nVert); vs answ(nEdges);
    ve tmp; vi vertices, ids;
    BridgesFinder bf;
    for (int w = 0; w <= WMAX; ++w) {
        const auto &wEdges = edges[w];
        if (wEdges.empty()) continue;
        tmp.clear();
        vertices = {0};
        bf.clear();
        for (auto &e : wEdges) {
            int u = dsu.get_parent(e.u);
            int v = dsu.get_parent(e.v);
            if (u > v) std::swap(u, v);
            if (u == v) {
                assert(answ[e.id].empty());
                answ[e.id] = "none";
                continue;
            }
            tmp.push_back(Edge(u, v, e.id));
            vertices.push_back(u);
            vertices.push_back(v);
        }
        if (tmp.empty()) {
            continue;
        }
        std::sort(all(vertices));
        unique(vertices);
        bf.init((int)vertices.size());
        std::sort(all(tmp));
        int u = tmp.front().u, v = tmp.front().v;
        ids.clear();
        for (int i = 0; i < (int)tmp.size(); ++i) {
            if (tmp[i].u == u && tmp[i].v == v) {
                ids.push_back(tmp[i].id);
            } else {
                if (ids.size() > 1u) {
                    for (int id : ids) {
                        assert(answ[id].empty());
                        answ[id] = "at least one";
                    }
                }
                bf.add_edge(Edge(binpos(vertices,u),binpos(vertices,v),ids.front()));
                u = tmp[i].u;
                v = tmp[i].v;
                ids = {tmp[i].id};
            }
        }
        if (ids.size() > 1u) {
            for (int id : ids) {
                assert(answ[id].empty());
                answ[id] = "at least one";
            }
        }
        bf.add_edge(Edge(binpos(vertices,u),binpos(vertices,v),ids.front()));
        
        ids = bf.find_bridges();
        for (int id : ids) {
            if (answ[id].empty()) {
                answ[id] = "any";
            }
        }
        
        for (auto &e : wEdges) {
            if (answ[e.id].empty()) {
                answ[e.id] = "at least one";
            }
            dsu.union_sets(e.u, e.v);
        }
    }
    return answ;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int nVert, nEdges;
    while (std::cin >> nVert >> nEdges) {
        vve edges(1+WMAX);
        for (int i = 0; i < nEdges; ++i) {
            int u, v, w;
            std::cin >> u >> v >> w;
            if (u > v) std::swap(u, v);
            edges[w].push_back(Edge(u,v,i));
        }
        vs answ = solve(nVert, nEdges, edges);
        for (const auto &s : answ) {
            std::cout << s << '\n';
        }
        std::cout << std::endl;
    }
    return 0;
}