#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    const ll MOD = 1000000007LL;
    ll a;
    cin >> a;
    ll r = a % MOD;
    if (r < 0) r += MOD;
    cout << r;
}
