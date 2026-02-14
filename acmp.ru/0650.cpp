// графы, компоненты связности, комбинаторика, O(V+E)
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
using ll = long long;
bool solve() {
    // читаем граф:
    int n, m;
    if (!(std::cin >> n >> m))
        return false;
    ll answ = 0;
    vvi adj(n+1);
    vpii edges;
    for (int i = 0; i < m; i++) {
        int u, v; std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.emplace_back(u, v);
    }
    // находим компоненты связности
    vvi comps; vi idComp(n+1, -1), used(n+1, 0);
    for (int u = 1; u <= n; u++) {
        if (!used[u]) {
            used[u] = 1;
            vi q = {u};
            for (int i = 0; i < isz(q); i++)
                for (int v : adj[q[i]])
                    if (!used[v]) {
                        used[v] = 1;
                        q.push_back(v);
                    }
            comps.push_back(q);
            for (int v : q)
                idComp[v] = isz(comps)-1;
        }
    }
    // считаем рёбра для каждой компоненты:
    vi numEdges(isz(comps));
    for (const auto &[u, v] : edges) {
        int iu = idComp[u], iv = idComp[v];
        assert(iu == iv);
        numEdges[iu]++;
    }
    // теперь каждая компонента - это цикл (nV == nE) или список (nV == nE+1)
    for (int i = 0; i < isz(comps); i++) {
        int nV = isz(comps[i]);
        int nE = numEdges[i];
        if (nV == nE+1) {
            // сумма путей в списке:
            for (int j = 0; j < nV; j++) {
                int last = std::max(0, nV-1 - j - 1);
                answ += last * (last+1LL);
            }
        } else {
            // сумма путей в цикле:
            assert(nV == nE);
            ll curr{};
            for (int j = 0; j < nV; j++) {
                int right = j - 0;
                int left = 0 - (j - nV);
                curr += std::max(0, std::min(left, right)-1);
            }
            answ += curr * 1LL * nV;
        }
    }
    std::cout << answ << std::endl;
    return true;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    while (solve());
}
