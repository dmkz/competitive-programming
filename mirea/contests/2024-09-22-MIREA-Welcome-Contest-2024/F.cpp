#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, s, k;
    cin >> n >> s >> k;
    // сразу переходим в 0-индексацию
    k--;
    // теперь находим период
    long long t = n / gcd(n, s);
    // целую часть и остаток
    long long q = k / t;
    long long r = k % t;
    // выводим ответ
    int answ = (int)((q + r * s) % n);
    cout << answ << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0)
        solve();
}
