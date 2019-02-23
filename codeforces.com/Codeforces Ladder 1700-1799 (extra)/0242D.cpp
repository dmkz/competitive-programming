/*
    Problem: 242D. Dispute
    
    Solution: greedy, graphs, O((n + m) * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <set>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m; 
    while (std::cin >> n >> m) {
        std::vector<std::vector<int>> next(1+n);
        for (int i = 0, u, v; i < m; ++i) {
            std::cin >> u >> v;
            next[u].push_back(v);
            next[v].push_back(u);
        }
        std::vector<int> number(1+n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> number[i];
        }
        std::vector<int> visited(1+n), currValue(1+n), used(1+n);
        std::set<int> queue;
        for (int u = 1; u <= n; ++u) {
            if (currValue[u] == number[u]) {
                queue.insert(u);
            }
        }
        while (!queue.empty()) {
            auto curr = *queue.begin();
            queue.erase(queue.begin());
            visited[curr] = true;
            if (currValue[curr] != number[curr]) {
                continue;
            }
            currValue[curr]++;
            used[curr] = true;
            for (int u : next[curr]) {
                currValue[u]++;
                if (currValue[u] == number[u] && !visited[u]) {
                    queue.insert(u);
                }
            }
        }
        bool ok = true;
        for (int i = 1; i <= n; ++i) {
            ok = ok && (currValue[i] != number[i]);
        }
        if (!ok) {
            std::cout << -1 << std::endl;
            continue;
        }
        std::vector<int> answ;
        for (int i = 1; i <= n; ++i) {
            if (used[i]) { answ.push_back(i); }
        }
        std::cout << answ.size() << "\n";
        for (auto& it : answ) { std::cout << it << ' '; }
        std::cout << '\n';
    }
    return 0;
}