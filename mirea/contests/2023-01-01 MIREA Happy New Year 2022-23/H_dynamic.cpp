// tags: dynamic programming, combinatorics, math, trees, O(d^3)
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)

using ll = long long;

ll geom(ll a, ll lastPow) {
    assert(lastPow >= 0);
    ll res = 0, pa = 1;
    for (ll p = 0; p <= lastPow; p++) {
        res += pa;
        pa *= a;
    }
    return res;
}

ll power(ll a, ll pw) {
    if (pw < 0) return 0;
    ll pa = 1;
    for (ll p = 1; p <= pw; p++) {
        pa *= a;
    }
    return pa;
}

ll solve(const int dep) {
    assert(dep >= 0);
    
    ll numVertOnLastLevel = 1;
    ll answ = 0;
    
    for (int i = 1; i <= dep; i++) {
        // добавляем уровень i
        numVertOnLastLevel *= 6;
        // считаем расстояние от вершины на последнем уровне до других
        ll sumBefore = 0;
        ll sumToLastLevel = 0;
        for (int j = i; j >= 0; j--) {
            for (int delta = 0; delta <= j; delta++) {
                ll coeff = (power(6, delta) - power(6, delta-1));
                ll dist = (j+delta);
                if (delta == j) sumToLastLevel += dist * coeff;
                else sumBefore += dist * coeff;
            }
        }
        answ += sumToLastLevel * numVertOnLastLevel;
        answ += sumBefore * numVertOnLastLevel * 2;
    }
    return answ;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int t; std::cin >> t;
    while (t--) {
        int depth; std::cin >> depth;
        std::cout << solve(depth) << '\n';
    }
    return 0;
}