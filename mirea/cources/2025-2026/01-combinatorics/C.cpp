#include <bits/stdc++.h>
using namespace std;
using ll = long long;
main() {
    const ll MOD = 1000000007LL;
    ll a, b;
    cin >> a >> b;
    ll p = (a % MOD) * (b % MOD) % MOD;
    cout << p;
}
