/*
    Problem: 321C. Ciel the Commander
    
    Solution: trees, centroid decomposition, dfs, constructive, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
namespace Tree {
    int n;
    vvi adj;
    vi used,size;
    std::string answ;
    void init(int n_) {
        n = n_;
        adj.assign(n+1,{});
        used.assign(n+1,false);
        size.assign(n+1,0);
        answ.assign(n+1,'?');
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int dfs_size(int u, int p) {
        size[u] = 1;
        for (int v : adj[u]) {
            if (used[v] || v == p) { continue; }
            size[u] += dfs_size(v,u);
        }
        return size[u];
    }
    int dfs_centroid(int u, int p, int s) {
        for (int v : adj[u]) {
            if (v == p || used[v]) { continue; }
            if (size[v] > s / 2) { return dfs_centroid(v,u,s); }
        }
        return u;
    }
    void solve(int root, char level) {
        int subTreeSize = dfs_size(root, 0);
        int centroid = dfs_centroid(root, 0, subTreeSize);
        used[centroid] = true;
        answ[centroid] = level;
        for (int v : adj[centroid]) {
            if (!used[v]) {
                solve(v, level+1);
            }
        }
    }
}
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        Tree::init(n);
        while (--n) {
            int u, v; std::cin >> u >> v;
            Tree::add_edge(u,v);
        }
        Tree::solve(1,'A');
        for (int u = 1; u <= Tree::n; u++) {
            std::cout << Tree::answ[u] << ' ';
        }
        std::cout << std::endl;
    }
    return 0;
}