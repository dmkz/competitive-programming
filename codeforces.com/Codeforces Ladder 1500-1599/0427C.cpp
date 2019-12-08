/*
    Problem: 427C. Checkposts
    Solution: dfs, graphs, topological sorting, connected components, O(n+m)
*/
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cassert>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<int> cost(n);
    for (auto& it : cost) std::cin >> it;
    
    std::vector<std::vector<int>> edges(n), reverse(n);
    int m; std::cin >> m;
    while (m--) {
        int a, b; std::cin >> a >> b; --a, --b;
        edges[a].push_back(b);
        reverse[b].push_back(a);
    }
    
    std::vector<int> order;
    {
        std::vector<bool> visited(n);
        std::function<void(int)> visit = [&](const int curr) {
            for (auto& it : edges[curr]) {
                if (!visited[it]) {
                    visited[it] = true;
                    visit(it);
                }
            }
            order.push_back(curr);
        };
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                visited[i] = true;
                visit(i);
            }
        }
        std::reverse(order.begin(), order.end());
    }
    
    std::vector<int> part(n);
    int nParts = 0;
    
    std::function<void(int)> make_component = [&](const int curr) {
        for (auto next : reverse[curr]) {
            if (part[next] == 0) {
                part[next] = part[curr];
                make_component(next);
            }
        }
    };
    
    for (auto it : order) {
        if (part[it] == 0) {
            part[it] = ++nParts;
            make_component(it);
        }
    }
    
    std::vector<int> min(1+nParts, (int)1e9+1), count(1+nParts);
    
    for (int i = 0; i < n; ++i) {
        int p = part[i];
        if (cost[i] < min[p]) {
            min[p] = cost[i];
            count[p] = 1;
        } else if (cost[i] == min[p]) {
            count[p]++;
        }
    }
    
    int64_t sum = 0, vars = 1;
    for (int p = 1; p <= nParts; ++p) {
        sum += min[p];
        vars = vars * count[p] % ((int)1e9+7);
    }
    std::cout << sum << ' ' << vars;
    return 0;
}