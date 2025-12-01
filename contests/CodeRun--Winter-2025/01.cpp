#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<ll, ll>;
void solve() {
    ll R, B; std::cin >> R >> B;
    // R = 2*(W-1)+2*(H-1)
    // B = (W-2)*(H-2)
    auto check = [&](ll W, ll H) -> bool {
        return R == 2*(W-1)+2*(H-1) &&
               B == (W-2)*(H-2) && W >= H;
    };
    pll answ(-1, -1);
    for (ll x = 1; x * x <= B; x++) {
        if (ll y = B / x; x * y == B) {
            // x = W-2, y = H-2
            if (check(x+2, y+2)) {
                answ = {x+2, y+2};
                break;
            }
            if (check(y+2, x+2)) {
                answ = {y+2, x+2};
                break;
            }
        }
    }
    auto [W, H] = answ;
    std::cout << W << " " << H << std::endl;
}
main() {
    solve();
}
