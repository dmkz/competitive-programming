/*
    Задача: 826. Жизнь цвета индиго
    
    Решение: динамическое программирование, деревья, поиск в глубину, O(n)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
struct Tree {
    int n;
    vvi adj, can, max;
    vi vis;
    Tree(int n_ = 0) : n(n_) {
        vis.resize(n+1);
        adj.resize(n+1);
        can.assign(n+1, vi{0,0,0});
        max.assign(n+1, vi{0,0,0});
    }
    void add_edge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void set_vert(int u, std::string s) {
        // I->0, B->1, V->2
        for (auto it : s) {
            if (it == 'I') { can[u][0] = 1; }
            if (it == 'B') { can[u][1] = 1; }
            if (it == 'V') { can[u][2] = 1; }
        }
    }
    void dfs(int u, int p) {
        if (vis[u]) { return; }
        vis[u] = true;
        for (int v : adj[u]) {
            if (v != p) { dfs(v,u); }
        }
        for (int i = 0; i < 3; ++i) {
            int sum = 0;
            for (int v : adj[u]) {
                int mx = 0;
                if (v == p) { continue; }
                bool temp = false;
                for (int j = 0; j < 3; ++j) {
                    if (i == j || !can[v][j]) { continue; }
                    temp = true;
                    mx = std::max(mx, max[v][j]);
                }
                can[u][i] = can[u][i] && temp;
                sum += mx;
            }
            if (can[u][i]) {
                max[u][i] = (i == 0) + sum;
            }
        }
    }
    int solve() {
        dfs(1,0);
        for (int u = 1; u <= n; ++u) {
            assert(vis[u]);
        }
        int ret = -1;
        for (int i = 0; i < 3; ++i) {
            if (!can[1][i]) { continue; }
            ret = std::max(ret, max[1][i]);
        }
        return ret;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        Tree tree(n);
        for (int i = 1, u, v; i < n; ++i) {
            std::cin >> u >> v;
            tree.add_edge(u,v);
        }
        std::string s;
        for (int i = 1; i <= n; ++i) {
            std::cin >> s;
            tree.set_vert(i, s);
        }
        std::cout << tree.solve() << std::endl;
    }
    return 0;
}