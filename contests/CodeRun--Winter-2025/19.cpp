#include <bits/stdc++.h>
// модульная арифметика
template<int mod>
struct IntMod {
    int value;
    IntMod(int x = 0)
        : value(x)
    {
        normalize();
    }
    void normalize() {
        if (value < 0 || value >= mod) {
            value %= mod;
            if (value < 0)
                value += mod;
        }
        assert(0 <= value && value < mod);
    }
    IntMod &operator*=(const IntMod &other) {
        value = int(value * 1LL * other.value % mod);
        return *this;
    }
    IntMod operator*(const IntMod &other) const {
        return IntMod(*this) *= other;
    }
    IntMod operator^(int n) const {
        while (n < 0)
            n += mod-1;
        int res = 1, a = value;
        while (n > 0) {
            if (n % 2 == 1)
                res = int(res * 1LL * a % mod);
            a = int(a * 1LL * a % mod);
            n >>= 1;
        }
        return res;
    }
    IntMod &operator/=(const IntMod &other) const {
        return *this *= (other ^ (-1));
    }
    IntMod operator/(const IntMod &other) const {
        return *this * (other ^ (-1));
    }
    IntMod &operator+=(const IntMod &other) {
        value += other.value;
        if (value >= mod)
            value -= mod;
        return *this;
    }
    IntMod operator-() const {
        int temp = -value;
        if (temp < 0)
            temp += mod;
        assert(0 <= temp && temp < mod);
        return IntMod(temp);
    }
    IntMod &operator-=(const IntMod &other) {
        return *this += -other;
    }
    IntMod operator+(const IntMod &other) const {
        return IntMod(*this) += other;
    }
    IntMod operator-(const IntMod &other) const {
        return IntMod(*this) -= other;
    }
};
template<int mod>
std::ostream &operator<<(std::ostream &os, const IntMod<mod> &num)
{
    return os << num.value;
}
// Решение:
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
void solve() {
    // M[x] = мат.ожидание для достижения N големов максимального цвета, имея x
    // M[N] = 0
    // Пусть сейчас их x. С вероятностью p = (N-x)*x/C(N, 2) увеличим на 1
    // С вероятностью q = 1 - p не поменяем. Тогда, по формуле условного мат. ожидания:
    // M[x] = M[x+1] * p + M[x] * q + 1
    // M[x] = (M[x+1] * p + 1) / p = M[x+1] + 1 / p
    // читаем данные и находим:
    // 1) N - суммарное количество големов
    // 2) iMax - максимальный номер голема с ненулевым количеством
    int m; std::cin >> m;
    std::vector<int> a(m);
    int N{}, iMax = -1;
    for (int i = 0; i < m; i++) {
        std::cin >> a[i];
        N += a[i];
        if (a[i] > 0)
            iMax = i;
    }
    assert(iMax != -1);
    // считаем мат.ожидания рекуррентно:
    std::vector<Int> M(N+1);
    Int denom = (Int)N*(N-1)/2;
    Int invDenom = (Int)1 / denom;
    for (int x = N-1; x >= 1; x--) {
        Int p = Int(N - x) * x * invDenom;
        M[x] = M[x+1] + (Int)1 / p;
    }
    // выводим ответ:
    std::cout << M[a[iMax]] << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    solve();
}
