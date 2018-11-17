/*
    Problem: 711D. Directed Roads
    
    Solution: math, combinatorics, graphs, dfs, cycles, O(n * log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <functional>
#include <queue>
#include <cassert>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

const int mod = (int)1e9+7;

int add(int a, int b) {
    return (a += b) >= mod ? a - mod : a;
}

int sub(int a, int b) {
    return (a -= b) < 0 ? a + mod : a;
}

int mul(int a, int b) {
    return int(1LL * a * b % mod);
}

int pow(int a, int n) {
    int res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mul(res, a);
        }
        n >>= 1;
        a = mul(a, a);
    }
    return res;
}

int main() {
    int n;
    while (std::cin >> n) {
        vvi edges(1+n); vi next(1+n);
        for (int u = 1, v; u <= n; ++u) {
            std::cin >> v; 
            next[u] = v;
            edges[u].push_back(v);
            edges[v].push_back(u);
        }
        // we need to know for each connected component:
        // - number of edges in cycle
        // - number of edges in component
        vi color(1+n), part(1+n), inCycle(1+n), prev(1+n);
        int nParts = 0;
        std::function<void(int,int,int)> visit = [&](int u, int p, int idPart) {
            if (color[u]) return;
            part[u] = idPart;
            prev[u] = p;
            color[u] = 1;
            for (int v : edges[u]) {
                if (v == p) continue;
                if (!color[v]) {
                    visit(v, u, idPart);
                } else if (color[v] == 1) {
                    inCycle[v] = 1;
                    for (int i = u; i != v; i = prev[i]) {
                        inCycle[i] = 1;
                    }
                }
            }
            color[u] = 2;
        };
        for (int i = 1; i <= n; ++i) {
            if (part[i]) continue;
            ++nParts;
            visit(i, 0, nParts);
        }
        vi edgesInComp(1+nParts), edgesInCycle(1+nParts);
        for (int u = 1; u <= n; ++u) {
            int v = next[u];
            assert(part[u] == part[v]);
            if ((inCycle[u] && inCycle[v]) || (u == next[v] && v == next[u])) {
                edgesInCycle[part[u]]++;
            }
            edgesInComp[part[u]]++;
        }
        int answ = 1;
        for (int idPart = 1; idPart <= nParts; ++idPart) {
            answ = mul(answ, sub(
                pow(2, edgesInComp[idPart]),
                pow(2, edgesInComp[idPart]-edgesInCycle[idPart]+1)
            ));
        }
        std::cout << answ << std::endl;
    }
    return 0;
}