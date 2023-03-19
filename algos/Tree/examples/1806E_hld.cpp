#include "template.hpp"
#include "fastio.hpp"
#include "tree.hpp"
#include "hld.hpp"
using namespace algos::tree;
using namespace algos::hld;
__attribute__((optimize("Ofast,unroll-loops"),target("avx2")))
ll dotProd(const int * __restrict a,
           const int * __restrict b,
           const int len)
{
    ll res{};
    for (int i = 0; i < len; i++)
        res += (ll)a[i] * b[i];
    return res;
}
__attribute__((optimize("Ofast,unroll-loops"),target("avx2")))
ll dotProdSelf(const int * __restrict a,
               const int len)
{
    ll res{};
    for (int i = 0; i < len; i++)
        res += (ll)a[i] * a[i];
    return res;
}
int main() {
    FastIO::Reader cin;
    FastIO::Writer cout;
    int n, q; cin >> n >> q;
    vi a(n+1, n);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    vi par(n+1);
    for (int i = 2; i <= n; i++)
        cin >> par[i];
    // building HLD:
    auto adj = par2adj(n, par);
    HLD hld(n, adj, 1);
    // placing values of each vertex on their path:
    vvi data(hld.nPaths());
    for (int id = 0; id < hld.nPaths(); id++) {
        data[id].resize(hld.vert[id].size());
        for (int i = 0; i < isz(data[id]); i++) {
            int u = hld.vert[id][i];
            data[id][i] = a[u];
        }
    }
    auto solve = [&](int u, int v)
    {
        ll res = 0;
        // non-common part of sum:
        while (hld.id[u] != hld.id[v]) {
            if (hld.pos[u] > hld.pos[v])
                std::swap(u, v);
            auto [iu,pu] = hld.posOf(u);
            auto [iv,pv] = hld.posOf(v);
            // dot product between two parts of paths:
            res += dotProd(&data[iu][0], &data[iv][pv-pu], pu+1);
            // go up:
            u = hld.goUp(u, pu+1);
            v = hld.goUp(v, pu+1);
        }
        // common part of sum:
        while (u) {
            auto [iu,pu] = hld.posOf(u);
            res += dotProdSelf(&data[iu][0], pu+1);
            u = hld.goUp(u, pu+1);
        }
        return res;
    };
    while (q --> 0) {
        int x, y; cin >> x >> y;
        cout << solve(x, y) << '\n';
    }
}
