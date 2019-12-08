/*
    Problem: 437C. The Child and Toy
    Solution: graphs, greedy
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cost(n);
    for (auto& it : cost) std::cin >> it;
    std::vector<std::vector<bool>> g(n,std::vector<bool>(n));
    while (m--) {
        int a, b; std::cin >> a >> b; --a, --b;
        g[a][b] = g[b][a] = 1;
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int curr = int(std::max_element(cost.begin(), cost.end())-cost.begin());
        cost[curr] = 0;
        for (int next = 0; next < n; ++next) {
            if (!g[curr][next]) continue;
            sum += cost[next];
            g[curr][next] = g[next][curr] = 0;
        }
    }
    std::cout << sum;
    return 0;
}
