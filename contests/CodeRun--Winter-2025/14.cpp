#include <bits/stdc++.h>
using ll = long long;

// namespace modulo { // Класс модульной арифметики
template<int mod>
struct IntMod {
    int x;
    IntMod(ll x_ = 0) : x(int(x_ % mod)) { normalize(); }
    IntMod(int x_) : x(x_) { normalize(); }
    IntMod &normalize() {
        if (x < 0 || x >= mod)
            x %= mod;
        if (x < 0)
            x += mod;
        return *this;
    }
    IntMod &operator*=(const IntMod &im) {
        x = int(x * 1LL * im.x % mod);
        return *this;
    }
    IntMod operator*(const IntMod &im) const {
        return (IntMod(*this) *= im);
    }
    IntMod &operator+=(const IntMod &im) {
        x += im.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    IntMod operator+(const IntMod &im) const {
        return (IntMod(*this) += im);
    }
    IntMod &operator-=(const IntMod &im) {
        x -= im.x;
        if (x < 0) x += mod;
        return *this;
    }
    IntMod operator-(const IntMod &im) const {
        return (IntMod(*this) -= im);
    }
    IntMod operator-() const {
        int temp = -x;
        if (temp < 0) temp += mod;
        return IntMod(temp);
    }
    IntMod operator^(ll n) const {
        n %= mod-1;
        if (n < 0)
            n += mod-1;
        int res = 1, a = x;
        while (n > 0) {
            if (n % 2 == 1)
                res = int(res * 1LL * a % mod);
            a = int(a * 1LL * a % mod);
            n >>= 1;
        }
        return IntMod(res);
    }
    IntMod &operator/=(const IntMod &im) {
        return *this *= (im^(-1));
    }
    IntMod operator/(const IntMod &im) const {
        return (IntMod(*this) /= im);
    }
};
template<int mod>
std::ostream &operator<<(std::ostream &os, const IntMod<mod> &im) {
    return os << im.x;
}
template<int mod>
std::istream &operator>>(std::istream &is, IntMod<mod> &im) {
    ll x; is >> x;
    im = x;
    return is;
}
template<int mod> bool operator<(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x < b.x; }
template<int mod> bool operator>(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x > b.x; }
template<int mod> bool operator<=(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x <= b.x; }
template<int mod> bool operator>=(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x >= b.x; }
template<int mod> bool operator==(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x == b.x; }
template<int mod> bool operator!=(const IntMod<mod> &a, const IntMod<mod> &b) { return a.x != b.x; }
// } // класс модульной арифметики

// namespace fractions { // Класс рациональный дробей
template<typename T> T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
template<typename T> T abs(T x) { return x < 0 ? -x : x; }

template<typename T>
struct Frac {
    T p, q;
    Frac(T p_ = 0, T q_ = 1) : p(p_), q(q_) { normalize(); }
    bool isInteger() const {
        return q != 0 && p % q == 0;
    }
    Frac &normalize() {
        if (q < 0) p = -p, q = -q;
        if (p == 0) q = 1;
        T g = gcd(abs(p), q);
        assert(g != 0);
        p /= g;
        q /= g;
        return *this;
    }
    Frac &operator*=(const Frac &f) {
        p *= f.p;
        q *= f.q;
        return normalize();
    }
    Frac operator*(const Frac &f) const {
        return Frac(*this) *= f;
    }
    Frac &operator/=(const Frac &f) {
        p *= f.q;
        q *= f.p;
        return normalize();
    }
    Frac operator/(const Frac &f) const {
        return Frac(*this) /= f;
    }
    Frac operator-() const {
        Frac ret = *this;
        ret.p = -ret.p;
        return ret;
    }
    Frac operator+(const Frac &f) const {
        return Frac(p * f.q + f.p * q, q * f.q);
    }
    Frac &operator+=(const Frac &f) {
        return *this = *this + f;
    }
    Frac operator-(const Frac &f) const {
        return *this + (-f);
    }
    Frac &operator-=(const Frac &f) {
        return *this = *this - f;
    }
    Frac flip() const {
        return Frac(q, p);
    }
};
template<typename T> bool operator<(const Frac<T> &a, const Frac<T> &b) { return (a - b).p < 0; }
template<typename T> bool operator>(const Frac<T> &a, const Frac<T> &b) { return b < a; }
template<typename T> bool operator<=(const Frac<T> &a, const Frac<T> &b) { return !(a > b); }
template<typename T> bool operator>=(const Frac<T> &a, const Frac<T> &b) { return !(a < b); }
template<typename T> bool operator!=(const Frac<T> &a, const Frac<T> &b) { return a < b || b < a; }
template<typename T> bool operator==(const Frac<T> &a, const Frac<T> &b) { return !(a != b); }
// вывод __int128:
std::ostream &operator<<(std::ostream &os, __int128 x) {
    if (x < 0) os << "-", x = -x;
    char stack[40];
    int sz = 0;
    do {
        stack[sz++] = char(x % 10 + '0');
        x /= 10;
    } while (x > 0);
    while (sz > 0)
        os << stack[--sz];
    return os;
}
// вывод дроби:
template<typename T>
std::ostream &operator<<(std::ostream &os, const Frac<T> &f) {
    return os << f.p << "/" << f.q;
}
// быстрое возведение дроби в степень:
template<typename T>
Frac<T> binpow(Frac<T> q, ll n) {
    if (n == 0)
        return 1;
    if (q == Frac<T>(0) || q == Frac<T>(1))
        return q;
    if (n < 0) {
        q = q.flip();
        n = -n;
    }
    Frac<T> sign = 1;
    if (q < Frac<T>(0)) {
        q = -q;
        sign = (n % 2 == 0 ? +1 : -1);
    }
    Frac<T> res = 1;
    while (n > 0) {
        if (n % 2 == 1) res *= q;
        q *= q;
        n >>= 1;
    }
    return sign * res;
}
// } // Класс рациональный дробей

const int mod = (int)1e9+7;
using Int = IntMod<mod>;
using pll = std::pair<ll, ll>;
using vpll = std::vector<pll>;
using tlll = std::tuple<ll,ll,ll>;
using tllll = std::tuple<ll,ll,ll,ll>;
using vtllll = std::vector<tllll>;

// медленное решение полным перебором + сбор статистики:
template<bool debug = false>
Int slow(ll a, ll q, ll L, ll R) {
    using T = Frac<__int128>;
    std::map<tlll, std::vector<tllll>> data;
    Int res = 0;
    for (ll n = L; n <= R; n++)
        for (ll m = L; m <= R; m++) {
            T A = (binpow(T(q), n) * a - binpow(T(q), m) * a);
            for (ll k = L; k <= R; k++)
                for (ll s = L; s <= R; s++) {
                    T B = (binpow(T(q), k) * a - binpow(T(q), s) * a);
                    if (B.p != 0 && (A / B).isInteger()) {
                        if (debug) {
                            ll x = std::abs(k-s);
                            ll y = std::abs(n-m);
                            ll right = std::max(n, m);
                            data[{x,y,right}].emplace_back(n,m,k,s);
                        }
                        res += 1;
                    }
                }
        }
    if (debug) {
        for (const auto &[key,val] : data) {
            const auto &[x,y,right] = key;
            std::cout << "x = " << x << ", y = " << y << ", max = " << right << std::endl;
            for (auto &[n,m,k,s] : val) {
                std::cout << " (" << n << ", " << m << ", " << k << ", " << s << ")";
            }
            std::cout << std::endl;
        }
    }
    return res;
}

// Различные формулы для суммирования
Int ar(Int n) {
// 1 + 2 + ... + n
    static const Int inv2 = Int(1) / 2;
    return n * (n+1) * inv2;
}

Int sumArithmeticProgression(Int L, Int R) {
// L + (L+1) + ... + R
    return ar(R) - ar(L-1);
}

Int sumTriangles(Int n) {
// sum_{i=1}^{n} (i (i - 1) / 2) = 1/6 (n - 1) n (n + 1)
    return (n-1) * n * (n+1) / 6;
}
Int sumTrianglesWithStep(Int n, Int x, Int m) {
// sum_{i=1}^{m} (n-i*x) * (n-i*x-1)/2
    return (m*n*n)/2-m*n*(m*x+x+1)/2+m*(m+1)*x*(m*x*2+x+3)/12;
}
Int sumSquares(Int R) {
// 1^2 + 2^2 + ... + R^2
    static const Int inv6 = Int(1) / 6;
    return R * (R + 1) * (R * 2 + 1) * inv6;
}
Int sumSquares(Int L, Int R) {
// L^2 + (L+1)^2 + ... + R^2
    return sumSquares(R) - sumSquares(L-1);
}
// быстрое решение задачи за O(sqrt(N)):
template<bool debug = 0>
Int fast(ll a, ll q, ll L, ll R) {
    if (a == 0)
        return 0;
    ll N = R - L + 1;
    assert(N > 0); // мало ли
    if (q == 0) {
        if (!(L <= 0 && 0 <= R)) return 0;
        return (Int)N * N * (N-1) * 2;
    }
    if (q == 1)
        return 0;
    if (q == -1) {
        // значения только двух видов: a и -a
        Int cnt0 = (N + 1) / 2; // четные индексы
        Int cnt1 = N / 2; // нечетные индексы
        Int denom = cnt0 * cnt1 * 2;
        return (Int)N * N * denom;
    }
    // Числитель равен нулю:
    Int res = (Int)N * N * (N-1);
    // x = 1:
    if (1 < N) // любой y подходит
        res += sumTriangles(N) * 4;
    else
        return res;
    // x = 2:
    if (2 < N) {
        if (q == -2) {
            // подходит любой y:
            res += (sumTriangles(N) - sumTriangles(2)) * 4;
        } else {
            // подходит только кратный 2:
            res += sumTrianglesWithStep(N+1, 2, N / 2) * 4;
        }
    } else
        return res;
    // Теперь x >= 3
    // Далее ответ можно посчитать так:
    // for (ll x = 3; x < N; x++)
    //     for (ll y = x; y < N; y += x)
    //         sum += (N-y)*(N-y+1)/2;
    // sum *= 4
    // Мы будем ускорять вычисления, делая их за O(sqrt(N))
    Int sum = 0;
    const Int A = (Int)N*(N+1)/2;
    const Int B = (Int)1/12;
    const Int C = ((Int)N/2 + Int(1)/4);
    // от x < N переходим к N-1 путём N--;
    N--;
    // случай когда x <= [N / x]:
    for (ll x = 3; x * x <= N; x++) {
        ll m = N / x;
        if (x <= m) {
            sum += A * m;
            sum += B * x * x * m * (m + 1) * (2 * m + 1);
            sum -= C * x * m * (m+1);
        }
    }
    // случай когда x > [N / x]:
    for (ll m = 1; m * m <= N; m++) {
        // какие x дадут N / x = m? Минимальный: N/(m+1)+1. Максимальный: N / m
        ll xMax = N/m;
        ll xMin = std::max<ll>({m+1, 3, N/(m+1)+1});
        if (xMin <= xMax) {
            sum += A * m * (xMax - xMin + 1);
            sum += B * m * (m + 1) * (2 * m + 1) * sumSquares(xMin, xMax);
            sum -= C * m * (m + 1) * sumArithmeticProgression(xMin, xMax);
        }
    }
    return res + sum * 4;
}
// стресс тест:
void stress() {
    for (int len = 1; len <= 100; len++)
        for (int a = -2; a <= 2; a++)
            for (int q = -2; q <= 2; q++) {
                for (int L = -2*len; L + len - 1 <= 2*len; L++) {
                    int R = L + len - 1;
                    Int sl = slow(a,q,L,R);
                    Int ft = fast(a,q,L,R);
                    if (sl != ft) {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "a = " << a << std::endl;
                        std::cout << "q = " << q << std::endl;
                        std::cout << "L = " << L << std::endl;
                        std::cout << "R = " << R << std::endl;
                        std::cout << "len=" << len << std::endl;
                        std::cout << "sl = " << sl << std::endl;
                        std::cout << "ft = " << ft << std::endl;
                        slow<1>(a,q,L,R);
                        fast<1>(a,q,L,R);
                        std::exit(0);
                    }
                }
                std::cout << "a = " << a << ", q = " << q << ", len = " << len << ": OK" << std::endl;
            }
    std::exit(0);
}
void solve() {
    ll a, q, L, R;
    std::cin >> a >> q >> L >> R;
    Int res = fast(a,q,L,R);
    std::cout << res << std::endl;
}
main() {
    //stress();
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
