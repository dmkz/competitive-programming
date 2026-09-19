#ifndef __EULERTOUR_HPP__
#define __EULERTOUR_HPP__
/*******************************************************************************************
 * The file "EulerTour.hpp" is a part of competitive programming C++ library "algos".      *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "Tree.hpp"
namespace algos {
namespace euler {
// Euler tour of a rooted tree.
// The subtree of vertex u corresponds to the half-interval [tin[u], tout[u]).
template<typename EdgeT = tree::Edge>
struct EulerTour : tree::Tree<EdgeT> {
    using Base = tree::Tree<EdgeT>;
    using Base::Base;
    using Base::dfs;
    std::vector<int> tin, tout, order;
    int timer{};
    EulerTour() = default;
    EulerTour(const Base &tree, int root = 1) : Base(tree) {
        build(root);
    }
    EulerTour(Base &&tree, int root = 1) : Base(std::move(tree)) {
        build(root);
    }
    friend std::istream &operator>>(std::istream &in, EulerTour &tree) {
        return tree.readEdges(true,in);
    }
private:
    void dfsEuler(int u, int p) {
        tin[u] = timer;
        order[timer++] = u;
        for (int id : this->adj[u]) {
            int v = this->edges[id].opp(u);
            if (v != p)
                dfsEuler(v,u);
        }
        tout[u] = timer;
    }
    auto getAccessors() {
        return std::make_tuple(
            [this](int u) { return tin[u]; },
            [this](int u) { return tout[u]; }
        );
    }
public:
    // Builds the Euler tour for the tree already stored in this object.
    auto build(int root = 1) {
        assert(1 <= root && root <= this->n);
        timer = 0;
        tin.assign(this->n+1,-1);
        tout.assign(this->n+1,-1);
        order.assign(this->n,-1);
        dfsEuler(root,0);
        return getAccessors();
    }
    // Copies a base tree and builds its Euler tour.
    auto build(const Base &tree, int root = 1) {
        static_cast<Base&>(*this) = tree;
        return build(root);
    }
    // Moves a base tree and builds its Euler tour.
    auto build(Base &&tree, int root = 1) {
        static_cast<Base&>(*this) = std::move(tree);
        return build(root);
    }
    // Builds a tree from pairs of endpoints and then builds its Euler tour.
    auto build(int n, const std::vector<std::pair<int,int>> &edges, int root = 1) {
        std::vector<EdgeT> converted;
        converted.reserve(edges.size());
        for (const auto &[u,v] : edges)
            converted.push_back(EdgeT{u,v});
        this->setEdges(n,std::move(converted));
        return build(root);
    }
    // Returns true if parent is an ancestor of vertex, including equality.
    bool isParent(int vertex, int parent) const {
        return tin[parent] <= tin[vertex] && tout[vertex] <= tout[parent];
    }
    // Returns the number of vertices in the subtree of u.
    int subtreeSize(int u) const {
        return tout[u]-tin[u];
    }
};
} // namespace euler
} // namespace algos
#endif // __EULERTOUR_HPP__