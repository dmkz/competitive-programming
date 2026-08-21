#include <bits/stdc++.h>
#include <cassert>
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
const int NMAX = 1 << 21;
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
    int n, d, q; cin >> n >> d >> q;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        int a, c; cin >> a >> c;
        cnt[a] += c;
    }
    while (q --> 0) {
        char ch; cin >> ch;
        if (ch == '+') {
            int a, c; cin >> a >> c;
            cnt[a] += c;
        } else if (ch == '-') {
            int a, c; cin >> a >> c;
            cnt[a] -= c;
            if (cnt[a] == 0)
                cnt.erase(cnt.find(a));
        } else {
            assert(ch == '?');
            int k; cin >> k;
            cout << C(cnt.size() + k - 1, k) << '\n';
        }
    }
}
main() {
    precalc(); // вызов предподсчёта факториалов и обратных к ним
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
