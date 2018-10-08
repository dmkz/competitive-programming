/*
    Problem: 711C. Coloring Trees

    Solution: dynamic programming, O(n*k*m^2)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

const ll INF = (ll)1e18L;

int main() {
    static ll min[101][101][101];
    std::fill(&min[0][0][0],&min[0][0][0]+101*101*101,INF);
    int n, m, k;
    std::cin >> n >> m >> k;
    min[0][0][0] = 0;
    std::vector<int> color(1+n);
    for (int i = 1; i <= n; ++i) {
        std::cin >> color[i];
    }
    int cost[101][101];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            std::cin >> cost[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int curr = 1; curr <= m; ++curr) {
            if (color[i] > 0 && color[i] != curr) continue;
            int cost_ = (color[i] == curr) ? 0 : cost[i][curr];
            for (int prev = 0; prev <= m; ++prev) {
                for (int count = 0; count + (prev != curr) <= n; ++count) {
                    auto& it = min[i][curr][count+(prev!=curr)];
                    it = std::min(it, min[i-1][prev][count] + cost_);
                }
            }
        }
    }
    ll answ = INF;
    for (int curr = 1; curr <= m; ++curr) {
        answ = std::min(answ, min[n][curr][k]);
    }
    if (answ == INF) answ = -1;
    std::cout << answ;
    return 0;
}