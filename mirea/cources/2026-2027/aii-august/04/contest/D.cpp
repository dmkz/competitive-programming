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
// Количество путей из (r1, c1) в (r2, c2):
int cntWays(int r1, int c1, int r2, int c2) {
    assert(r1 <= r2);
    if (c1 > c2) return 0;
    int dr = r2 - r1, dc = c2 - c1;
    return C(dr+dc, dr);
}
// Решение:
void solve() {
    int n, m, r1, c1, r2, c2;
    cin >> n >> m >> r1 >> c1 >> r2 >> c2;
    // отсортируем клетки так, чтобы (r1, c1) шла раньше (r2, c2)
    if (r1 > r2 || (r1 == r2 && c1 > c2)) {
        swap(r1, r2);
        swap(c1, c2);
    }
    // считаем пути по формуле включений-исключений:
    int64_t answ = cntWays(1, 1, n, m);
    answ -= cntWays(1, 1, r1, c1) * 1LL * cntWays(r1, c1, n, m);
    answ -= cntWays(1, 1, r2, c2) * 1LL * cntWays(r2, c2, n, m);
    answ += cntWays(1, 1, r1, c1) * 1LL * cntWays(r1, c1, r2, c2) % mod * cntWays(r2, c2, n, m);
    // выводим ответ:
    cout << (answ % mod + mod) % mod << '\n';
}
main() {
    precalc(); // вызов предподсчёта факториалов и обратных к ним
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
