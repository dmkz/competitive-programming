/*
    Problem: 557D. Vitaly and Cycle
    
    Solution: graphs, bipartite graph, combinatorics, dfs, cycles, connected components, greedy, O(n+m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

typedef long long ll;
typedef std::vector<int> vi;
typedef std::vector<vi> vvi;

int main() {
    int n, m;
    while (std::cin >> n >> m) {
        vvi next(1+n);
        for (int i = 0, a, b; i < m; ++i) {
            std::cin >> a >> b;
            next[a].push_back(b);
            next[b].push_back(a);
        }
        if (m == 0) {
            std::cout << 3 << " " << (ll)n*(n-1)*(n-2)/6 << std::endl;
            continue;
        }
        bool is_odd_cycle = false;        
        vi from(1+n, 0), part(1+n), color(1+n), size{0}, cnt1{0}, cnt2{0};
        color[0] = 2;
        std::function<void(int,int,int)> make_component = [&](int u, int p, int idPart) {
            if (part[u]) return;
            part[u] = idPart;
            size[idPart]++;
            color[u] = 3 - color[p];
            cnt1[idPart] += (color[u] == 1);
            cnt2[idPart] += (color[u] == 2);
            for (int v : next[u]) {
                if (p == v) continue;
                if (!color[v]) {
                    make_component(v, u, idPart);
                } else if (color[v] == color[u]) {
                    is_odd_cycle = true;
                }
            }
        };
        for (int u = 1; u <= n; ++u) {
            if (part[u]) continue;
            size.push_back(0);
            cnt1.push_back(0);
            cnt2.push_back(0);
            make_component(u, 0, (int)size.size()-1);
        }
        
        if (is_odd_cycle) {
            std::cout << 0 << ' ' << 1 << std::endl;
            continue;
        }
        
        int max = *std::max_element(size.begin(), size.end());
        if (max >= 3) {
            // answer is 1
            ll count = 0;
            for (int idPart = 1; idPart < (int)size.size(); ++idPart) {
                count += cnt1[idPart] * (cnt1[idPart]-1LL) + cnt2[idPart] * (cnt2[idPart]-1LL);
            }
            count /= 2;
            std::cout << 1 << ' ' << count << std::endl;
            continue;
        }
        ll count = 0;
        ll sum1 = 0;
        ll sum2 = 0;
        for (int idPart = 1; idPart < (int)size.size(); ++idPart) {
            sum1 += (size[idPart] == 1);
            sum2 += (size[idPart] == 2);
        }
        for (int idPart = 1; idPart < (int)size.size(); ++idPart) {
            if (size[idPart] == 2) {
                count += (sum2 - 1) * 2 + sum1;
            }
        }
        std::cout << 2 << ' ' << count << std::endl;
    }
    return 0;
}