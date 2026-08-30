#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем данные:
    ll g, l; cin >> g >> l;
    // перебираем все подходящие значения a, проверяя каждое:
    vector<pair<ll,ll>> answ;
    for (ll a = 1; a <= 1'000'000; a++)
        if (a % g == 0 && l % a == 0) {
            ll b = g * l / a; // используем a * b = НОК * НОД
            if (b <= 1'000'000 && gcd(a,b) == g && lcm(a,b) == l)
                answ.emplace_back(a, b);
        }
    // выводим ответ:
    cout << answ.size() << '\n';
    for (auto &[a, b] : answ)
        cout << a << ' ' << b << '\n';
}
main() {
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
