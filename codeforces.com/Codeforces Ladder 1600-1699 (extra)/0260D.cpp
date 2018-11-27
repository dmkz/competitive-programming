/*
    Problem: 260D. Black and White Tree
    
    Solution: trees, greedy, std::set, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cassert>
#include <set>

struct State {
    int vert, sum;
};

bool operator<(const State &lhs, const State &rhs) {
    return lhs.sum < rhs.sum || (lhs.sum == rhs.sum && lhs.vert < rhs.vert);
}

struct Edge {
    int u, v, cost;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int n;
    while (std::cin >> n) {
        std::vector<int> color(1+n), sum(1+n);
        std::set<State> setW, setB;
        std::vector<Edge> edges;
        for (int i = 1; i <= n; ++i) {
            std::cin >> color[i] >> sum[i];
            if (color[i] == 0) {
                setW.insert(State{i,sum[i]});
            } else {
                setB.insert(State{i,sum[i]});
            }
        }
        while (!setW.empty() || !setB.empty()) {
            if (setW.empty()) {
                assert(setB.size() == 1u);
                assert(setB.begin()->sum == 0);
                setB.erase(setB.begin());
            } else if (setB.empty()) {
                assert(setW.size() == 1u);
                assert(setW.begin()->sum == 0);
                setW.erase(setW.begin());
            } else if (setW.begin()->sum < setB.begin()->sum || 
                (setW.begin()->sum == setB.begin()->sum && setW.size() >= setB.size())) {
                int u = setW.begin()->vert;
                int v = setB.begin()->vert;
                int c = setW.begin()->sum;
                auto it = *setB.begin();
                setB.erase(setB.begin());
                setW.erase(setW.begin());
                it.sum -= c;
                setB.insert(it);
                edges.push_back(Edge{u,v,c});
            } else {
                int u = setW.begin()->vert;
                int v = setB.begin()->vert;
                int c = setB.begin()->sum;
                auto it = *setW.begin();
                setB.erase(setB.begin());
                setW.erase(setW.begin());
                it.sum -= c;
                setW.insert(it);
                edges.push_back(Edge{u,v,c});
            }
        }        
        {   // Check greedy solution:
            std::vector<int> check_sum(1+n);
            for (auto& e : edges) {
                assert(color[e.u] != color[e.v]);
                check_sum[e.u] += e.cost;
                check_sum[e.v] += e.cost;
            }
            assert(check_sum == sum);
        }
        for (auto& e : edges) {
            std::cout << e.u << ' ' << e.v << ' ' << e.cost << '\n';
        }
        std::cout << std::endl;
    }
    return 0;
}