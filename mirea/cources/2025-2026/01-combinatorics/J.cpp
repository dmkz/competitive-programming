#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll geom(ll a, ll n, ll mod) {
// сумма 1 + a + a^2 + ... + a^{n-1}, состоящая из n слагаемых
    if (n % 2 == 0) // если число слагаемых чётное, то группируем отдельно
        // чётные и нечётные степени, выносим множитель из нечётных, и дальше
        // выносим общий множитель за скобки
        // (1 + a^2 + a^4 + ...) + (a + a^3 + a^5 + ...)
        // (1 + a) * (1 + a^2 + a^4 + ...)
        return (1 + a) * geom(a * a % mod, n / 2, mod) % mod;
    return (n == 1) ? 1 : (1 + a * geom(a, n - 1, mod) % mod);
}

main() {
    ll a, n, m;
    cin >> a >> n >> m;
    if (m == 1) { // по mod=1 всё равно нулю
        cout << 0;
        return 0;
    }
    a %= m;
    if (a < 0)
        a += m;
    cout << geom(a, n+1, m);
}
