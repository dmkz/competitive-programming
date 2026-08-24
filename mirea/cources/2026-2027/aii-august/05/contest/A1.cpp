#include <bits/stdc++.h>
using namespace std;
// предподсчёт суммы всех простых Решетом Эратосфена
const int NMAX = 1 << 20;
vector<int64_t> primes;
void precalc() {
    // строим решето Эратосфена за O(n log(log(n))):
    primes.assign(NMAX+1, 1);
    primes[0] = primes[1] = 0;
    for (int i = 2; i * i <= NMAX; i++)
        if (primes[i])
            for (int j = i * i; j <= NMAX; j += i)
                primes[j] = 0;
    // считаем префиксные суммы прямо внутри решета:
    for (int i = 2; i <= NMAX; i++)
        primes[i] = (primes[i] ? i : 0) + primes[i-1];
}
void solve() {
    // читаем запросы:
    int q; cin >> q;
    vector<int> r(q);
    for (auto &it : r) cin >> it;
    // отвечаем на них:
    for (auto rr : r)
        cout << primes[rr] << ' ';
    cout << '\n';
}
main() {
    precalc(); // вызываем предподсчёт один раз
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
}
