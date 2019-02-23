/*
    Problem: 1118F2. Tree Cutting (Hard Version)
    
    Solution: dfs, trees, dynamic programming on trees, O(n * log(mod))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int mod = 998244353;
int add(int a, int b) { return (a += b) >= mod ? (a -= mod) : a; }
int mul(int a, int b) { return int(1LL * a * b % mod); }
int pow(int a, int n) {
    if (a < 2) { return a; }
    int r = 1;
    while (n > 0) {
        if (n & 1) { r = mul(r, a); }
        n >>= 1; a = mul(a, a);
    }
    return r;
}
int inverse(int a) { return pow(a, mod-2); }

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n, k;
    while (std::cin >> n >> k) {
        // Input tree and colors
        // color[u] = given color of vertix `u`
        // cnt[c] = number of unvisited vertices with color `c`
        vi color(1+n), cnt(1+k); 
        for (int i = 1; i <= n; ++i) {
            std::cin >> color[i];
            cnt[color[i]]++;
        }
        vvi adj(1+n); // adj[u] = list of adjacent to vertex `u` vertices
        for (int i = 1, u, v; i < n; ++i) {
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // Firstly we need to connect each equal colors to single component, if we can
        int answ = 1;
        std::function<void(int,int)> connectComponents = [&](int u, int p) {
            for (int v : adj[u]) {
                if (v == p) { continue; }
                connectComponents(v, u);
            }
            if (color[u] == 0 || cnt[color[u]] == 1 || p == 0) { return; }
            if (color[p] == 0) { color[p] = color[u]; return; }
            if (color[p] != color[u]) { answ = 0; return; }
            if (color[u] == color[p]) { cnt[color[u]]--; return; }
        };
        connectComponents(1,0);
        if (!answ) { std::cout << 0 << std::endl; continue; }
        // We need to solve problem for each single uncolored components 
        // separatelly and then multiply answers
        // colored components - leafs of trees
        // nWays[0][u] - number of ways to choose 0 colored vertices from subtree of vertex `u`
        // nWays[1][u] - number of ways to choose 1 colored vertex from subtree of vertex `u`
        vvi nWays(2, vi(1+n)); 
        vi visited(1+n);
        std::function<void(int,int)> solve = [&](int u, int p) {
            if (visited[u]) { return; }
            visited[u] = true;
            if (color[u] != 0) { 
                nWays[0][u] = 0;
                nWays[1][u] = 1;
                return;
            }
            // nWays[0][u] = product(nWays[0][v] + nWays[1][v]
            // where `v` - child of `u`
            int prod = 1, sum = 0;
            for (int v : adj[u]) {
                if (v == p) { continue; }
                solve(v, u);
                prod = mul(prod, add(nWays[0][v], nWays[1][v]));
            }
            nWays[0][u] = prod;
            // nWays[1][u] = sum(prod / (nWays[0][v] + nWays[1][v]) * nWays[1][v])
            // where `v` - child of `u`
            for (int v : adj[u]) {
                if (v == p) { continue; }
                sum = add(sum, mul(mul(prod, inverse(add(nWays[0][v], nWays[1][v]))), nWays[1][v]));
            }
            nWays[1][u] = sum;
        };
        for (int u = 1; u <= n; ++u) {
            if (color[u] == 0 && !visited[u]) {
                solve(u, 0);
                answ = mul(answ, nWays[1][u]);
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}