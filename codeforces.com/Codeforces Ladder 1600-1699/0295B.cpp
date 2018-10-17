/*
    Problem: 295B. Greg and Graph
    
    Solution: graphs, Floyd-Warshall, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

#define remin(x, y) if (x > y) x = y

typedef long long ll;

const int INF = (int)1e9+1;

int main() {
    int n; 
    while (scanf("%d", &n) == 1) {
        std::vector<std::vector<int>> edge(n, std::vector<int>(n));
        for (auto& row : edge) {
            for (auto& it : row) {
                scanf("%d", &it);
            }
        }
        std::vector<int> order(n), added(n);
        for (auto& it : order) { scanf("%d", &it); --it; }
        std::reverse(order.begin(), order.end());
        std::vector<ll> answer;
        std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
        for (int x : order) {
            added[x] = 1;
            // add new edges:
            for (int y = 0; y < n; ++y) {
                if (!added[y]) continue;
                remin(dist[x][y], edge[x][y]);
                remin(dist[y][x], edge[y][x]);
            }
            // relax paths to x:
            for (int u = 0; u < n; ++u) {
                if (!added[u]) continue;
                for (int v = 0; v < n; ++v) {
                    if (!added[v]) continue;
                    remin(dist[v][x], dist[v][u] + dist[u][x]);
                }
            }
            // relax paths from x:
            for (int u = 0; u < n; ++u) {
                if (!added[u]) continue;
                for (int v = 0; v < n; ++v) {
                    if (!added[v]) continue;
                    remin(dist[x][v], dist[x][u] + dist[u][v]);
                }
            }
            // relax paths through x:
            for (int u = 0; u < n; ++u) {
                if (!added[u]) continue;
                for (int v = 0; v < n; ++v) {
                    if (!added[v]) continue;
                    remin(dist[u][v], dist[u][x] + dist[x][v]);
                }
            }
            // calculate answer:
            ll sum = 0;
            for (int u = 0; u < n; ++u) {
                if (!added[u]) continue;
                for (int v = 0; v < n; ++v) {
                    if (!added[v]) continue;
                    assert(dist[u][v] < INF);
                    sum += dist[u][v];
                }
            }
            answer.push_back(sum);
        }
        std::reverse(answer.begin(), answer.end());
        for (auto& it : answer) printf("%lld ", it);
        printf("\n");
    }
    return 0;
}