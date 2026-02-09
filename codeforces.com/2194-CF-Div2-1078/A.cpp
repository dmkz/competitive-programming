// математика
#include <bits/stdc++.h>
using ll = long long;
void solve() {
    ll w, n;
    std::cin >> n >> w;
    if (w == 1) {
        std::cout << "0\n";
        return;
    }
    ll full = n / w;
    ll rem = n - full * w;
    ll res = full * (w - 1);
    res += std::min(rem, w-1);
    std::cout << res << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
