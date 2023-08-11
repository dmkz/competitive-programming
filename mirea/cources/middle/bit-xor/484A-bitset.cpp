#include <bits/stdc++.h>

using ll = long long;
using bs = std::bitset<64>;

ll solve(bs l, bs r) {
    // найти наибольший общий двоичный префикс
    int i = 60;
    while (i >= 0 && l[i] == r[i])
        i--;
    if (i < 0)
        return l.to_ullong();
    // различие в i-м разряде, все остальные разряды можем заполнить единицами
    auto x = l;
    for (int bit = i-1; bit >= 0; bit--)
        x[bit] = 1;
    return ((x.count() >= r.count()) ? x : r).to_ullong();
}
int main() {
    int n; std::cin >> n;
    while (n --> 0) {
        ll l, r; std::cin >> l >> r;
        std::cout << solve(l,r) << '\n';
    }
    return 0;
}
