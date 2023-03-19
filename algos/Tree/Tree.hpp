#ifndef __TREE_HPP__
#define __TREE_HPP__

namespace algos {
namespace tree {
inline vvi par2adj(int n, const vi &par) {
    assert(isz(par) == n+1);
    vvi adj(1+n);
    for (int u = 1; u <= n; u++) {
        if (int v = par[u]; v) {
            adj[u] << v;
            adj[v] << u;
        }
    }
    return adj;
}
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
} // namespace tree
} // namespace algos
#endif // __TREE_HPP__