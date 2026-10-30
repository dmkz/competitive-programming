#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using ll = long long;
ll solve(ll r) {
    // число x можно представить в виде: x = d + 10*(other_digits)
    // переберём последнюю цифру и посчитаем, какие числа на неё делятся
    // для каждой цифры точно делятся делители 10, то есть: {1, 2, 5}
    // остальные сокращаем на gcd и считаем, сколько способов выбрать (other_digits)
    // other_digits должно делиться на d / gcd(d, 10)
    ll answ{};
    for (ll d = 1; d <= 9; d++) {
        ll step = d / gcd(d, 10);
        // к ответу прибавляется k+1 из: d + 10 * k * step <= r
        // k <= (r - d) / (10 * step)
        ll k = max<ll>(0, (r - d) / (10 * step));
        answ += (r >= d ? k+1 : 0);
    }
    return answ;
}
void solve() {
    int q; cin >> q;
    while (q --> 0) {
        ll l, r; cin >> l >> r;
        cout << solve(r) - solve(l-1) << '\n';
    }
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; // cin >> tt;
    while (tt --> 0) solve();
    return 0;
}
