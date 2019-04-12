/*
    Задача: 749. Неправильный RSA
    
    Решение: рекурсия, перебор, разложение на множители, мемоизация
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
typedef long long ll;
typedef std::pair<ll,ll> pll;
struct Brute {
    std::vector<ll> data;
    std::map<pll, ll> cache;
    ll solve(ll last, ll prod) {
        if (prod == 1) { return 1; }
        auto key = pll(last, prod);
        auto it = cache.find(key);
        if (it == cache.end()) {
            ll answ = 0;
            for (auto curr = std::lower_bound(all(data), last); curr != data.end() && *curr <= prod; ++curr) {
                if (prod % (*curr) == 0) {
                    answ += solve(*curr, prod / *curr);
                }
            }
            if (isz(cache) < (1 << 18)) {
                return cache[key] = answ;
            }
            return answ;
        }
        return it->second;
    }
    ll operator()(int x, int y) {
        data.clear();
        ll pp = 1;
        for (int cx = 0; cx <= x; ++cx) {
            ll pq = 1;
            for (int cy = 0; cy <= y; ++cy) {
                if (cx + cy > 0) {
                    data.push_back(pq * pp);
                }
                pq *= 3;
            }
            pp *= 2;
        }
        std::sort(all(data));
        data.erase(std::unique(all(data)), data.end());
        return solve(2, data.back()) - 1;
    }
};

ll solve(ll n) {
    int k = 0;
    for (ll x = 2; x * x <= n && x <= (1 << 20); ++x) {
        if (n % x == 0) {
            while (n % x == 0) { n /= x; k++; }
            break;
        }
    }
    if (k == 0) { return 1; }
    return Brute()(k,k);
}
int main() {
    for (ll n; std::cin >> n; std::cout << solve(n) << "\n");
    return 0;
}