// Решение: математика, итеративная функция, корневая эвристика
#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using ll = long long;
const ll XMAX = (ll)1e12L;
const ll XSQRT = (ll)1e6L;
ll solveFast(ll numOps, ll y, ll answ) {
    if (y == 1)
        return -1;
    if (answ < y)
        return answ;
    // бинарный поиск не нужен, будем сразу считать ответ, попутно выполняя
    // операции за O(sqrt(n))
    if (y - 1 <= XSQRT) {
        while (numOps --> 0 && answ >= y && answ <= XMAX)
            answ += (answ - 1) / (y - 1);
    } else {
        while (numOps > 0 && answ >= y && answ <= XMAX) {
            ll k = (answ - 1) / (y - 1);
            // k * (y-1) + 1 <= answ <= (k+1) * (y-1)
            ll right = std::max(answ, std::min(XMAX, (k + 1LL) * (y - 1LL)));
            ll steps = std::min(numOps, (right - answ) / k + 1LL);
            answ += k * steps;
            numOps -= steps;
        }
    }
    return (answ > XMAX) ? -1 : answ;
}

ll solve() {
    ll numOps; ll y, k;
    std::cin >> numOps >> y >> k;
    return solveFast(numOps, y, k);
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << "\n";
}
