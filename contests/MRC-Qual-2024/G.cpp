#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using ll = long long;
using ld = long double;
using pll = std::pair<ll, ll>;
// C(n,k) * k! = n! / (n-k)! == x
// x = n * (n-1) * (n-2) * ... * (n-k+1)
// k = 1: n = x
// k = 2: x = n * (n - 1) >= (n-1)^2
// k = 3: x = n * (n - 1) * (n - 2) >= (n-2)^3

// предподсчитаем все числа, которые могут быть получены при n <= 10^6:
std::vector<std::tuple<ll, int, int>> data;
void precalc() {
    for (int n = 1; n <= (int)1e6+100; n++) {
        ld kek = 1;
        for (int k = 1; k <= n; k++) {
            kek *= (n - k + 1);
            if (kek <= 1e18) {
                data.emplace_back((ll)kek, n, k);
            } else {
                break;
            }
        }
    }
    std::sort(all(data));
}
// решаем задачу
pll solve(ll x) {
    std::vector<pll> cand;
    // вытаскиваем предподсчитанное значение, если оно было возможно (для n <= 10^6):
    auto it = std::lower_bound(all(data), std::make_tuple(x, 0, 0));
    int i = int(it - data.begin());
    if (i < isz(data)) {
        auto [xx, nn, kk] = data[i];
        if (xx == x) {
            cand.emplace_back(nn, kk);
        }
    }
    // если n > 10^6, то k могло быть только либо 1, либо 2
    // считаем вариант при k = 2, то есть число вида:
    // x = n * (n-1)
    ll root = (ll)std::sqrt(ld(x));
    if (root * (root + 1) == x)
        cand.emplace_back(root+1, 2);
    // вариант при x=n, k = 1 всегда подходит, его тоже добавим:
    cand.emplace_back(x, 1);
    // вортируем и выдаём минимальный вариант в качестве ответа:
    std::sort(all(cand));
    return cand[0];
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    precalc();
    int tt; std::cin >> tt;
    while (tt --> 0) {
        ll x; std::cin >> x;
        auto [n,k] = solve(x);
        std::cout << n << ' ' << k << "\n";
    }
}
