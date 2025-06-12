#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
// функция находит количество пар элементов a[i] < a[j] && i < j
ll count(vi & a, int l, int r) {
    if (l + 1 == r)
        return 0;
    // посчитаем количество пар в левой и правой половинах:
    const int m = (l + r) / 2;
    ll answ = count(a, l, m) + count(a, m, r);
    // после вызова функции для половин они отсортированы (каждая из них)
    // двумя указателями пройдёмся по половинам и посчитаем число пар
    int pos = m;
    for (int i = l; i < m; i++) {
        while (pos < r && a[pos] <= a[i])
            pos++;
        answ += (r - pos);
    }
    // сольём две отсортированные половины в одну:
    inplace_merge(a.begin() + l, a.begin() + m, a.begin() + r);
    return answ;
}
// быстрое возведение в степень:
const int mod = (int)1e9+7;
ll binpow(ll a, ll n) {
    ll r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            (r *= a) %= mod;
        (a *= a) %= mod;
        n /= 2;
    }
    return r;
}
void solve() {
    // прочитаем массив и найдём количество надписей ГОООООЛ!!! для него
    int n; cin >> n;
    vi a(n);
    for (auto &it : a)
        cin >> it;
    ll k = count(a, 0, n) % mod;
    // теперь посчитаем ответ:
    ll answ = 5 * k * (k+1) % mod * (k+2) % mod * binpow(6, mod-2) % mod;
    cout << answ << endl;
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
