/*
    Задача: 774. Шляпа
    
    Решение: геометрия, описанная окружность, O(n*m)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
 
typedef long double ld;
 
typedef long long ll;
 
const ld PI = std::acos(ld(-1));
 
const ld EPS = 1e-16L;
 
bool less(ld a, ld b) {
    return a <= b * (1 + EPS);
}
 
bool check(const int n, ld a, ld r) {
    ld d = 0;
    switch (n) {
        case 1: d = a * std::sqrt(ld(1)/2); break;
        case 2: d = a * std::sqrt(ld(5)/4); break;
        case 3: d = a * std::sqrt(ld(256) + ld(169)) / 16; break;
        case 4: d = a * std::sqrt(ld(2)); break;
        case 5: d = a * std::sqrt(ld(5)/2); break;
    };
    return less(d, r);
}
 
auto max_number(ld a, ld r, ld h) {
    ll answ = 0;
    for (int i = 1; i <= 5; ++i) {
        if (check(i, a, r)) {
            answ = std::max(answ, ll(h / a + EPS) * i);
        }
    }
    return answ;
}
 
int main() {
    std::ios_base::sync_with_stdio(false); std::cin.tie(0);
    int n, nC; ld r, h;
    while (std::cin >> n >> nC >> r >> h) {
        std::vector<ld> side(n);
        for (auto &it : side) { std::cin >> it; }
        ll answ = 0;
        for (int i = 0; i < nC; ++i) {
            for (int j = 0; j < n; ++j) {
                ll q; std::cin >> q;
                answ = std::max(answ, q * max_number(side[j], r, h));
            }
        }
        std::cout << answ << std::endl;
    }
    return 0;
}