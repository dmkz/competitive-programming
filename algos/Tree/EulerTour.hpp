#ifndef __EULERTOUR_HPP__
#define __EULERTOUR_HPP__
namespace algos {
namespace euler {
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
} // namespace euler
} // namespace algos
#endif // __EULERTOUR_HPP__