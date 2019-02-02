/*
    Задача: 1414. Многословие
    
    Решение: offline-запросы, прибавление квадрата расстояния на отрезке, сортировка, O(n log(n))
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define all(x) (x).begin(), (x).end()

typedef long long ll;

struct Pair {
    int index, value; 
    Pair(int index_ = 0, int value_ = 0) : index(index_), value(value_) { }
};

typedef std::vector<Pair> vp;

bool operator<(Pair lhs, Pair rhs) {
    return lhs.index < rhs.index || (lhs.index == rhs.index && lhs.value < rhs.value);
}

void solve(const int n, const std::vector<Pair>& queries, std::vector<ll>& answ, bool reverseOrder = false) {
    ll s2 = 0, s1 = 0, k = 0; int id = 0;
    for (int i = 1; i <= n; ++i) {
        while (id < (int)queries.size() && queries[id].index == i) {
            int sign = queries[id].value >= 0 ? +1 : -1;
            int value = std::abs(queries[id].value);
            id++;
            k += sign;
            s2 += sign * (ll)value * value;
            s1 += sign * (ll)value;
        }
        s2 += 2 * s1 + k;
        s1 += k;
        answ[reverseOrder ? n - i + 1 : i] += s2;
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cerr.tie(0); std::cout.tie(0);
    int n, q;
    while (std::cin >> n >> q) {
        vp queriesLR, queriesRL;
        for (int i = 0, l, r; i < q; ++i) {
            std::cin >> l >> r;
            if (l <= r) {
                queriesLR.push_back(Pair(l,0));
                queriesLR.push_back(Pair(r+1,-(r-l+1)));
            } else {
                queriesRL.push_back(Pair(n-l+1,0));
                queriesRL.push_back(Pair(n-(r-1)+1,-(l-r+1)));
            }
        }
        std::sort(all(queriesLR));
        std::sort(all(queriesRL));
        std::vector<ll> answ(1+n);
        solve(n, queriesLR, answ, false);
        solve(n, queriesRL, answ, true);
        for (int i = 1; i <= n; ++i) { std::cout << answ[i] << "\n"; }
    }
    return 0;
}