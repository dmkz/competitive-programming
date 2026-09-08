#ifndef __NTT_HPP__
#define __NTT_HPP__
/*******************************************************************************************
 * The file "ntt.hpp" is a part of competitive programming C++ library "algos".            *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
namespace algos {
namespace numeric {
template<int mod, int primRoot>
struct NTT {
    static const int NAIVE_LIMIT = 60;
    using Poly = vi;
    int normalize(ll x) const {
        x %= mod;
        if (x < 0) x += mod;
        return (int)x;
    }
    void normalize(Poly &a) const {
        for (auto &x : a)
            x = normalize(x);
    }
    // Applies the forward or inverse number-theoretic transform in-place.
    // The vector size must be a power of two dividing mod-1.
    void transform(Poly &a, bool inverse = false) const {
        int n = isz(a);
        assert(n > 0 && (n & (n-1)) == 0);
        assert((mod-1)%n == 0);
        normalize(a);
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            while (j & bit) j ^= bit, bit >>= 1;
            j ^= bit;
            if (i < j) std::swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
            int wlen = powmod(primRoot, (mod-1)/len, mod);
            if (inverse) wlen = powmod(wlen, mod-2, mod);
            for (int i = 0; i < n; i += len) {
                int w = 1;
                for (int j = 0; j < len/2; j++) {
                    int u = a[i+j];
                    int v = mulmod(a[i+j+len/2], w, mod);
                    a[i+j] = addmod(u, v, mod);
                    a[i+j+len/2] = submod(u, v, mod);
                    w = mulmod(w, wlen, mod);
                }
            }
        }
        if (inverse) {
            int invN = powmod(n, mod-2, mod);
            for (auto &x : a)
                x = mulmod(x, invN, mod);
        }
    }
    // Multiplies two polynomials and optionally keeps only the first limit coefficients.
    // A negative limit means that the complete product is returned.
    Poly multiply(Poly a, Poly b, int limit = -1) const {
        if (a.empty() || b.empty() || limit == 0) return {};
        if (limit > 0) {
            if (isz(a) > limit) a.resize(limit);
            if (isz(b) > limit) b.resize(limit);
        }
        normalize(a), normalize(b);
        int fullSize = isz(a)+isz(b)-1;
        int resultSize = (limit < 0 ? fullSize : std::min(fullSize, limit));
        if (std::min(isz(a), isz(b)) <= NAIVE_LIMIT) {
            Poly result(resultSize);
            for (int i = 0; i < isz(a); i++)
                for (int j = 0; j < isz(b) && i+j < resultSize; j++)
                    result[i+j] = int((result[i+j]+a[i]*1LL*b[j])%mod);
            return result;
        }
        int n = 1;
        while (n < fullSize) n <<= 1;
        assert((mod-1)%n == 0);
        a.resize(n), b.resize(n);
        transform(a), transform(b);
        for (int i = 0; i < n; i++)
            a[i] = mulmod(a[i], b[i], mod);
        return (transform(a, true), a.resize(resultSize), a);
    }
    // Convenient notation: ntt(a,b) returns the complete convolution.
    Poly operator()(const Poly &a, const Poly &b) const {
        return multiply(a, b);
    }
    // Convenient notation: ntt(a,b,limit) returns the first limit coefficients.
    Poly operator()(const Poly &a, const Poly &b, int limit) const {
        return multiply(a, b, limit);
    }
    // Squares a polynomial and optionally keeps only the first limit coefficients.
    Poly square(Poly a, int limit = -1) const {
        if (a.empty() || limit == 0) return {};
        if (limit > 0 && isz(a) > limit) a.resize(limit);
        normalize(a);
        int fullSize = 2*isz(a)-1;
        int resultSize = (limit < 0 ? fullSize : std::min(fullSize, limit));
        if (isz(a) <= NAIVE_LIMIT) {
            Poly result(resultSize);
            for (int i = 0; i < isz(a); i++)
                for (int j = 0; j < isz(a) && i+j < resultSize; j++)
                    result[i+j] = int((result[i+j]+a[i]*1LL*a[j])%mod);
            return result;
        }
        int n = 1;
        while (n < fullSize) n <<= 1;
        assert((mod-1)%n == 0);
        a.resize(n), transform(a);
        for (auto &x : a) x = mulmod(x, x, mod);
        return (transform(a, true), a.resize(resultSize), a);
    }
    // Multiplies polynomials modulo x^n-1.
    // Coefficients with equal indices modulo n are folded together.
    Poly cyclic(const Poly &a, const Poly &b, int n) const {
        assert(n > 0);
        Poly x(n), y(n);
        for (int i = 0; i < isz(a); i++)
            x[i%n] = addmod(x[i%n], normalize(a[i]), mod);
        for (int i = 0; i < isz(b); i++)
            y[i%n] = addmod(y[i%n], normalize(b[i]), mod);
        Poly product = multiply(x, y), result(n);
        for (int i = 0; i < isz(product); i++)
            result[i%n] = addmod(result[i%n], product[i], mod);
        return result;
    }
};
using NTT998244353 = NTT<998244353, 3>;
} // namespace numeric
} // namespace algos
#endif // __NTT_HPP__
#ifndef __TREE_HPP__
#define __TREE_HPP__