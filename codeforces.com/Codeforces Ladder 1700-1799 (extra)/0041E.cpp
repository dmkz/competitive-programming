/*
    Problem: 41E. 3-cycles
    
    Solution: graphs, cycles, constructive, O(n^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

struct Edge {int u, v; };

int main() {
    int n;
    while (std::cin >> n) {
        std::vector<Edge> answ;
        for (int i = 2; i <= n; ++i) {
            for (int j = i-1; j >= 1; j -= 2) {
                answ.push_back(Edge{j,i});
            }
        }
        std::cout << answ.size() << "\n";
        for (auto &e : answ) {
            std::cout << e.u << ' ' << e.v << '\n';
        }
        std::cout << std::endl;
    }
    return 0;
}