/*
    Problem: 1265E. Beautiful Mirrors
    Solution: probability theory, expected value, math, O(n)
*/
#include <bits/stdc++.h>
const auto io_sync_off = [](){std::ios_base::sync_with_stdio(0);std::cin.tie(0);return 0;}();
using ll = long long;
template<int mod>
struct IntMod {
    int value;
    IntMod(ll value_ = 0)
    {
        if (value_ < 0) { value = int(mod - (-value_) % mod); }
        else if (value_ >= mod) { value = int(value_ % mod); }
        else { value = (int)value_; }
    }
    IntMod pow(ll n) const {
        if (n == 0) { return IntMod(1); }
        else if (n < 0) { return (IntMod(1) / *this).pow(-n); }
        if (value <= 1) { return *this; }
        IntMod r = 1, a = *this;
        while (n > 0) {
            if (n & 1) {
                r *= a;
            }
            a *= a;
            n >>= 1;
        }
        return r;
    }
    IntMod operator-() const { return IntMod(mod-value); }
    IntMod operator*(IntMod other) const { return IntMod(value * 1LL * other.value); }
    IntMod operator/(IntMod other) const { return *this * other.pow(mod-2); }
    IntMod operator+(IntMod other) const { return IntMod(value+0LL+other.value); }
    IntMod operator-(IntMod other) const { return *this + (mod - other.value); }
    IntMod& operator*=(IntMod other) { return *this = *this * other; }
    IntMod& operator/=(IntMod other) { return *this = *this / other; }
    IntMod& operator+=(IntMod other) { return *this = *this + other; }
    IntMod& operator-=(IntMod other) { return *this = *this - other; }
};
template<int Mod> IntMod<Mod> pow(IntMod<Mod> v, ll n) { return v.pow(n); }
const int mod = 998244353;
using Int = IntMod<mod>;
int main() {
    for (int n; std::cin >> n; ) {
        std::vector<Int> a(n);
        Int sum = 1, prod = 1;
        for (int i = 0; i < n; i++) {
            int tmp; std::cin >> tmp;
            prod *= Int(tmp) / 100;
            sum += prod;
        }
        std::cout << ((sum - prod) / prod).value << std::endl;
    }
    return 0;
}