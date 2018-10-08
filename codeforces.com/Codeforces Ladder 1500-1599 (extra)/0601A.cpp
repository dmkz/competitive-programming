/*
    Problem: 601A. The Two Routes
    
    Solution: graphs, bfs, constructive, O(n^2 + m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <cassert>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int nVert, nEdges;
    std::cin >> nVert >> nEdges;
    vvi g(nVert, vi(nVert,2));
    for (int i = 0; i < nEdges; ++i) {
        int u, v; std::cin >> u >> v; --u, --v;
        g[u][v] = g[v][u] = 1;
    }
    for (int u = 0; u < nVert; ++u) {
        g[u][u] = 0;
    }
    std::function<int(int,int,int)> bfs = [&](int s, int f, int color) {
        vi dist(nVert, -1);
        dist[s] = 0;
        
        std::queue<int> queue;
        queue.push(s);
        
        while (!queue.empty()) {
            auto curr = queue.front(); queue.pop();
            for (int next = 0; next < nVert; ++next) {
                if (g[curr][next] == color && dist[next] == -1) {
                    dist[next] = dist[curr]+1;
                    queue.push(next);
                }
            }
        }
        return dist[f];
    };
    std::cout << bfs(0, nVert-1, 3-g[0][nVert-1]);
    return 0;
}