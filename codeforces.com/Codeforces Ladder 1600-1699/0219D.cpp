/*
    Problem: 219D. Choosing Capital for Treeland
    
    Solution: Trees, DFS, dynamic programming, O(n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <functional>

const int UP = 0, DOWN = 1;

struct Edge {
    int v, type;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; 
    while (std::cin >> n) {
        std::vector<std::vector<Edge>> edges(1+n);
        for (int i = 0; i < n-1; ++i) {
            int s, f; std::cin >> s >> f;
            edges[s].push_back(Edge{f, DOWN});
            edges[f].push_back(Edge{s, UP});
        }
        int nUpAll = 0;
        std::function<void(int,int)> dfs = [&](int u, int p) {
            for (auto& e : edges[u]) {
                if (e.v == p) continue;
                nUpAll += (e.type == UP);
                dfs(e.v, u);
            }
        };
        dfs(1, 0);
        int best = n-1; std::vector<int> answ;
        std::function<void(int,int,int,int)> calc = [&](int u, int p, int nUp, int nDown) {
            if (nUpAll - nUp + nDown < best) {
                best = nUpAll - nUp + nDown;
                answ.clear();
            }
            if (nUpAll - nUp + nDown == best) {
                answ.push_back(u);
            }
            for (auto& e : edges[u]) {
                if (e.v == p) continue;
                calc(e.v, u, (e.type == UP) + nUp, (e.type == DOWN) + nDown);
            }
        };
        calc(1,0,0,0);
        std::sort(answ.begin(), answ.end());
        std::cout << best << "\n";
        for (auto& it : answ) std::cout << it << ' ';
        std::cout << std::endl;
    }
    return 0;
}