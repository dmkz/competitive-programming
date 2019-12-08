/*
    Problem: 369C. Valera and Elections
    Solution: graphs, trees, dfs
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

struct Edge {
    int vert, type;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<std::vector<Edge>> edges(n);
    for (int i = 0; i < n-1; ++i) {
        int a, b, t;
        std::cin >> a >> b >> t; --a, --b;
        edges[a].push_back(Edge{b,t});
        edges[b].push_back(Edge{a,t});
    }
    
    std::vector<int> answ;
    
    std::function<bool(int,int,int)> visit = [&](int curr, int parent, int type) {
        bool flag = false;
        for (auto& e : edges[curr]) {
            if (e.vert != parent) {
                auto res = visit(e.vert, curr, e.type);
                flag = res || flag;
            }
        }
        if (!flag && type == 2) {
            answ.push_back(curr+1);
            flag = true;
        }
        return flag;
    };
    
    visit(0, -1, 1);
    std::sort(answ.begin(), answ.end());
    std::cout << answ.size() << '\n';
    for (auto& it : answ) {
        std::cout << it << ' ';
    }
    return 0;
}