/*
    solution: ternary search, math, O(n log(n))
*/
#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int int64_t
using ll = __int128;
ll abs(ll x) { return x < 0 ? -x : x; }
int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    // читаем данные и делим p(i) на НОД всех p(i):
    int n; std::cin >> n;
    std::vector<int> s(n), p(n);
    for (auto &it : s) std::cin >> it;
    for (auto &it : p) std::cin >> it;
    int gcd = 0;
    for (auto &it : p) gcd = std::gcd(gcd, it);
    for (auto &it : p) it /= gcd;
    // теперь будем считать, что в i-й кучке будет лежать p[i] * base камней 
    // где 1 <= base <= 10^9. Тогда пропорции сохраняются и мы можем вычислить 
    // ответ для фиксированного base.
    // делаем тернарный поиск по base:
    auto f = [&](int base) {
        ll res{};
        for (int i = 0; i < isz(s); i++)
            res += abs((ll)base * p[i] - s[i]);
        return res;
    };
    int L = 1, R = (int)1e9;
    while (R - L > 2) {
        int l = (2 * L + R) / 3;
        int r = (L + 2 * R) / 3;
        if (f(l) <= f(r)) R = r;
        else L = l;
    }
    ll res = std::numeric_limits<ll>::max();
    for (int i = L; i <= R; i++)
        res = std::min(res, f(i));
    std::cout << (int64_t)res << std::endl;
}
