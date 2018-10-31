/*
    Problem: 216B. Forming Teams
    
    Solution: greedy, graphs, dfs, cycles, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int nV, nE;
    while (std::cin >> nV >> nE) {
        vvi next(1+nV);
        for (int i = 0, u, v; i < nE; ++i) {
            std::cin >> u >> v;
            next[u].push_back(v);
            next[v].push_back(u);
        }
        vi color(1+nV); 
        bool isCycle; int partSize, fi = 0, se = 0;
        std::function<void(int,int)> visit = [&](int u, int p) {
            partSize++;
            color[u] = 1;
            for (int v : next[u]) {
                if (p == v) {continue;}
                if (color[v] == 0) {
                    visit(v, u);
                } else if (color[v] == 1) {
                    isCycle = true;
                }
            }
            color[u] = 2;
        };
        for (int u = 1; u <= nV; ++u) {
            if (color[u] != 0) continue;
            partSize = 0; isCycle = 0;
            visit(u, 0);
            if (isCycle) {
                int perTeam = partSize / 2;
                fi += perTeam;
                se += perTeam;
            } else {
                int inc1 = (partSize+1)/2, inc2 = partSize/2;
                if (fi < se) {
                    fi += inc1;
                    se += inc2;
                } else {
                    se += inc1;
                    fi += inc2;
                }
            }
        }
        
        int answ = nV - 2 * std::min(fi, se);
        std::cout << answ << std::endl;
    }
    return 0;
}