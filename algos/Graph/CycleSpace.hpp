#ifndef __CYCLE_SPACE_HPP__
#define __CYCLE_SPACE_HPP__
/*******************************************************************************************
 * The file "CycleSpace.hpp" is a part of competitive programming C++ library "algos".     *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "UndirectedGraph.hpp"
namespace algos {
namespace graph {
/*******************************************************************************
 * CycleSpace - fundamental cycle basis of a connected undirected graph
 *
 * Each basis element is represented by a list of edge indices.
 * Every Eulerian edge set is a symmetric difference of basis elements.
 * The dimension of the cycle space is m-n+1.
 ******************************************************************************/
struct CycleSpace {
    vvi basis;
    CycleSpace() {}
    CycleSpace(const UndirectedGraph &g, int root = 0) {
        build(g,root);
    }
    /*******************************************************************************
     * Build the fundamental cycle basis using a DFS spanning tree
     ******************************************************************************/
    void build(const UndirectedGraph &g, int root = 0) {
        auto tree = g.spanningTree(root);
        basis.clear();
        for (int id = 0; id < isz(g.edges); id++) {
            if (tree.isTreeEdge[id]) continue;
            auto [u,v] = g.edges[id];
            vi curr{id};
            while (tree.dep[u] > tree.dep[v]) {
                curr.push_back(tree.parEdge[u]);
                u = tree.par[u];
            }
            while (tree.dep[v] > tree.dep[u]) {
                curr.push_back(tree.parEdge[v]);
                v = tree.par[v];
            }
            while (u != v) {
                curr.push_back(tree.parEdge[u]);
                curr.push_back(tree.parEdge[v]);
                u = tree.par[u];
                v = tree.par[v];
            }
            basis.push_back(std::move(curr));
        }
    }
    /*******************************************************************************
     * Return the dimension of the cycle space
     ******************************************************************************/
    int dimension() const {
        return isz(basis);
    }
};
} // namespace graph
} // namespace algos
#endif // __CYCLE_SPACE_HPP__