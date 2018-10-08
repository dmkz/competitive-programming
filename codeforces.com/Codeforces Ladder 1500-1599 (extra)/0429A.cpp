/*
    Problem: 429A. Xor-tree
    
    Solution: constructive, trees, xor, dfs, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <functional>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n; std::cin >> n;
    std::vector<std::vector<int>> edges(n);
    for (int i = 1; i < n; ++i) {
        int u, v; std::cin >> u >> v; --u, --v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    std::vector<int> curr(n), need(n), answ;
    for (int i = 0; i < n; ++i) std::cin >> curr[i];
    for (int i = 0; i < n; ++i) std::cin >> need[i];
    std::function<void(int,int,int,int,int)> visit = [&](int u, int p, int d, int fl_odd, int fl_even) {
        int fl = d % 2 == 0 ? fl_even : fl_odd;
        if ((curr[u] ^ fl) != need[u]) {
            answ.push_back(u+1);
            if (d%2==0) fl_even ^= 1; else fl_odd ^= 1;
        }
        for (int v : edges[u]) {
            if (v != p) {
                visit(v, u, d+1, fl_odd, fl_even);
            }
        }
    };
    visit(0, -1, 0, 0, 0);
    std::cout << answ.size() << '\n';
    for (auto& u : answ) std::cout << u << '\n';
    return 0;
}