#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9+7;
// Быстрое возведение в степень:
int binpow(int a, int n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = int(r * 1LL * a % mod);
        a = int(a * 1LL * a % mod);
        n >>= 1;
    }
    return r;
}
// Факториалы и обратные к ним:
const int NMAX = 1 << 20;
int fact[NMAX], ifact[NMAX];
void precalc() {
    fact[0] = 1;
    for (int i = 1; i < NMAX; i++)
        fact[i] = int(fact[i-1] * 1LL * i % mod);
    ifact[NMAX-1] = binpow(fact[NMAX-1], mod-2);
    for (int i = NMAX-2; i >= 0; i--)
        ifact[i] = int((i+1LL) * ifact[i+1] % mod);
}
// Биномиальный коэффициент:
int C(int n, int k) {
    if (n < 0 || k < 0 || k > n)
        return 0;
    return int(fact[n] * 1LL * ifact[k] % mod * ifact[n-k] % mod);
}
// Решение:
void solve() {
    int n, q; cin >> n >> q;
    vector<int> r(q), c(q);
    for (auto &it : r) cin >> it;
    for (auto &it : c) cin >> it;
    for (int i = 1; i <= q; i++)
        cout << (C(n * n - i, n - i) - fact[n - i] + mod) % mod << ' ';
    cout << '\n';
}
main() {
    precalc(); // вызов предподсчёта факториалов и обратных к ним
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
