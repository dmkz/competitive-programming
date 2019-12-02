/*
    Problem: 283B. Cow Program
    Solution: graphs, dfs, cycles, dynamic programming, O(n)
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using ll = long long;
using vi = std::vector<ll>;
using vvi = std::vector<vi>;
const ll INF = (ll)1e18L;
int main() {
    for (int n; std::cin >> n; std::cout << std::endl) {
        vi a(n);
        for (int i = 1; i < n; i++) std::cin >> a[i];
        vvi visited(2, vi(n)), res(2, vi(n)), color(2, vi(n));
        std::function<void(int,int)> visit = [&](int inc, int i) {
            if (color[inc][i] == 2) return;
            assert(color[inc][i] == 0);
            color[inc][i] = 1;
            auto delta = (inc ? a[i] : -a[i]);
            auto next = i + delta;
            if (next < 0 || next >= n) {
                res[inc][i] = std::abs(delta);
            } else if (color[1-inc][next] == 1) {
                res[inc][i] = INF;
            } else {
                if (color[1-inc][next] == 0) {
                    visit(1-inc, (int)next);
                }
                res[inc][i] = std::min(INF, std::abs(delta) + res[1-inc][next]);
            }
            color[inc][i] = 2;
        };
        for (int i = 1; i < n; i++) {
            visit(0, i);
            visit(1, i);
        }
        for (int i = 1; i < n; i++) {
            auto answ = i + res[0][i];
            if (answ >= INF) {
                std::cout << "-1\n";
            } else {
                std::cout << answ << '\n';
            }
        }
    }
    return 0;
}