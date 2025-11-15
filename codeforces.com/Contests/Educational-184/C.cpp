// Решение: префикс-суммы, оптимизация перебора, линейные алгоритмы, математика
#include <bits/stdc++.h>
using ll = long long;
using vi = std::vector<int>;
using vl = std::vector<ll>;
void remax(auto &x, const auto &y) { if (x < y) x = y; }
// была сумма S
// вычли сумму на отрезке, заменили её на (l+r):
// S - (s[r] - s[l-1]) + (r-(l-1))*(l+r)
// S - s[r] + s[l-1] + r * l + r * r - l * (l-1) - r * (l-1)
// S - s[r] + s[l-1] + r * (r+1) - l * (l-1)
// S - (s[r] - r * (r+1)) + (s[l-1] - (l-1) * l)
const ll inf = (ll)1e18L;
ll solve() {
    int n; std::cin >> n;
    vi a(n+1);
    vl s(n+1);
    ll maxLeft = 0;
    ll S{}, answ = -inf;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        s[i] = a[i] + s[i-1];
        ll val = (s[i] - i * (i + 1LL));
        remax(answ, maxLeft - val);
        remax(maxLeft, val);
        S += a[i];
    }
    return S + answ;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << "\n";
}
