/*
    Problem: 208C. Police Station
    
    Solution: graphs, bfs, shortest paths, dynamic programming, combinatorics, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <queue>

typedef long double Real;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;
typedef std::vector<Real> vr;

const int INF = (int)1e9+7;

vi calc_dist_from(const int n, const int s, const vvi& g) {
    vi dist(1+n, INF);
    std::queue<int> queue;
    dist[s] = 0;
    queue.push(s);
    while (!queue.empty()) {
        auto u = queue.front(); queue.pop();
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] && dist[v] == INF) {
                dist[v] = dist[u] + 1;
                queue.push(v);
            }
        }
    }
    return dist;
}

vr number_of_paths(const int n, const int s, const int t, const vvi& g) {
    vi distFromT = calc_dist_from(n, t, g);
    std::queue<int> queue;
    vr answ(1+n);
    vi used(1+n);
    queue.push(s), answ[s] = 1, used[s] = true;
    while (!queue.empty()) {
        auto u = queue.front(); queue.pop();
        for (int v = 1; v <= n; ++v) {
            if (g[u][v] && distFromT[u] - distFromT[v] == 1) {
                answ[v] += answ[u];
                if (!used[v]) {
                    queue.push(v);
                    used[v] = true;
                }
            }
        }
    }
    return answ;
}

int main() {
    std::cout << std::fixed << std::setprecision(6);
    int n, m;
    while (std::cin >> n >> m) {
        vvi g(1+n, vi(1+n));
        while (m--) {
            int u, v; std::cin >> u >> v;
            g[u][v] = g[v][u] = 1;
        }
        vr  left = number_of_paths(n, 1, n, g);
        vr right = number_of_paths(n, n, 1, g);
        Real answ = 1;
        for (int u = 2; u < n; ++u) {
            answ = std::max(answ, 2 * left[u] * right[u] / right[1]);
        }
        std::cout << answ << std::endl;
    }
    return 0;
}