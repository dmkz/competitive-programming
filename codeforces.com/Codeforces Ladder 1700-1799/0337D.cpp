/*
    Problem: 337D. Book of Evil
    
    Solution: trees, bfs, diameter, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
const int INF = (int)1e9+7;
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n, m, d; std::cin >> n >> m >> d; ) {
        vvi adj(1+n);
        vi queries(m);
        for (auto &it : queries) { std::cin >> it; }
        for (int i = 1, u, v; i < n; i++) {
            std::cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        auto bfs = [&](int s, vi& dist) {
            std::fill(all(dist), INF);
            std::queue<int> queue;
            queue.push(s);
            dist[s] = 0;
            while (isz(queue) > 0) {
                auto u = queue.front(); queue.pop();
                for (int v : adj[u]) {
                    if (dist[v] > dist[u] + 1) {
                        dist[v] = dist[u] + 1;
                        queue.push(v);
                    }
                }
            }
        };
        int s; vi dist_s(1+n), dist_t(1+n);
        bfs(s = queries.front(), dist_s);
        for (auto u : queries) {
            if (dist_s[u] > dist_s[s]) {
                s = u;
            }
        }
        bfs(s, dist_s);
        int t = s;
        for (auto u : queries) {
            if (dist_s[u] > dist_s[t]) {
                t = u;
            }
        }
        bfs(t, dist_t);
        int answ = 0;
        for (int u = 1; u <= n; u++) {
            answ += dist_s[u] <= d && dist_t[u] <= d;
        }
        std::cout << answ << std::endl;
    }
    return 0;
}