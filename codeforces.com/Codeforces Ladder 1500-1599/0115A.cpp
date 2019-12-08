/*
    Problem: 115A. Party
    Solution: dfs, graphs, trees
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<std::vector<int>> edges(1+n);
    std::vector<int> height(1+n);
    for (int i = 1; i <= n; ++i) {
        int p; std::cin >> p;
        if (p != -1) {
            edges[p].push_back(i);
        }
    }
    std::function<int(int)> visit = [&](int cur) {
        if (!height[cur]) {
            for (auto& it : edges[cur]) {
                height[cur] = std::max(height[cur], visit(it)+1);
            }
        }
        if (!height[cur]) height[cur] = 1;
        return height[cur];
    };
    int answ = 0;
    for (int i = 1; i <= n; ++i) {
        answ = std::max(answ, visit(i));
    }
    std::cout << answ;
    return 0;
}