#include <bits/stdc++.h>
#include "FastIO.hpp"

struct Edge { int u, v; };
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Edge> ve;
bool check(const int nOrg, int lim, const ve& edges, const vvi& adj, vi& answ) {
    std::function<void(int,int,int)> visit = [&](int u, int p, int last) {
        int color = 0; bool bad = false;
        for (int id : adj[u]) {
            const int v = edges[id].u + edges[id].v - u;
            if (v == p) { continue; }
            if (!bad) {
                color++;
                color += (color == last);
            }
            if (color > nOrg) { lim--; bad = true; color = 1; }
            visit(v,u,answ[id] = color);
        }
    };
    visit(1,0,0);
    return (lim >= 0);
}
int main() {
    FastIO::Reader fin;
    FastIO::Writer fout;
    for (int n, k; fin >> n >> k; fout << '\n') {
        // Input tree:
        ve edges(n);
        vvi adj(1+n);
        vi answ(n-1);
        for (int i = 0; i < n-1; ++i) {
            auto &it = edges[i];
            fin >> it.u >> it.v;
            adj[it.u].push_back(i);
            adj[it.v].push_back(i);
        }
        // Binary search
        int low = 0, high = n;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            if (check(mid, k, edges, adj, answ)) { high = mid; }
            else { low = mid; }
        }
        assert(check(high,k,edges,adj,answ));
        fout << high << '\n';
        for (auto it : answ) { fout << it << ' '; }
        fout << '\n';
    }
    return 0;
}