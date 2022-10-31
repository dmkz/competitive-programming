#include <bits/stdc++.h>
using namespace std;

namespace Numeric {
    template<typename T, typename N> 
    T pow(T a, N n) {
        T r(1);
        while (n > 0) {
            if (n & 1) { r *= a; }
            a *= a; n >>= 1;
        }
        return r;
    }
    template<int mod>
    struct IntMod {
        int value;
        IntMod(int value_ = 0) : value(value_) {
            if (value >= mod) value -= mod;
            if (value < 0) value += mod;
        }
        IntMod& operator+=(IntMod num) {
            value += num.value;
            if (value >= mod) value -= mod;
            return *this;
        }
        IntMod& operator-=(IntMod num) {
            value -= num.value;
            if (value < 0) value += mod;
            return *this;
        }
        IntMod operator+(IntMod num) const { return IntMod(*this) += num; }
        IntMod operator-(IntMod num) const { return IntMod(*this) -= num; }
        IntMod operator*(IntMod num) const { return IntMod(int(value * 1LL * num.value % mod)); }
        IntMod& operator*=(IntMod num) { return *this = *this * num; }
        IntMod operator/(IntMod num) const { return *this * pow(num, mod-2); }
        IntMod& operator/=(IntMod num) { return *this = *this / num; }
    };
    template<int mod> bool operator<(IntMod<mod> a,IntMod<mod> b) { return a.value < b.value; }
    template<int mod>
    std::ostream& operator<<(std::ostream& os, const IntMod<mod>& num) {
        return os << num.value;
    }
}

const int mod = (int)(1e9+7); // 1'000'000'000+7

using Rem = Numeric::IntMod<mod>;

const int NMAX = (int)1e6;

Rem fact[NMAX+1];

int main() {
    fact[0] = 1;
    for (int i = 1; i <= NMAX; i++) {
        fact[i] = fact[i-1] * i;
    }
    int n; std::string s;
    cin >> n >> s;
    map<char,int> count;
    for (int i =0; i < n; i++) count[s[i]]++;
    // считаем ответ:
    Rem answer = 1;
    for (char c = 'a'; c <= 'z'; c++) {
        answer /= fact[count[c]];
    }
    answer *= fact[n];
    cout << answer << endl;
}

