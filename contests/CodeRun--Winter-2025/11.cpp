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
    // пусть число единиц текущее равно k, а позиций всего n
    // с вероятностью p = k / n мы инвертируем единицу,
    // и с вероятностью, q = 1 - k / n - нолик
    // M[n] = M[n-1] + 1                       (1)
    // M[n-1] = p * M[n-2] + q * M[n] + 1      (2)
    // M[k] = p * M[k-1] + q * M[k+1] + 1
    // M[0] = 0
    
    // подставляем (1) в (2), получим:
    // M[n-1] = p * M[n-2] + q * (M[n-1] + 1) + 1
    // M[n-1] * (1 - q) = p * M[n-2] + q + 1
    // M[n-1] = (p * M[n-2] + q + 1) / (1 - q)
    
    // в общем случае:
    // M[k] = A * M[k-1] + B
    // M[k-1] = p * M[k-2] + q * (A * M[k-1] + B) + 1
    // M[k-1] = (1 - q * A)^(-1) * (p * M[k-2] + q * B + 1)
    int n; std::cin >> n;
    std::vector<Int> M(n+1), A(n+1), B(n+1);
    // инициализируем i == n:
    A[n] = 1, B[n] = 1;
    const Int recipN = Int(1) / n;
    for (int i = n-1; i >= 1; i--) {
        // подставляем (i+1) в i:
        Int p = Int(i) * recipN;
        Int q = Int(1) - p;
        Int coeff = Int(1) / (Int(1) - q * A[i+1]);
        A[i] = coeff * p;
        B[i] = (q * B[i+1] + 1) * coeff;
    }
    for (int i = 1; i <= n; i++)
        M[i] = A[i] * M[i-1] + B[i];
    std::cout << M[n] << std::endl;
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
