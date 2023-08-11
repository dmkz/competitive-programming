#include <bits/stdc++.h>

// Operations with bits:
template<typename T> void setbit(T &mask, int bit, bool x) {
// устанавливает значение бита в `x`
    (mask &= ~(T(1) << bit)) |= (T(x) << bit);
}

template<typename T> bool getbit(T &mask, int bit) {
// возвращает значение бита
    return (mask >> bit & 1);
}

template<typename T> void flipbit(T &mask, int bit) {
// меняет значение бита на противоположный
    mask ^= (T(1) << bit);
}

using ll = long long;

ll solve(ll l, ll r) {
    // найти наибольший общий двоичный префикс
    int i = 60;
    while (i >= 0 && getbit(l,i) == getbit(r,i))
        i--;
    if (i < 0)
        return l;
    // различие в i-м разряде, все остальные разряды можем заполнить единицами
    ll x = l;
    for (int bit = i-1; bit >= 0; bit--)
        setbit(x, bit, 1);
    return (__builtin_popcountll(x) >= __builtin_popcountll(r)) ? x : r;
}
int main() {
    int n; std::cin >> n;
    while (n --> 0) {
        ll l, r; std::cin >> l >> r;
        std::cout << solve(l,r) << '\n';
    }
    return 0;
}
