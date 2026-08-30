#include <bits/stdc++.h>
using namespace std;
// модульная арифметика:
const int mod = 998244353;
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
int add(int a, int b) {
    return (a + b) % mod;
}
int sub(int a, int b) {
    return (a - b + mod) % mod;
}
int binpow(int a, int64_t n) {
    int res = 1;
    while (n > 0) {
        if (n % 2 == 1)
            res = mul(res, a);
        a = mul(a, a);
        n >>= 1;
    }
    return res;
}
int inv(int a) {
    return binpow(a, mod - 2);
}
// факториалы и обратные к ним:
const int NMAX = 2 * 1024 * 1024;
const auto fact = [](){
    vector<int> res(NMAX+1, 1);
    for (int i = 2; i <= NMAX; i++)
        res[i] = mul(res[i-1], i);
    return res;
}();
const auto ifact = [](){
    vector<int> res(NMAX+1, 1);
    res[NMAX] = inv(fact[NMAX]);
    for (int i = NMAX-1; i >= 0; i--)
        res[i] = mul(res[i+1], i+1);
    return res;
}();
// биномиальный коэффициент:
int C(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    return mul(fact[n], mul(ifact[k], ifact[n-k]));
}
// количество путей (r1, c1) -> (r2, c2):
int cntWays(int r1, int c1, int r2, int c2) {
    int dr = r2 - r1, dc = c2 - c1;
    if (dr < 0 || dc < 0) return 0;
    return C(dr+dc, dr);
}
// решение задачи:
void solve() {
    // читаем данные:
    int n, m, q; cin >> n >> m >> q;
    // сколько всего путей из (1, 1) в (n, m):
    int total = cntWays(1, 1, n, m);
    while (q --> 0) {
        // читаем текущий набор ловушек:
        int k; cin >> k;
        vector<int> r(k), c(k);
        for (auto &it : r) cin >> it;
        for (auto &it : c) cin >> it;
        // считаем ответ: "безопасные пути" = "все пути" вычесть "пути через ловушки"
        int answ = total;
        for (int i = 0; i < k; i++)
            answ = sub(answ, mul(cntWays(1, 1, r[i], c[i]), cntWays(r[i], c[i], n, m)));
        cout << answ << '\n';
    }
}
main() {
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
}
