/*
    Problem: 501C. Misha and Forest
    Solution: trees, dfs, constructive, greedy
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>
struct Edge { int a, b; };
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<int> degree(n), sum(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> degree[i] >> sum[i];
    }
    std::vector<Edge> edges;
    std::function<void(int)> visit = [&](const int curr) {
        assert(degree[curr]==1);
        degree[curr]--;
        const int next = sum[curr];
        edges.push_back(Edge{curr, next});
        sum[next] ^= curr;
        degree[next]--;
        if (degree[next] == 1) {
            visit(next);
        }
    };
    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) visit(i);
    }
    std::cout << edges.size() << '\n';
    for (auto& e : edges) {
        std::cout << e.a << ' ' << e.b << '\n';
    }
    return 0;
}