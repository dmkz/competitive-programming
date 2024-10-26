#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 998244353;
int kek(ll n, int k, ll prev) {
// n = число, которое нужно набрать суммой k чисел,
// причём предыдущее число было prev
// переберём, какое самое правое число мы можем поставить.
// Оно должно быть >= n / k, отсюда:
// x1 <= x2 <= x3 <= ... <= xk, x1+x2+...+xk = n
// Также оно должно быть делителем n
    if (k == 1)
        return (n >= 1 && n <= prev);
    int res = 0;
    for (int t = 1; t <= k; t++) {
        ll last = n / t;
        if (last * t != n || last > prev)
            continue;
        // выбрали, что k-м числом будет last. вызываемся рекурсивно:
        // должны поставить k-1 число и набрать сумму n - last
        res += kek(n - last, k-1, last);
        if (res >= mod)
            res -= mod;
    }
    return res;
}
main() {
    ll n; int k;
    while (cin >> n >> k)
        cout << kek(n,k,n) << endl;
}
