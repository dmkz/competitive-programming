// комбинаторика, простой модуль, биномиальные коэффициенты
#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
const int mod = 998244353, NMAX = 55;
using vi = std::vector<int>;
using vvi = std::vector<vi>;
using ll = long long;
// вычисляем все факториалы
const vi fact = [](){
    vi res(1+NMAX, 1);
    for (int i = 2; i <= NMAX; i++)
        res[i] = int(res[i-1] * 1LL * i % mod);
    return res;
}();
// вычисляем все биномиальные коэффициенты через треугольник паскаля:
const vvi C = [](){
    vvi res(1+NMAX, vi(1+NMAX));
    res[0][0] = 1;
    for (int n = 1; n <= NMAX; n++)
        for (int k = 0; k <= n; k++)
            res[n][k] = ((k-1 >= 0 ? res[n-1][k-1] : 0) + res[n-1][k]) % mod;
    return res;
}();
void solve() {
    int n; std::cin >> n;
    vi a(n+1);
    for (int i = 0; i <= n; i++)
        std::cin >> a[i];
    ll sum = std::accumulate(all(a), ll(0));
    ll numRounds = sum / n;
    ll remainder = sum % n;
    int answ = 0;
    int max = *std::max_element(a.begin()+1, a.end());
    if (((remainder > 0) && max > numRounds + 1) ||
        ((remainder == 0) && max > numRounds))
    {
        std::cout << answ << "\n";
        return;
    }
    int less = 0, equal = 0;
    for (int i = 1; i < isz(a); i++) {
        ll limit = numRounds + 1;
        less += (a[i] < limit);
        equal += (a[i] == limit);
    }
    if (equal > remainder) {
        std::cout << answ << "\n";
        return;
    }
    ll diff = remainder - equal;
    // 4-й пример: 2 * 3 * 2 = 12
    answ = int(C[less][diff] * 1LL * fact[remainder] % mod * fact[n-remainder] % mod);
    std::cout << answ << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
