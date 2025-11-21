#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    const ll MOD = 1000000007LL;
    ll a, b;
    cin >> a >> b;
    ll d = (a - b) % MOD;
    if (d < 0) d += MOD;
    cout << d;
}
