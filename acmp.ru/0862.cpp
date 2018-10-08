/*
    Задача: 862. Домашняя работа
    
    Решение: целочисленная арифметика, арифметическая прогрессия, O(sqrt(m))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

typedef long long ll;

ll sum(ll a, ll b) {
    if (b < a) return ll(0);
    return (a + b) * (b-a+1) / 2;
}

ll part1(ll n, ll m) {
    return n / m * sum(1, m-1) + sum(1, n % m);
}

ll part2(ll n, ll m) {
    ll res = n * m;
    ll last = n+1;
    for (ll k = 1; k * k <= m; ++k) {
        // [m / i] = k
        // m = i * k + rem
        ll high = m / k;
        ll low = m / (k+1) + 1;
        res -= k * sum(low, std::min(n, high));
        last = std::min(last, low);
    }
    for (ll i = 1; i < last; ++i) {
        res -= m / i * i;
    }
    return res;
}

ll solve(ll n, ll m) {
    return part1(n,m) + part2(n,m);
}

int main() {
    ll n, m; 
    while (std::cin >> n >> m) {
        std::cout << solve(n,m) << std::endl;
    }
    return 0;
}