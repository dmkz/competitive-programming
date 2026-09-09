#ifndef __UNDIRECTED_GRAPH_HPP__
#define __UNDIRECTED_GRAPH_HPP__
/*******************************************************************************************
 * The file "UndirectedGraph.hpp" is a part of competitive programming C++ library "algos" *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "template.hpp"
namespace algos {
namespace graph {
/*******************************************************************************
 * SearchResult - result of DFS or BFS in an undirected graph
 *
 * par[u]       - parent of vertex u, or -1 if u was not reached
 * parEdge[u]   - edge connecting u with its parent
 * dep[u]       - distance from the root in the search tree
 * order        - vertices in the order in which they were reached
 ******************************************************************************/
struct SearchResult {
    vi par, parEdge, dep, order;
    bool reached(int u) const {
        return par[u] != -1;
    }
};
/*******************************************************************************
 * SpanningTree - rooted spanning tree represented by parent vertices and edges
 ******************************************************************************/
struct SpanningTree : SearchResult {
    vi isTreeEdge;
};
/*******************************************************************************
 * UndirectedGraph - undirected graph with 0-indexed vertices and edges
 *
 * adj[u] contains indices of edges incident to vertex u.
 ******************************************************************************/
struct UndirectedGraph {
    int n{};
    vpii edges;
    vvi adj;
    UndirectedGraph() {}
    UndirectedGraph(int n_) {
        assign(n_);
    }
    UndirectedGraph(int n_, const vpii &edges_) {
        build(n_,edges_);
    }
    /*******************************************************************************
     * Clear the graph and assign the number of vertices
     ******************************************************************************/
    void assign(int n_) {
        n = n_;
        edges.clear();
        adj.assign(n,{});
    }
    /*******************************************************************************
     * Build the graph from a list of edges
     ******************************************************************************/
    void build(int n_, const vpii &edges_) {
        assign(n_);
        for (const auto &[u,v] : edges_)
            addEdge(u,v);
    }
    /*******************************************************************************
     * Add an edge and return its index
     ******************************************************************************/
    int addEdge(int u, int v) {
        int id = isz(edges);
        edges.push_back({u,v});
        adj[u].push_back(id);
        adj[v].push_back(id);
        return id;
    }
    /*******************************************************************************
     * Return the opposite endpoint of an edge
     ******************************************************************************/
    int other(int id, int u) const {
        auto [a,b] = edges[id];
        return a ^ b ^ u;
    }
    /*******************************************************************************
     * Run iterative DFS using only edges accepted by allowEdge
     ******************************************************************************/
    SearchResult dfs(int root, auto allowEdge) const {
        SearchResult res;
        res.par.assign(n,-1);
        res.parEdge.assign(n,-1);
        res.dep.assign(n,0);
        vi st{root};
        res.par[root] = root;
        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            res.order.push_back(u);
            for (auto id : adj[u]) {
                if (!allowEdge(id)) continue;
                int v = other(id,u);
                if (res.par[v] != -1) continue;
                res.par[v] = u;
                res.parEdge[v] = id;
                res.dep[v] = res.dep[u]+1;
                st.push_back(v);
            }
        }
        return res;
    }
    /*******************************************************************************
     * Run iterative DFS using all edges
     ******************************************************************************/
    SearchResult dfs(int root = 0) const {
        return dfs(root,[](int) {
            return true;
        });
    }
    /*******************************************************************************
     * Run BFS using only edges accepted by allowEdge
     ******************************************************************************/
    SearchResult bfs(int root, auto allowEdge) const {
        SearchResult res;
        res.par.assign(n,-1);
        res.parEdge.assign(n,-1);
        res.dep.assign(n,0);
        std::queue<int> q;
        res.par[root] = root;
        q.push(root);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            res.order.push_back(u);
            for (auto id : adj[u]) {
                if (!allowEdge(id)) continue;
                int v = other(id,u);
                if (res.par[v] != -1) continue;
                res.par[v] = u;
                res.parEdge[v] = id;
                res.dep[v] = res.dep[u]+1;
                q.push(v);
            }
        }
        return res;
    }
    /*******************************************************************************
     * Run BFS using all edges
     ******************************************************************************/
    SearchResult bfs(int root = 0) const {
        return bfs(root,[](int) {
            return true;
        });
    }
    /*******************************************************************************
     * Build a rooted spanning tree using DFS
     *
     * For a disconnected graph only the component of root is processed.
     ******************************************************************************/
    SpanningTree spanningTree(int root = 0) const {
        auto search = dfs(root);
        SpanningTree tree;
        tree.par = std::move(search.par);
        tree.parEdge = std::move(search.parEdge);
        tree.dep = std::move(search.dep);
        tree.order = std::move(search.order);
        tree.isTreeEdge.assign(isz(edges),0);
        for (auto u : tree.order)
            if (u != root)
                tree.isTreeEdge[tree.parEdge[u]] = 1;
        return tree;
    }
    /*******************************************************************************
     * Count vertices reachable using only edges accepted by allowEdge
     ******************************************************************************/
    int reachableCount(int root, auto allowEdge) const {
        return isz(bfs(root,allowEdge).order);
    }
    /*******************************************************************************
     * Count vertices reachable using all edges
     ******************************************************************************/
    int reachableCount(int root = 0) const {
        return isz(bfs(root).order);
    }
    /*******************************************************************************
     * Check connectivity using only edges accepted by allowEdge
     ******************************************************************************/
    bool connected(auto allowEdge) const {
        return n == 0 || reachableCount(0,allowEdge) == n;
    }
    /*******************************************************************************
     * Check connectivity using all edges
     ******************************************************************************/
    bool connected() const {
        return n == 0 || reachableCount(0) == n;
    }
};
} // namespace graph
} // namespace algos
#endif // __UNDIRECTED_GRAPH_HPP__