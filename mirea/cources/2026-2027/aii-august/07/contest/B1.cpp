#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    ll n, a, b, c; cin >> n >> a >> b >> c;
    ll na = n / a;
    ll nb = n / b - n / (a * b);
    ll nc = n / c - n / (b * c) - n / (a * c) + n / (a * b * c);
    cout << na << ' ' << nb << ' ' << nc << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
