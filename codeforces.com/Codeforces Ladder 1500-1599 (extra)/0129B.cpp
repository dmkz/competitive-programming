/*
    Problem: 129B. Students and Shoelaces
    
    Solution: graphs, implementation, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, m; std::cin >> n >> m;
    std::vector<std::vector<bool>> g(n, std::vector<bool>(n));
    std::vector<int> degree(n);
    for (int i = 0; i < m; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        g[b][a] = g[a][b] = 1;
        degree[a]++;
        degree[b]++;
    }
    int answ = 0;
    while (true) {
        std::queue<int> queue;
        for (int v = 0; v < n; ++v) {
            if (degree[v] == 1) {
                queue.push(v);
            }
        }
        if (queue.empty()) break;
        ++answ;
        while (!queue.empty()) {
            auto u = queue.front(); queue.pop();
            for (int v = 0; v < n; ++v) {
                if (g[u][v] == 1) {
                    g[u][v] = g[v][u] = 0;
                    degree[u]--;
                    degree[v]--;
                }
            }
        }
    }
    std::cout << answ;
    return 0;
}