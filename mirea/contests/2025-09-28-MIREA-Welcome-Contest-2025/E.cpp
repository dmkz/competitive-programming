#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
using ll = long long;
void solve() {
    ll n, d; int k;
    std::cin >> n >> d >> k;
    // читаем позиции и распределяем их по остаткам:
    std::map<ll, std::vector<ll>> pos;
    for (int i = 0; i < k; i++) {
        ll pi; std::cin >> pi;
        ll rem = pi % d;
        ll div = pi / d;
        pos[rem].push_back(div);
    }
    std::vector<ll> answ;
    for (const auto &[rem, vec] : pos) {
        // максимальная целая часть для этого остатка:
        ll maxDiv = (n-1) % d >= rem ? (n-1) / d : (n-1) / d - 1;
        assert(maxDiv >= 0);
        assert(maxDiv+1 >= isz(vec));
        // количество операций налево:
        ll toLeft = 0;
        for (ll target = 0; target <= maxDiv; target++) {
            if (target >= isz(vec))
                break;
            toLeft += vec[target] - target;
        }
        // количество операций направо:
        ll target = maxDiv, toRight = 0;
        for (int id = isz(vec)-1; id >= 0; id--, target--)
            toRight += target - vec[id];
        if (toLeft >= toRight) {
            for (int i = 0; i < isz(vec); i++)
                answ.push_back(rem + i * d);
        } else {
            target = maxDiv;
            for (int i = isz(vec)-1; i >= 0; i--, target--)
                answ.push_back(rem + target * d);
        }
    }
    std::sort(all(answ));
    for (int i = 0; i < isz(answ); i++) {
        if (i > 0)
            std::cout << ' ';
        std::cout << answ[i];
    }
    std::cout << "\n";
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
