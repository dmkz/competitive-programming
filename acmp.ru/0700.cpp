// арифметическая прогрессия, математика
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// 15 100 10:
// 100 + 90 + 80 + ... + 10
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, v, k; cin >> n >> v >> k;
    ll sum{}; bool ok = true;
    for (ll i = 1; i <= n; i++) {
        ll val = v - (i-1) * k;
        if (val < 0) val = 0;
        if (val == 0) ok = false;
        sum += val;
    }
    cout << (ok ? "YES ": "NO ") << sum << endl;
}
