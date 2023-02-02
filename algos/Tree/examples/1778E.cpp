/*
    problem: 1778E. The Tree Has Fallen!
    solution: euler tour, trees, dfs, segment tree, xor basis, maximum xor
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("fma")
#include "template.hpp"
#include "segmenttree.hpp"
#include "algebra.hpp"
#include "tree.hpp"
using namespace algos::tree;
using namespace algos::SegmentTree;
using namespace algos::algebra;
int main() {
    int tt; std::cin >> tt;
    while (tt--) {
        int n; std::cin >> n;
        vi a(n); std::cin >> a;
        vpii edges(n-1);
        for (auto &[u,v] : edges)
            std::cin >> u >> v;
        // building euler tour over a tree:
        EulerTour euler;
        auto [tin, tout] = euler.build(n, edges);
        // building LCA for a tree:
        BinaryJumps lca;
        lca.build(n, edges);
        // building segment tree over euler tour
        // now each subtree is a segment of array
        using Basis = XorBasis<int>;
        SegmentTree<Basis, TraitsSumSet<Basis>> segtree;
        {
            std::vector<Basis> data(n);
            for (int u = 1; u <= n; u++)
                data[tin(u)] = a[u-1];
            segtree.build(data);
        }
        int q; std::cin >> q;
        while (q--) {
            int r, v; std::cin >> r >> v;
            if (r == v) {
                // we can take all of the numbers
                std::cout << segtree.get(0, n-1).max() << '\n';
            } else if (euler.isParent(r,v)) {
                // we can take all of the numbers, except subtree of child on path v-r:
                int child = lca.directChild(r,v);
                std::cout << (segtree.get(0, tin(child)-1)+
                              segtree.get(tout(child)+1,n-1)).max() << '\n';
            } else {
                // we can take only a substree of v:
                std::cout << segtree.get(tin(v),tout(v)).max() << '\n';
            }
        }
    }
}
