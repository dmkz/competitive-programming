#include <bits/stdc++.h>
using ll = long long;
ll binpow(ll a, ll n, ll modulo) {
    ll res = 1 % modulo;
    while (n > 0) {
        if (n & 1)
            (res *= a) %= modulo;
        (a *= a) %= modulo;
        n >>= 1;
    }
    return res;
}
void solve() {
    // изначально все степени равны 1
    // один запрос увеличивает одну степень на 1
    // это значит, что различных степеней не больше чем sqrt(q), потому что
    // чтобы достигнуть степени 2, мы должны сделать 1 запрос
    // чтобы достигнуть степени 3, мы должны сделать 2 запроса
    // чтобы достигнуть степени 4, мы должны сделать 3 запроса
    // чтобы достигнуть степени 5, мы должны сделать 4 запроса
    // ...
    // чтобы достигнуть степени k, мы должны сделать (k-1) запросов
    // а всего у нас q запросов, поэтому решение заключается в следующем:
    // храним список уникальных степеней, вовремя добавляя/удаляя из него
    // и идём слева-направо по уникальных степеням, считаем произведение
    // зная текущее количество каждой степени
    // асимптотика O(q * sqrt(q))
    int n, q; std::cin >> n >> q;
    std::vector<int> powersCnt(1+std::max(q,n));
    powersCnt[0] = n;
    std::vector<int> powerOfElem(n);
    std::set<int> nonZeroPowers = {0};
    while (q --> 0) {
        int t; std::cin >> t;
        if (t == 1) { // умножение
            int i; std::cin >> i;
            i--; // 0-индексация
            int was = powerOfElem[i]++;
            powersCnt[was]--;
            if (powersCnt[was] == 0) {
                auto it = nonZeroPowers.find(was);
                assert(it != nonZeroPowers.end());
                nonZeroPowers.erase(it);
            }
            powersCnt[was+1]++;
            if (powersCnt[was+1] == 1) {
                auto it = nonZeroPowers.find(was+1);
                assert(it == nonZeroPowers.end());
                nonZeroPowers.insert(was+1);
            }
        } else { // произведение k минимумов
            assert(t == 2);
            int k, modulo; std::cin >> k >> modulo;
            if (k > n) k = n;
            assert(1 <= k && k <= n);
            ll totalPowerOf2 = 0;
            for (int p : nonZeroPowers) {
                int take = std::min(k, powersCnt[p]);
                k -= take;
                totalPowerOf2 += p * 1LL * take;
                if (k == 0)
                    break;
            }
            std::cout << binpow(2, totalPowerOf2, modulo) << "\n";
        }
    }
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
