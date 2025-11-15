// Решение: бинарный поиск по ответу, математика
#include <bits/stdc++.h>
using ll = long long;
const ll XMAX = (ll)1e12L;
ll solve() {
    int numOps; ll y, k;
    std::cin >> numOps >> y >> k;
    auto cntAlive = [&](ll n) {
        for (int i = numOps; i --> 0; n -= n / y);
        return n;
    };
    ll low = 0, high = (ll)XMAX+1;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (cntAlive(mid) >= k) high = mid;
        else low = mid;
    }
    return (high > XMAX ? -1 : high);
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << "\n";
}
