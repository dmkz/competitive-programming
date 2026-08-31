#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    ll a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    auto check = [&](ll n){
        ll na = n / a;
        if (na < x) return false;
        ll nb = n / b - n / (a * b);
        if (nb < y) return false;
        ll nc = n / c - n / (b * c) - n / (a * c) + n / (a * b * c);
        return nc >= z;
    };
    ll low = 0, high = (ll)1e18;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
