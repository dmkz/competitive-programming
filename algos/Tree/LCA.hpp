#ifndef __LCA_HPP__
#define __LCA_HPP__
#include "sparsetable.hpp"

namespace algos {
namespace lca {

struct LCA {
    const int INF = (int)1e9+7;
    vi pos, pf, dep;
    vpii euler;
    algos::SparseTable::SparseTable<pii, algos::SparseTable::Min<pii>> st;

    void eulerwalk(int u, int p, const vvi &adj) {
        dep[u] = dep[p]+1;
        pos[u] = std::min(pos[u], isz(euler));
        pf.push_back(+1);
        euler.push_back({dep[u],u});
        for (int v : adj[u]) {
            if (v != p) {
                eulerwalk(v, u, adj);
                euler.push_back({dep[u],u});
                pf.push_back(-1);
            }
        }
    }
    
    void build(int nV, const vpii & edges, int root) {
        vvi adj(nV+1);
        for (auto &[u,v] : edges)
            adj[u] << v, adj[v] << u;
        build(nV, adj, root);
    }

    void build(int nV, const vvi & adj, int root) {
        pos.assign(1+nV, INF);
        dep.assign(1+nV, 0);
        euler.clear();
        pf.clear();
        eulerwalk(root, 0, adj);
        for (int i = isz(pf)-2; i >= 0; i--)
            pf[i] += pf[i+1];
        st.build(euler);
    }
    int lca_from_poses(int u, int v) const {
        if (u > v) std::swap(u, v);
        return st(u,v).second;
    }
    int lca(int u, int v) const {
        return lca_from_poses(pos[u],pos[v]);
    }
    int dist_from_poses(int u, int v) const {
        int p = pos[lca_from_poses(u,v)];
        return pf[p] - pf[u] + pf[p] - pf[v];
    }
    int dist(int u, int v) const {
        return dist_from_poses(pos[u], pos[v]);
    }
};
} // namespace lca
} // namespace algos
#endif // __LCA_HPP__