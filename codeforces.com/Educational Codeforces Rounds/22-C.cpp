/*
    Problem: 813C. The Tag Game
    
    Solution: dfs, trees, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

std::vector<int> dfs(int root, const std::vector<std::vector<int>>& edges) {
    const int n = (int)edges.size();
    std::vector<int> dist(n, -1);
    std::function<void(int)> visit = [&](const int vert) {
        for (int next : edges[vert]) {
            if (dist[next] == -1) {
                dist[next] = dist[vert]+1;
                visit(next);
            }
        }
    };
    dist[root] = 0;
    visit(root);
    return dist;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n, x; std::cin >> n >> x; --x;
    std::vector<std::vector<int>> edges(n);
    for (int i = 1; i < n; ++i) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    
    auto dist_a = dfs(0, edges);
    auto dist_b = dfs(x, edges);
    int max = 0;
    for (int i = 0; i < n; ++i) {
        if (dist_b[i] < dist_a[i]) {
            max = std::max(max, 2*dist_a[i]);
        }
    }
    std::cout << max;
    return 0;
}