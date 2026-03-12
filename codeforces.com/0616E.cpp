// модульная арифметика, суммирование до корня, вклад множителей в сумму
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mod = (int)1e9 + 7;
const int inv2 = (mod + 1) / 2;
const ll SQRT = (ll)4e6;

ll arithmetic(ll a, ll b) {
    ll len = (b - a + 1) % mod;
    a %= mod;
    b %= mod;
    return (a + b) % mod * len % mod * inv2 % mod;
}

int main() {
    ll n, m;
    cin >> n >> m;
    // Упростим сумму:
    // sum_{i=1}^{m} (n % i) = sum_{i=1}^{m} (n - [n / i] * i)
    // = n * m - sum_{i=1}^{m} ([n / i] * i)
    // либо i <= SQRT, либо [n/i] <= SQRT
    ll res = (n % mod) * (m % mod) % mod;
    // Случай 1. i <= SQRT:
    for (ll i = 1; i <= min(m, SQRT); i++)
        res = (res - (n / i) % mod * (i % mod)) % mod;
    // Случай 2. j=[n/i] <= SQRT:
    for (ll j = 1; j <= min(n, SQRT); j++) {
        // найдём отрезок [iMin, iMax] по i такой, что при делении n
        // целочисленно на каждое число из этого отрезка будем получать j:
        ll iMin = n / (j + 1) + 1;
        ll iMax = n / j;
        iMin = max(iMin, SQRT + 1);
        iMax = min(iMax, m);
        if (iMin <= iMax) // прибавляем вклад каждого числа i:
            res = (res - (j % mod) * arithmetic(iMin, iMax)) % mod;
    }
    // выводим ответ:
    cout << (res % mod + mod) % mod << '\n';
}
