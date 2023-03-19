#ifndef __HLD_HPP__
#define __HLD_HPP__

namespace algos {
namespace hld {
struct HLD {
    
    vi sz, par, id, pos;
    vvi vert;
    int lastPath{};
    HLD(){}
    HLD(int n, const vvi &adj, int root = 1) { build(n, adj, root); }
    void build(int n, const vvi &adj, int root = 1) {
        sz.assign(n+1, 0);
        par.assign(n+1, 0);
        id.assign(n+1, 0);
        pos.assign(n+1, 0);
        vert.assign(n+1,{});
        lastPath = 0;
        calcSize(root,0,adj);
        dfs(root,0,adj);
    }
    int nPaths() const {
        return lastPath+1;
    }
    int calcSize(int u, int p, const vvi &adj) {
        par[u] = p;
        for (int v : adj[u])
            if (v != p)
                sz[u] += calcSize(v, u, adj);
        return ++sz[u];
    }
    void dfs(int u, int p, const vvi &adj) {
        vert[id[u]].push_back(u);
        int mx = -1;
        for (int v : adj[u]) {
            if (v == p) continue;
            if (mx == -1 || sz[mx] < sz[v])
                mx = v;
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            if (mx == v) {
                // same path
                id[v] = id[u];
                pos[v] = pos[u] + 1;
            } else {
                // new path
                id[v] = ++lastPath;
                pos[v] = 0;
            }
            dfs(v,u,adj);
        }
    }
    pii posOf(int u) const { return {id[u], pos[u]}; }
    int goUp(int u, int delta) const {
        while (delta > 0) {
            auto [iu,pu] = posOf(u);
            if (delta <= pu) {
                // step during single path
                u = vert[iu][pu-delta];
                break;
            } else {
                // switch path
                delta -= pu + 1;
                u = par[vert[iu][0]];
            }
        }
        return u;
    }
};
} // namespace hld
} // namespace algos
#endif // __HLD_HPP__