/*
    Problem: 1187E. Tree Painting
    Solution: dfs, dynamic programming, trees, O(n)
*/
#include <bits/stdc++.h>
typedef long long ll;
namespace Solution {
    int n; ll answ;
    std::vector<std::vector<int>> adj;
    std::vector<ll> sz, dp;
    bool input() {
        bool flag = bool(std::cin >> n);
        if (!flag) return false;
        adj.assign(1+n, {});
        sz.assign(1+n, 0);
        dp.assign(1+n, 0);
        for (int i = 0, u, v; i < n-1; i++) {
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return flag;
    }
    ll dfs_sz(int u, int p) {
        sz[u] = 1;
        for (int v : adj[u]) {
            if (v == p) continue;
            sz[u] += dfs_sz(v,u);
        }
        return sz[u];
    }
    ll dfs_dp(int u, int p) {
        dp[u] = sz[u];
        for (int v : adj[u]) {
            if (v == p) continue;
            dp[u] += dfs_dp(v, u);
        }
        return dp[u];
    }
    void brute(int u, int p) {
        answ = std::max(answ, dp[u]);
        for (int v : adj[u]) {
            if (v == p) continue;
            auto new_sz_u = sz[u] - sz[v];
            auto new_dp_u = dp[u] - dp[v] - sz[u] + new_sz_u;
            dp[v] -= sz[v];
            dp[v] += n + new_dp_u;
            sz[v] = n;
            brute(v,u);
        }
    }
    ll solve() {
        answ = 0;
        dfs_sz(1,0);
        dfs_dp(1,0);
        brute(1,0);
        return answ;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    while (Solution::input()) {
        std::cout << Solution::solve() << '\n';
    }
    return 0;
}