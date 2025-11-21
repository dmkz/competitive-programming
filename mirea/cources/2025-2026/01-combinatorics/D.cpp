#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

ll mul(ll x, ll y) {
    return (x * y) % MOD;
}

ll binpow(ll a, ll n) {
    a %= MOD;
    ll res = 1 % MOD;
    while (n > 0) {
        if (n & 1)
            res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}

main() {
    ll a, n;
    cin >> a >> n;
    cout << binpow(a, n);
}
