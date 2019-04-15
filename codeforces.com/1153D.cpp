/*
    Problem: 1153D. Serval and Rooted Tree
    
    Solution: greedy, dynamic programming, trees, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    for (int n; std::cin >> n; ) {
        std::vector<int> op(1+n);
        for (int i = 1; i <= n; ++i) { std::cin >> op[i]; }
        std::vector<std::vector<int>> next(1+n);
        for (int i = 2, p; i <= n; ++i) {
            std::cin >> p; next[p].push_back(i);
        }
        std::vector<int> nLeafs(1+n);
        std::function<void(int)> dfs = [&](int u) {
            for (int v : next[u]) {
                dfs(v);
                nLeafs[u] += nLeafs[v];
            }
            nLeafs[u] += (next[u].empty());
        };
        dfs(1);
        std::vector<int> max(1+n);
        std::function<void(int)> dp = [&](int u) {
            if (next[u].empty()) {
                max[u] = 1;
                return;
            }
            
            for (int v : next[u]) { dp(v); }
            
            if (op[u] == 1) { // max
                max[u] = INT_MIN;
                for (int v : next[u]) {
                    max[u] = std::max(max[u], max[v] + nLeafs[u] - nLeafs[v]);
                }
            } else { // min
                max[u] = 1;
                for (int v : next[u]) {
                    max[u] += max[v] - 1;
                }
            }
        };
        dp(1);
        std::cout << max[1] << std::endl;
    }
    return 0;
}