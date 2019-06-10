/*
    Problem: 61D. Eternal Victory
    
    Solution: dynamic programming, trees, dp on trees, dfs, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef long long ll;
const ll INF = (ll)1e18L;
struct Edge { int vert, cost; };
template<typename X, typename Y> X& remin(X& x, const Y& y) { return x = (x < y) ? x : y; }
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int nV; std::cin >> nV; ) {
        std::vector<std::vector<Edge>> adj(1+nV);
        for (int i = 1, u, v, w; i < nV; i++) {
            std::cin >> u >> v >> w;
            adj[u].push_back(Edge{v,w});
            adj[v].push_back(Edge{u,w});
        }
        std::vector<std::vector<ll>> dp(2, std::vector<ll>(1+nV, INF));
        std::function<void(int,int)> dfs = [&](int u, int p) {
            dp[0][u] = 0;
            for (const auto& e : adj[u]) {
                if (e.vert == p) { continue; }
                dfs(e.vert,u);
                dp[0][u] += 2 * e.cost + dp[0][e.vert];
            }
            for (const auto& e : adj[u]) {
                if (e.vert == p) { continue; }
                remin(dp[1][u],dp[0][u] - dp[0][e.vert] - e.cost + dp[1][e.vert]);
            }
            remin(dp[1][u],dp[0][u]);
        };
        dfs(1,0);
        std::cout << dp[1][1] << std::endl;
    }
    return 0;
}