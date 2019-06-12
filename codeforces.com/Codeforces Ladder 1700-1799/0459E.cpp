/*
    Problem: 459E. Pashmak and Graph
    
    Solution: dynamic programming, graphs, topological sorting, O(V * log(V))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
template<typename X, typename Y>
int lowpos(const X& x, const Y& y) {
    return int(std::lower_bound(all(x), y) - x.begin());
}
const int INF = (int)1e9+7;
struct Edge {
    int vert, cost;
};
bool operator<(const Edge& a, const Edge& b) {
    return a.cost < b.cost || (a.cost == b.cost && a.vert < b.vert);
}
int main() {
	std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int nV, nE; std::cin >> nV >> nE; ) {
        std::vector<std::vector<Edge>> edges(1+nV);
        std::vector<std::vector<int>> dp(1+nV);
        for (int i = 0, u, v, d; i < nE; i++) {
            std::cin >> u >> v >> d;
            edges[u].push_back({v,d});
        }
        for (int u = 1; u <= nV; u++) {
            std::sort(all(edges[u]));
            dp[u].assign(isz(edges[u]),-INF);
            dp[u].push_back(0);
        }
        std::function<int(int,int)> dfs = [&](int u, int id) {
            if (id + 1 < isz(dp[u]) && dp[u][id+1] == -INF) {
                dfs(u, id+1);
            }
            if (dp[u][id] == -INF) {
                dp[u][id] = dp[u][id+1];
                auto cost = edges[u][id].cost;
                auto vert = edges[u][id].vert;
                auto it = lowpos(edges[vert], Edge{0, cost+1});
                dp[u][id] = std::max(dp[u][id], dfs(vert, it) + 1);
            }
            return dp[u][id];
        };
        int answ = 0;
        for (int u = 1; u <= nV; u++) {
            for (int id = isz(edges[u])-1; id >= 0; --id) {
                if (dp[u][id] == -INF) {
                    dfs(u, id);
                }
                answ = std::max(dp[u][id], answ);
            }
        }
        std::cout << answ << std::endl;
    }
	return 0;
}