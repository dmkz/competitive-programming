#ifndef __DSU_HPP__
#define __DSU_HPP__
namespace algos
{
namespace dsu
{
    struct DSU {
        vi par, sz;
        DSU(int n) : par(n), sz(n,1)
        {
            for (int i = 0; i < n; i++)
                par[i] = i;
        }
        int getPar(int u) {
            return par[u] == u ? u : par[u] = getPar(par[u]);
        }
        void connect(int u, int v) {
            u = getPar(u);
            v = getPar(v);
            if (u == v) return;
            if(sz[u] < sz[v]) std::swap(u,v);
            sz[u] += sz[v];
            par[v] = u;
        }
        bool isConnected(int u, int v) {
            return getPar(u) == getPar(v);
        }
    }; // class DSU
} // namespace dsu
} // namespace algos
#endif // __DSU_HPP__