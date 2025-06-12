#include <bits/stdc++.h>
using namespace std;
uint32_t binpow(uint32_t a, uint64_t n) {
// быстрое возведение числа a в степень n по модулю 2^32
    uint32_t r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r *= a;
        a *= a;
        n /= 2;
    }
    return r;
}
uint32_t geomsum(uint32_t a, uint64_t n) {
    // сумма геометрической прогрессии 1 + a + a^2 + ... + a^(n-1), n слагаемых
    if (n == 1)
        return 1;
    // если число слагаемых чётно, то сгруппируем нечётные и чётные степени, затем вынесем множитель
    // 1 + a + a^2 + ... + a^(n-1) = (1 + a^2 + a^4 + ...) + (a + a^3 + a^5 + ...) =
    // = (1 + a^2 + a^4 + ...) + a * (1 + a^2 + a^4 + ...) = (1 + a) * (1 + a^2 + a^4 + ...)
    if (n % 2 == 0)
        return (1 + a) * geomsum(a * a, n / 2);
    // если число слагаемых нечётно, то уменьшим его на 1:
    // 1 + a + a^2 + ... + a^(n-1) = 1 + a * (1 + a + a^2 + ... + a^(n-2))
    return 1 + a * geomsum(a, n - 1);
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    uint32_t k, b, x; int q;
    cin >> k >> b >> x >> q;
    while (q --> 0) {
        int64_t n; cin >> n;
        // применим пару раз операцию и раскроем скобки, получаем:
        // (((x * k + b) * k + b) * k + b) * k + b = x * k^4 + b * k^3 + b * k^2 + ... + b =
        // = x * k^4 + b * (k^3 + k^2 + k + 1)
        // в общем виде:
        // x * k^n + b * (1 + k + k^2 + ... + k^(n-1))
        cout << x * binpow(k, n) + b * geomsum(k, n) << ' ';
    }
    cout << endl;
}
