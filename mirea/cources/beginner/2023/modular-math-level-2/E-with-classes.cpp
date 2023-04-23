#include <bits/stdc++.h>

template<int mod>
struct Residue {

    int x;
    
    Residue(int x_ = 0)
        : x(x_)
    {
        // взятие остатка, если нужно:
        if (std::abs(x) >= mod)
            x %= mod;
        // потом приводим к полуинтервалу [0, mod):
        if (x < 0)
            x += mod;
    }
    
    Residue(int64_t x_)
        : Residue(int(x_ % mod)) // вызов конструктора от инта
    { }
    
    // прибавление:
    Residue& operator+=(const Residue &rhs) {
        x += rhs.x;
        if (x >= mod)
            x -= mod;
        return *this;
    }
    
    // унарный минус:
    Residue operator-() const {
        int y = mod - x; // x in [0, mod) --> y in [mod, 0)
        if (y >= mod)
            y -= mod;
        return Residue(y);
    }
    
    // вычитание через прибавление + унарный минус:
    Residue& operator-=(const Residue &rhs) {
        return *this += (-rhs);
    }
    
    // сумма двух остатков через копирование + прибавление:
    Residue operator+(const Residue &rhs) const {
        return Residue(*this) += rhs;
    }
    
    // разность двух остатков через копирование + вычитание:
    Residue operator-(const Residue &rhs) const {
        return Residue(*this) -= rhs;
    }
    
    // умножение двух остатков:
    Residue operator*(const Residue &rhs) const {
        return Residue(x * 1LL * rhs.x);
    }
    
    // умножение на rhs с модификацией через умножение двух остатков:
    Residue &operator*=(const Residue &rhs) {
        return *this = *this * rhs;
    }
    
    // возведение в степень:
    Residue operator^(int n) const {
        // степень - периодична с периодом phi(p) = p-1:
        if (n >= std::abs(mod-1))
            n %= mod-1;
        if (n < 0)
            n += mod-1;
        // частные случаи:
        if (n == 0) // нулевая степень
            return 1;
        if (x <= 1) // возводим 0 или 1
            return x;
        // дальше быстрое возведение в степень в нерекурсивном виде:
        Residue r(1), a(x);
        while (n > 0) {
            if (n % 2 == 1)
                r *= a;
            a *= a;
            n >>= 1;
        }
        return r;
    }
    
    // деление через возведение в степень:
    Residue operator/(const Residue &rhs) const {
        return *this * (rhs ^ -1); // это не ксор, а возведение в степень, которую мы переопределили
    }
    
    // те же операторы но с модификацией:
    Residue &operator^=(const int n) { return *this = *this ^ n; }
    Residue &operator/=(const Residue &rhs) { return *this = *this / rhs; }
    
    // сравнение (C++20: operator <=> генерирует все сам компараторы):
    auto operator<=>(const Residue &rhs) const {
        return x <=> rhs.x; // используем реализованный operator<=> для int
    }
    
    template<typename Int>
    Residue &read(std::istream &is) {
        Int val; is >> val;
        return *this = Residue(val);
    }
    
    // ввод из потока через int64_t (осторожно с TLE: быстрее читать как int через read<int>)
    friend std::istream &operator>>(std::istream &is, Residue &r) {
        r.read<int64_t>(is);
        return is;
    }
    
    // вывод в поток:
    friend std::ostream &operator<<(std::ostream &os, const Residue &r) {
        return os << r.x;
    }
    
};

const int mod = (int)1e9+7;
using Res = Residue<mod>;

int main() {
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(0);
    Res a, b;;
    cin >> a >> b;
    cout << a / b;
}