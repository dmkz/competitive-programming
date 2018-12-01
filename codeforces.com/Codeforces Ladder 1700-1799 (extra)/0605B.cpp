/*
    Problem: 605B. Lazy Student
    
    Solution: MST, contructive, sorting, binary search, O(n*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge {
    int weight, in, id;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    int nV, nE;
    while (std::cin >> nV >> nE) {
        std::vector<Edge> input(nE);
        for (int i = 0; i < nE; ++i) {
            auto &p = input[i]; p.id = i;
            std::cin >> p.weight >> p.in;
        }
        std::sort(input.begin(), input.end(), [](const Edge &a, const Edge& b){
            return a.weight < b.weight || (a.weight == b.weight && (a.in > b.in || (a.in == b.in && a.id < b.id)));
        });
        std::vector<int> nConnected(1+nV), fi(nE), se(nE);
        int used = 1; bool flag = true;
        for (auto &e : input) {
            if (e.in) {
                // connect set of vertices with new vertex
                int u = used;
                int v = ++used;
                fi[e.id] = u;
                se[e.id] = v;
                nConnected[u]++;
            } else {
                // connect two not connected vertices yet:
                int low = 0, high = used;
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (nConnected[mid] == used - mid) {
                        low = mid;
                    } else {
                        high = mid;
                    }
                }
                if (high == used) {
                    flag = false;
                    std::cout << -1 << std::endl;
                    break;
                }
                int u = high, v = u + nConnected[high] + 1;
                assert(v <= used);
                fi[e.id] = u;
                se[e.id] = v;
                nConnected[u]++;
            }
        }
        if (flag) {
            for (int i = 0; i < nE; ++i) {
                std::cout << fi[i] << ' ' << se[i] << "\n";
            }
        }
    }
    return 0;
}