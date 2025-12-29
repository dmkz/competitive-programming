// математика, степени двоек
#include <bits/stdc++.h>
using ll = long long;
void solve() {
    ll a, b; std::cin >> a >> b;
    ll answ = 0;
    for (ll layers = 1; layers <= 30; layers++) {
        ll sum[2]{};
        for (ll id = 0; id < layers; id++)
            sum[id%2] += (1LL << id);
        if ((sum[0] <= a && sum[1] <= b) ||
            (sum[0] <= b && sum[1] <= a))
        {
            answ = layers;
        }
    }
    std::cout << answ << "\n";
}
main() {
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
