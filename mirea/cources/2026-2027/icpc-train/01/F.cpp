#include <bits/stdc++.h>
#include <bits/extc++.h>
#define isz(x) (int)(x).size()
using namespace std;
// арифметика по простому модулю:
const int mod = (int)1e9+7, NMAX = 2020;
int &add(int &x, int y) { return (x += y) >= mod ? x -= mod : x; }
int mul(int a, int b) { return int(a * 1LL * b % mod); }
int mul(int a, int b, int c) { return mul(c, mul(a, b)); }
int binpow(int a, int64_t n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = mul(r, a);
        a = mul(a, a);
        n >>= 1;
    }
    return r;
}
const auto fact = [](){
    vector<int> res(NMAX, 1);
    for (int i = 1; i < NMAX; i++) res[i] = mul(res[i-1], i);
    return res;
}();
const auto ifact = [](){
    vector<int> res(NMAX, binpow(fact[NMAX-1], mod-2));
    for (int i = NMAX - 2; i >= 0; i--)
        res[i] = mul(res[i+1], i+1);
    return res;
}();
int C(int n, int k) {
    if (k < 0 || k > n || n < 0) return 0;
    return mul(fact[n], ifact[k], ifact[n-k]);
}
// решение задачи:
void solve() {
    int n, k, d; cin >> n >> k >> d;
    if (d >= n) {
        cout << C(n, k) << "\n";
        return;
    }
    // поделим фонари на группы с одинаковым остатком при делении на d: такие группы независимы
    // в одной группе не должно быть двух подряд взятых фонарей
    // посчитаем количество способов взять t фонарей в каждой группе
    vector dp(n+1, vector(k+1, vector(2, 0)));
    dp[0][0][0] = 1;
    for (int i = 1; i < isz(dp); i++) {
        // не берём i-й фонарь:
        for (int t = 0; t <= k; t++) {
            add(dp[i][t][0], dp[i-1][t][0]);
            add(dp[i][t][0], dp[i-1][t][1]);
        }
        // берём i-й фонарь: не берём предыдущий
        for (int t = 0; t < k; t++)
            add(dp[i][t+1][1], dp[i-1][t][0]);
    }
    // теперь нам нужно перемножить группы: скомбинировать их друг с другом
    // combined[d][k] = кол-во способов среди первых d групп выбрать k фонарей
    vector combined(d+1, vector(k+1, 0));
    combined[0][0] = 1;
    for (int i = 0; i < d; i++) {
        const int gsize = n / d + (i < n % d);
        for (int take = 0; take <= min(k, gsize); take++) {
            int ways = (dp[gsize][take][0] + dp[gsize][take][1]) % mod;
            for (int prev = 0; prev + take <= k; prev++)
                add(combined[i+1][prev+take], mul(combined[i][prev], ways));
        }
    }
    cout << combined[d][k] << "\n";
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
    return 0;
}