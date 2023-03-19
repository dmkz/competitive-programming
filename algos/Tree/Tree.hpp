#ifndef __TREE_HPP__
#define __TREE_HPP__

namespace algos {
namespace tree {
inline vvi edges2adj(int n, const vpii & edges) {
    vvi adj(n+1);
    for (const auto &[u, v] : edges) {
        assert(0 <= u && u <= n);
        assert(0 <= v && v <= n);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return adj;
}
inline vpii readEdges(int n, std::istream &is = std::cin) {
    vpii edges(n-1);
    for (auto &[u,v] : edges)
        is >> u >> v;
    return edges;
}
inline vvi readAdj(int n, std::istream &is = std::cin) {
    return edges2adj(n,readEdges(n,is));
}
struct EulerTour {

    vvi adj;
    vi tin, tout;
    int timer{};
    
    void dfs(int u, int p) {
        tin[u] = ++timer;
        for (int v : adj[u])
            if (v != p)
                dfs(v,u);
        tout[u] = timer;
    }
    
    auto build(int n, const vpii &edges, int root = 1)
    {
        timer = -1;
        adj.assign(1+n,{});
        tin.assign(n+1,-1);
        tout.assign(n+1,-1);
        for (auto &[u,v] : edges) {
            adj[u] << v;
            adj[v] << u;
        }
        dfs(root, 0);
        return std::make_tuple([&](int u){return tin[u];},
                               [&](int u){return tout[u];});
    }

    bool isParent(int vertex, int parent) const {
        return tin[parent] <= tin[vertex] && tout[vertex] <= tout[parent];
    }

};
} // namespace tree
} // namespace algos
#endif // __TREE_HPP__