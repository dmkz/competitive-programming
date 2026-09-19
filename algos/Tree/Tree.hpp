#ifndef __TREE_HPP__
#define __TREE_HPP__
/*******************************************************************************************
 * The file "Tree.hpp" is a part of competitive programming C++ library "algos".           *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "template.hpp"
#include <type_traits>
#include <utility>
namespace algos {
namespace tree {
inline vvi par2adj(int n, const vi &par) {
    assert(isz(par) == n+1);
    vvi adj(n+1);
    for (int u = 1; u <= n; u++)
        if (int v = par[u]; v) {
            adj[u] << v;
            adj[v] << u;
        }
    return adj;
}
inline vvi edges2adj(int n, const vpii &edges) {
    vvi adj(n+1);
    for (const auto &[u,v] : edges) {
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        adj[u] << v;
        adj[v] << u;
    }
    return adj;
}
inline vpii readEdges(int n, std::istream &is = std::cin) {
    vpii edges(n-1);
    for (auto &[u,v] : edges) is >> u >> v;
    return edges;
}
inline vvi readAdj(int n, std::istream &is = std::cin) {
    return edges2adj(n,readEdges(n,is));
}
struct Edge {
    int u{}, v{};
    friend std::istream &operator>>(std::istream &in, Edge &e) {
        return in >> e.u >> e.v;
    }
    int getU() const {
        return u;
    }
    int getV() const {
        return v;
    }
    int opp(int x) const {
        assert(x == u || x == v);
        return (x == u ? v : u);
    }
};
struct NoOp {
    void operator()(auto&&...) const {}
};
template<typename EdgeT = Edge>
struct Tree {
    int n{};
    std::vector<EdgeT> edges;
    vvi adj;
    Tree() = default;
    explicit Tree(int n_) : n(n_), adj(n+1) {}
    Tree(int n_, std::vector<EdgeT> edges_) :
        n(n_), edges(std::move(edges_)) {
        buildAdjList();
    }
    void buildAdjList() {
        adj.assign(n+1,{});
        for (int id = 0; id < isz(edges); id++) {
            int u = edges[id].getU();
            int v = edges[id].getV();
            assert(1 <= u && u <= n);
            assert(1 <= v && v <= n);
            adj[u] << id;
            adj[v] << id;
        }
    }
    void setEdges(int n_, std::vector<EdgeT> edges_) {
        n = n_;
        edges = std::move(edges_);
        buildAdjList();
    }
    void addEdge(EdgeT edge) {
        int u = edge.getU();
        int v = edge.getV();
        assert(1 <= u && u <= n);
        assert(1 <= v && v <= n);
        int id = isz(edges);
        edges.push_back(std::move(edge));
        if (isz(adj) != n+1) adj.assign(n+1,{});
        adj[u] << id;
        adj[v] << id;
    }
    std::istream &readEdges(bool readN = true, std::istream &in = std::cin) {
        if (readN) in >> n;
        edges.resize(n-1);
        for (auto &edge : edges) in >> edge;
        buildAdjList();
        return in;
    }
    friend std::istream &operator>>(std::istream &in, Tree &tree) {
        return tree.readEdges(true,in);
    }
private:
    void callVertex(auto &func, int u, int p) const {
        if constexpr (std::is_invocable_v<decltype(func),int,int>)
            func(u,p);
        else if constexpr (std::is_invocable_v<decltype(func),int>)
            func(u);
        else
            func();
    }
    void callEdge(auto &func, int v, int u, int id) const {
        if constexpr (std::is_invocable_v<decltype(func),int,int,int>)
            func(v,u,id);
        else if constexpr (std::is_invocable_v<decltype(func),int,int>)
            func(v,u);
        else if constexpr (std::is_invocable_v<decltype(func),int>)
            func(v);
        else
            func();
    }
    void dfsImpl(int u, int p, auto &fe, auto &fin, auto &fout) const {
        callVertex(fin,u,p);
        for (int id : adj[u]) {
            int v = edges[id].opp(u);
            if (v != p) {
                callEdge(fe,v,u,id);
                dfsImpl(v,u,fe,fin,fout);
            }
        }
        callVertex(fout,u,p);
    }
public:
    template<typename FuncEdge = NoOp, typename FuncIn = NoOp, typename FuncOut = NoOp>
    void dfs(int u, int p = 0, FuncEdge fe = {}, FuncIn fin = {}, FuncOut fout = {}) const {
        dfsImpl(u,p,fe,fin,fout);
    }
};
} // namespace tree
} // namespace algos
#endif // __TREE_HPP__