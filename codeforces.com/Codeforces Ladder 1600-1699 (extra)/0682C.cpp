/*
    Problem: 682C. Alyona and the Tree
    
    Solution: trees, dfs, greedy, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

typedef long long ll;
typedef std::vector<int> vi;

const ll INF = (ll)1e18L;

struct Edge {
    int vert, cost;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        vi arr(1+n);
        for (int i = 1; i <= n; ++i) {
            std::cin >> arr[i];
        }
        std::vector<std::vector<Edge>> edges(1+n);
        for (int u = 2, p, c; u <= n; ++u) {
            std::cin >> p >> c;
            edges[p].push_back(Edge{u, c});
        }
        vi size(1+n);
        std::function<void(int)> calc_size = [&](int u) {
            size[u] = 1;
            for (auto& e : edges[u]) {
                calc_size(e.vert);
                size[u] += size[e.vert];
            }
        };
        calc_size(1);
        int answ = 0;
        std::function<void(int,ll)> solve = [&](int u, ll max) {
            if (arr[u] < max) {
                answ += size[u];
            } else {
                for (auto& e : edges[u]) {
                    solve(e.vert, std::max(max+e.cost, (ll)e.cost));
                }
            }
        };
        solve(1, -INF);
        std::cout << answ << std::endl;
    }
    return 0;
}