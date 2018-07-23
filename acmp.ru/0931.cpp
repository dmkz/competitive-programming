/*
    Задача: 931. Две окружности - 2
    
    Решение: длинная арифметика, геометрия, окружность, окружность по трем точкам, O(n)
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/


#include <stdio.h>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <complex>
#include <climits>

const int BASE_DIGITS = 9;
const int BASE = 1000000000;

struct BigInt {
    
    int sign;
    std::vector<int> a;

    // -------------------- Constructors -------------------- 
    // Default constructor.
    BigInt() : sign(1) {}

    // Constructor from long long.
    BigInt(long long v) {
        *this = v;
    }
    BigInt& operator = (long long v) {
        sign = 1;
        if (v < 0) {
            sign = -1;
            v = -v;
        }
        a.clear();
        for (; v > 0; v = v / BASE)
            a.push_back(int(v % BASE));
        return *this;
    }

    // Copy constructor.
    BigInt(const BigInt& other) {
        sign = other.sign;
        a = other.a;
    }
    // Assignment operator using Copy-and-swap idiom.
    friend void swap(BigInt& a, BigInt& b) {
        std::swap(a.sign, b.sign);
        std::swap(a.a, b.a);
    }
    BigInt& operator = (BigInt other) {
        swap(*this, other);
        return *this;
    }
    BigInt(BigInt&& other) : BigInt() {
        swap(*this, other);
    }

    // Initialize from string.
    BigInt(const std::string& s) {
        read(s);
    }

    // -------------------- Input / Output --------------------
    void read(const std::string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-')
                sign = -sign;
            ++pos;
        }
        for (int i = (int)s.size() - 1; i >= pos; i -= BASE_DIGITS) {
            int x = 0;
            for (int j = std::max(pos, i - BASE_DIGITS + 1); j <= i; j++)
                x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend std::istream& operator>>(std::istream &stream, BigInt &v) {
        std::string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend std::ostream& operator<<(std::ostream &stream, const BigInt &v) {
        if (v.sign == -1 && !v.isZero())
            stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int) v.a.size() - 2; i >= 0; --i)
            stream << std::setw(BASE_DIGITS) << std::setfill('0') << v.a[i];
        return stream << std::setfill(' ');
    }

    // -------------------- Comparison --------------------
    bool operator<(const BigInt &v) const {
        if (sign != v.sign)
            return sign < v.sign;
        if (a.size() != v.a.size())
            return (int)a.size() * sign < (int)v.a.size() * v.sign;
        for (int i = ((int) a.size()) - 1; i >= 0; i--)
            if (a[i] != v.a[i])
                return a[i] * sign < v.a[i] * sign;
        return false;
    }

    bool operator>(const BigInt &v) const {
        return v < *this;
    }
    bool operator<=(const BigInt &v) const {
        return !(v < *this);
    }
    bool operator>=(const BigInt &v) const {
        return !(*this < v);
    }
    bool operator==(const BigInt &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigInt &v) const {
        return *this < v || v < *this;
    }

    // Returns:
    // 0 if |x| == |y|
    // -1 if |x| < |y|
    // 1 if |x| > |y|
    friend int __compare_abs(const BigInt& x, const BigInt& y) {
        if (x.a.size() != y.a.size()) {
            return x.a.size() < y.a.size() ? -1 : 1;
        }

        for (int i = ((int) x.a.size()) - 1; i >= 0; --i) {
            if (x.a[i] != y.a[i]) {
                return x.a[i] < y.a[i] ? -1 : 1;
            }
        }
        return 0;
    }

    // -------------------- Unary operator - and operators +- --------------------
    BigInt operator-() const {
        BigInt res = *this;
        if (isZero()) return res;

        res.sign = -sign;
        return res;
    }

    // Assumption: *this and v have same sign.
    void __internal_add(const BigInt& v) {
        if (a.size() < v.a.size()) {
            a.resize(v.a.size(), 0);
        }
        for (int i = 0, carry = 0; i < (int) std::max(a.size(), v.a.size()) || carry; ++i) {
            if (i == (int) a.size()) a.push_back(0);

            a[i] += carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] >= BASE;
            if (carry) a[i] -= BASE;
        }
    }

    // Assumption: *this and v have same sign, and |*this| >= |v|
    void __internal_sub(const BigInt& v) {
        for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
            a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
            carry = a[i] < 0;
            if (carry) a[i] += BASE;
        }
        this->trim();
    }

    BigInt operator += (const BigInt& v) {
        if (sign == v.sign) {
            __internal_add(v);
        } else {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
            }
        }
        return *this;
    }

    BigInt operator -= (const BigInt& v) {
        if (sign == v.sign) {
            if (__compare_abs(*this, v) >= 0) {
                __internal_sub(v);
            } else {
                BigInt vv = v;
                swap(*this, vv);
                __internal_sub(vv);
                this->sign = -this->sign;
            }
        } else {
            __internal_add(v);
        }
        return *this;
    }

    // Optimize operators + and - according to
    // https://stackoverflow.com/questions/13166079/move-semantics-and-pass-by-rvalue-reference-in-overloaded-arithmetic
    template< typename L, typename R >
        typename std::enable_if<
            std::is_convertible<L, BigInt>::value &&
            std::is_convertible<R, BigInt>::value &&
            std::is_lvalue_reference<R&&>::value,
            BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(std::forward<L>(l));
        result += r;
        return result;
    }
    template< typename L, typename R >
        typename std::enable_if<
            std::is_convertible<L, BigInt>::value &&
            std::is_convertible<R, BigInt>::value &&
            std::is_rvalue_reference<R&&>::value,
            BigInt>::type friend operator + (L&& l, R&& r) {
        BigInt result(std::move(r));
        result += l;
        return result;
    }

    template< typename L, typename R >
        typename std::enable_if<
            std::is_convertible<L, BigInt>::value &&
            std::is_convertible<R, BigInt>::value,
            BigInt>::type friend operator - (L&& l, R&& r) {
        BigInt result(std::forward<L>(l));
        result -= r;
        return result;
    }

    // -------------------- Operators * / % --------------------
    friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1) {
        assert(b1 > 0);  // divmod not well-defined for b < 0.

        int norm = BASE / (b1.a.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q = 0, r = 0;
        q.a.resize(a.a.size());

        for (int i = (int)a.a.size() - 1; i >= 0; i--) {
            r *= BASE;
            r += a.a[i];
            int s1 = (int)r.a.size() <= (int)b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = (int)r.a.size() <= (int)b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            long long d = ((int64_t) BASE * s1 + s2) / b.a.back();
            assert(0 <= d && d < INT_MAX);
            r -= b * (int)d;
            while (r < 0) {
                r += b, --d;
            }
            assert(0 <= d && d < BASE);
            q.a[i] = (int)d;
        }

        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        auto res = std::make_pair(q, r / norm);
        if (res.second < 0) res.second += b1;
        return res;
    }
    BigInt operator/(const BigInt &v) const {
        return divmod(*this, v).first;
    }

    BigInt operator%(const BigInt &v) const {
        return divmod(*this, v).second;
    }

    void operator/=(int v) {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        if (llabs(v) >= BASE) {
            *this /= BigInt(v);
            return ;
        }
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
            long long cur = a[i] + rem * (long long) BASE;
            a[i] = (int) (cur / v);
            rem = (int) (cur % v);
        }
        trim();
    }

    BigInt operator/(int v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.

        if (llabs(v) >= BASE) {
            return *this / BigInt(v);
        }
        BigInt res = *this;
        res /= v;
        return res;
    }
    void operator/=(const BigInt &v) {
        *this = *this / v;
    }

    int operator%(int v) const {
        assert(v > 0);  // operator / not well-defined for v <= 0.
        assert(v < BASE);
        int m = 0;
        for (int i = (int)a.size() - 1; i >= 0; --i)
            m = int((a[i] + m * (long long) BASE) % v);
        return m * sign;
    }

    void operator*=(int v) {
        if (llabs(v) >= BASE) {
            *this *= BigInt(v);
            return ;
        }
        if (v < 0)
            sign = -sign, v = -v;
        for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
            if (i == (int) a.size())
                a.push_back(0);
            long long cur = a[i] * (long long) v + carry;
            carry = (int) (cur / BASE);
            a[i] = (int) (cur % BASE);
        }
        trim();
    }

    BigInt operator*(int v) const {
        if (std::abs(v) >= BASE) {
            return *this * BigInt(v);
        }
        BigInt res = *this;
        res *= v;
        return res;
    }

    // Convert BASE 10^old --> 10^new.
    static std::vector<int> convert_base(const std::vector<int> &a, int old_digits, int new_digits) {
        std::vector<long long> p(std::max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int) p.size(); i++)
            p[i] = p[i - 1] * 10;
        std::vector<int> res;
        long long cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int) a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back(int(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int) cur);
        while (!res.empty() && !res.back())
            res.pop_back();
        return res;
    }

    static void fft(std::vector<std::complex<double> > & a, bool invert) {
        int n = (int) a.size();

        for (int i = 1, j = 0; i < n; ++i) {
            int bit = n >> 1;
            for (; j >= bit; bit >>= 1)
                j -= bit;
            j += bit;
            if (i < j)
                std::swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            double ang = 2 * 3.14159265358979323846 / len * (invert ? -1 : 1);
            std::complex<double> wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) {
                std::complex<double> w(1);
                for (int j = 0; j < len / 2; ++j) {
                    std::complex<double> u = a[i + j];
                    std::complex<double> v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
        if (invert)
            for (int i = 0; i < n; ++i)
                a[i] /= n;
    }

    static void multiply_fft(const std::vector<int> &a, const std::vector<int> &b, std::vector<int> &res) {
        std::vector<std::complex<double> > fa(a.begin(), a.end());
        std::vector<std::complex<double> > fb(b.begin(), b.end());
        int n = 1;
        while (n < (int) std::max(a.size(), b.size()))
            n <<= 1;
        n <<= 1;
        fa.resize(n);
        fb.resize(n);

        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; ++i)
            fa[i] *= fb[i];
        fft(fa, true);

        res.resize(n);
        long long carry = 0;
        for (int i = 0; i < n; ++i) {
            long long t = (long long) (fa[i].real() + 0.5) + carry;
            carry = t / 1000;
            res[i] = int(t % 1000);
        }
    }

    BigInt mul_simple(const BigInt &v) const {
        BigInt res;
        res.sign = sign * v.sign;
        res.a.resize(a.size() + v.a.size());
        for (int i = 0; i < (int) a.size(); ++i)
            if (a[i])
                for (int j = 0, carry = 0; j < (int) v.a.size() || carry; ++j) {
                    long long cur = res.a[i + j] + (long long) a[i] * (j < (int) v.a.size() ? v.a[j] : 0) + carry;
                    carry = (int) (cur / BASE);
                    res.a[i + j] = (int) (cur % BASE);
                }
        res.trim();
        return res;
    }

    typedef std::vector<long long> vll;

    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = (int)a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    res[i + j] += a[i] * b[j];
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++)
            a2[i] += a1[i];
        for (int i = 0; i < k; i++)
            b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int) a1b1.size(); i++)
            r[i] -= a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            r[i] -= a2b2[i];

        for (int i = 0; i < (int) r.size(); i++)
            res[i + k] += r[i];
        for (int i = 0; i < (int) a1b1.size(); i++)
            res[i] += a1b1[i];
        for (int i = 0; i < (int) a2b2.size(); i++)
            res[i + n] += a2b2[i];
        return res;
    }

    BigInt mul_karatsuba(const BigInt &v) const {
        std::vector<int> a6 = convert_base(this->a, BASE_DIGITS, 6);
        std::vector<int> b6 = convert_base(v.a, BASE_DIGITS, 6);
        vll a_(a6.begin(), a6.end());
        vll b_(b6.begin(), b6.end());
        while (a_.size() < b_.size())
            a_.push_back(0);
        while (b_.size() < a_.size())
            b_.push_back(0);
        while (a_.size() & (a_.size() - 1))
            a_.push_back(0), b_.push_back(0);
        vll c_ = karatsubaMultiply(a_, b_);
        BigInt res;
        res.sign = sign * v.sign;
        long long carry = 0;
        for (int i = 0; i < (int) c_.size(); i++) {
            long long cur = c_[i] + carry;
            res.a.push_back((int) (cur % 1000000));
            carry = cur / 1000000;
        }
        res.a = convert_base(res.a, 6, BASE_DIGITS);
        res.trim();
        return res;
    }

    void operator*=(const BigInt &v) {
        *this = *this * v;
    }
    BigInt operator*(const BigInt &v) const {
        if (a.size() * v.a.size() <= 1000111u) return mul_simple(v);
        if (a.size() > 500111u || v.a.size() > 500111u) return mul_fft(v);
        return mul_karatsuba(v);
    }

    BigInt mul_fft(const BigInt& v) const {
        BigInt res;
        res.sign = sign * v.sign;
        multiply_fft(convert_base(a, BASE_DIGITS, 3), convert_base(v.a, BASE_DIGITS, 3), res.a);
        res.a = convert_base(res.a, 3, BASE_DIGITS);
        res.trim();
        return res;
    }

    // -------------------- Misc --------------------
    BigInt abs() const {
        BigInt res = *this;
        res.sign *= res.sign;
        return res;
    }
    void trim() {
        while (!a.empty() && !a.back())
            a.pop_back();
        if (a.empty())
            sign = 1;
    }

    bool isZero() const {
        return a.empty() || (a.size() == 1 && !a[0]);
    }

    friend BigInt gcd(const BigInt &a, const BigInt &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend BigInt lcm(const BigInt &a, const BigInt &b) {
        return a / gcd(a, b) * b;
    }

    friend BigInt sqrt(const BigInt &a1) {
        BigInt a = a1;
        while (a.a.empty() || (int)a.a.size() % 2 == 1)
            a.a.push_back(0);

        int n = (int)a.a.size();

        int firstDigit = (int) std::sqrt((double) a.a[n - 1] * BASE + a.a[n - 2]);
        int norm = BASE / (firstDigit + 1);
        a *= norm;
        a *= norm;
        while (a.a.empty() || (int)a.a.size() % 2 == 1)
            a.a.push_back(0);

        BigInt r = (long long) a.a[n - 1] * BASE + a.a[n - 2];
        firstDigit = (int) std::sqrt((double) a.a[n - 1] * BASE + a.a[n - 2]);
        int q = firstDigit;
        BigInt res;

        for(int j = n / 2 - 1; j >= 0; j--) {
            for(; ; --q) {
                BigInt r1 = (r - (res * 2 * BigInt(BASE) + q) * q) * BigInt(BASE) * BigInt(BASE) + (j > 0 ? (long long) a.a[2 * j - 1] * BASE + a.a[2 * j - 2] : 0);
                if (r1 >= 0) {
                    r = r1;
                    break;
                }
            }
            res *= BASE;
            res += q;

            if (j > 0) {
                int d1 = res.a.size() + 2u < r.a.size() ? r.a[res.a.size() + 2] : 0;
                int d2 = res.a.size() + 1u < r.a.size() ? r.a[res.a.size() + 1] : 0;
                int d3 = res.a.size() < r.a.size() ? r.a[res.a.size()] : 0;
                long long temp = ((long long) d1 * BASE * BASE + (long long) d2 * BASE + d3) / (firstDigit * 2);
                assert(0 <= temp && temp < INT_MAX);
                q = (int)temp;
            }
        }

        res.trim();
        return res / norm;
    }
};

typedef BigInt Real;

struct Frac {
    
    Real p, q;
    
    Frac(Real p_ = 0, Real q_ = 1) : p(p_), q(q_) { normalize(); }

    Frac(Frac p_, Frac q_) {
        *this = p_ / q_;
    }
    
    void normalize() {
        if (q < 0) { p = -p; q = -q; }
    }
    
    inline Frac operator+(const Frac& f) const {
        return Frac(p * f.q + q * f.p, q * f.q);
    }
    
    inline Frac operator-(const Frac& f) const {
        return Frac(p * f.q - q * f.p, q * f.q);
    }
    
    inline Frac operator*(const Frac& f) const {
        return Frac(p * f.p, q * f.q);
    }
    
    inline Frac operator/(const Frac& f) const {
        return Frac(p * f.q, q * f.p);
    }
    
    inline bool operator==(const Frac& f) const {
        return p * f.q == q * f.p;
    }
    
    inline bool operator!=(const Frac& f) const {
        return !(*this == f);
    }
    
};

struct Point {
    Frac x, y;
    
    Point(Frac x_ = Frac(), Frac y_ = Frac()) : x(x_), y(y_) { }
    
    inline Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    
    inline Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    
    inline Point operator*(const Frac& f) const {
        return Point(x * f, y * f);
    }
    
    inline Point operator/(const Frac& f) const {
        return Point(x / f, y / f);
    }
    
    inline Frac norm2() const {
        return x * x + y * y;
    }
};

inline Frac det(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

inline bool get_circle_center(const Point& p1, const Point& p2, const Point& p3, Point& Ans) {
    auto d = det(p2 - p1, p3 - p1) * Real(2);
    if (d == Frac(0)) return false;
    auto T = Point(p1.norm2() - p2.norm2(), p1.norm2() - p3.norm2());
    auto x = Frac(det(T, Point(p1.y-p2.y, p1.y-p3.y)), d);
    auto y = Frac(det(Point(p1.x-p2.x, p1.x-p3.x), T), d);
    Ans = Point(x, y);
    return true;
}

inline bool same_circle_dist(const Point& C, const Point& A, const Point& B) {
    return (A-C).norm2() == (B-C).norm2();
}

int main() {
    int n; scanf("%d", &n);
    if (n == 2) {
        printf("1\n2\n");
        return 0;
    } else if (n == 3) {
        printf("1 2\n3\n");
        return 0;
    } else if (n == 4) {
        printf("1 2\n3 4\n");
        return 0;
    }
    
    std::vector<Point> pt(n);
    std::vector<int> id(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        pt[i] = Point(Real(x), Real(y));
        id[i] = i+1;
    }
    
    std::srand((uint64_t)std::time(0) ^ (uint64_t)new(char));
    for (int k = 0; k < n; ++k) {
        int i = std::rand() % n;
        int j = std::rand() % n;
        std::swap(pt[i], pt[j]);
        std::swap(id[i], id[j]);
    }
    
    int m = std::min(n, 5);
    bool success = false;
    
    std::vector<int> part, group1, group2;
    for (int i1 = 0; !success && i1 < m; ++i1) {
        for (int i2 = i1+1; !success && i2 < m; ++i2) {
            for (int i3 = i2+1; !success && i3 < m; ++i3) {
                Point C1, C2;
                if (!get_circle_center(pt[i1], pt[i2], pt[i3], C1)) continue;
                
                part.assign(n, 0);
                
                part[i1] = part[i2] = part[i3] = 1;
                for (int t = 0; t < n; ++t) {
                    if (!part[t] && same_circle_dist(C1, pt[i1], pt[t])) {
                        part[t] = 1;
                    }
                }
                
                int j1 = -1, j2 = -1, j3 = -1, t = 0;
                while (t < n && part[t]) ++t;
                if (t == n) { // All points at one circle
                    success = true;
                    //continue;
                }
                if (!success) {
                    j1 = t++; part[j1] = 2;
                    while (t < n && part[t]) ++t;
                    if (t == n) { // One point on another circle
                        success = true;
                        //continue;
                    }
                }
                if (!success) {
                    j2 = t++; part[j2] = 2;
                    while (t < n && part[t]) ++t;
                    if (t == n) { // Two points on another circle
                        success = true;
                        //continue;
                    }
                }
                if (!success) {
                    j3 = t++; part[j3] = 2; // Main case
                    if (!get_circle_center(pt[j1], pt[j2], pt[j3], C2)) continue;
                    success = true;
                    for (; t < n; ++t) {
                        if (part[t]) continue;
                        if (!same_circle_dist(C2, pt[j1], pt[t])) {
                            success = false;
                            break;
                        }
                        part[t] = 2;
                    }
                }
                if (success) {
                    for (t = 0; t < n; ++t) {
                        if (part[t] == 1) {
                            group1.push_back(t);
                        }
                        if (part[t] == 2 || (j1 != -1 && same_circle_dist(C2, pt[t], pt[j1]))) {
                            group2.push_back(t);
                        }
                    }
                }
                
            }
        }
    }
    assert(success);

    if (group2.empty()) {
        group2.push_back(0);
    }
    for (auto& it : group1) {
        printf("%d ", id[it]);
    }
    printf("\n");
    for (auto& it : group2) {
        printf("%d ", id[it]);
    }
    printf("\n");
    return 0;
}