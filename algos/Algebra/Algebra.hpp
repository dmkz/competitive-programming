#ifndef __ALGEBRA_HPP__
#define __ALGEBRA_HPP__
/*******************************************************************************************
 * The file "Algebra.hpp" is a part of competitive programming C++ library "algos".        *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
namespace algos {
namespace algebra {

template<typename T>
struct Tridiag {

    int n;
    
    std::vector<T> lower, mainDiag, upper, rhs, x;
    
    Tridiag(int n_)
        : n(n_), lower(n,T{}), mainDiag(n,T{})
        , upper(n,T{}), rhs(n,T{}), x(n,T{})
    { }
    
    T& A(int i, int j) {
        if (i == j) return mainDiag[i];
        if (i < j) return upper[i];
        return lower[i];
    }
    
    T& b(int i) { return rhs[i]; }
    
    auto getView() {
        return std::make_pair([&](int i, int j) -> T& { return A(i,j); },
                              [&](int i) -> T& { return b(i); });
    }
    
    const auto &solve() {
        for (int i = 1; i < n; i++)
        {
            auto temp = lower[i]/mainDiag[i-1];
            mainDiag[i] = mainDiag[i] - temp*upper[i-1];
            rhs[i] = rhs[i] - temp*rhs[i-1];
        }
        x[n-1] = rhs[n-1]/mainDiag[n-1];
        for (int i = n - 2; i >= 0; i--)
            x[i]=(rhs[i]-upper[i]*x[i+1])/mainDiag[i];
        return x;
    }
    
};
} // namespace algos
} // namespace algebra


namespace algos {
namespace algebra {
template<typename T>
struct XorBasis {
    
    T vec[sizeof(T) * 8]{};
    int sz{};
    
    T *begin() { return vec; }
    T *end() { return vec+sz; }
    
    const T *begin() const { return vec; }
    const T *end() const { return vec+sz; }
    int size() const { return sz; }
    
    XorBasis(T x = T{}) { (*this) += x; }
    
    bool add(T x) { return ({auto was = sz; (*this)+=x; sz > was;}); }
    
    XorBasis &operator+=(const XorBasis &other) {
        std::for_each(all(other), [&](auto x){*this+=x;});
        return *this;
    }
    XorBasis &operator+=(T x)
    {
        // subtract all vectors from x:
        for (int i = 0; i < sz; i++)
            if (int bit = std::__lg(vec[i]); x >> bit & 1)
                x ^= vec[i];
        // if rank is increased:
        if (x != T(0)) {
            // push back new vector:
            int xpos = sz++, xbit = std::__lg(x);
            vec[xpos] = x;
            // swap while leading bit is greater:
            while (xpos > 0 && std::__lg(vec[xpos-1]) < xbit)
                std::swap(vec[xpos-1],vec[xpos]), xpos--;
            // subtract x from all vectors before:
            for (int i = xpos-1; i >= 0; i--)
                if (vec[i] >> xbit & 1)
                    vec[i] ^= x;
        }
        return *this;
    }
    XorBasis operator+(const XorBasis &other) const {
        return XorBasis(*this) += other;
    }
    T max() const { return std::accumulate(vec,vec+sz,T(0),std::bit_xor<T>()); }
};
/*******************************************************************************
 * Return the binary reflected Gray code of x
 ******************************************************************************/
template<typename T>
T grayCode(T x) {
    return x ^ (x >> 1);
}
/*******************************************************************************
 * Enumerate all non-zero steps of an n-bit Gray code
 *
 * Consecutive states differ in exactly one bit.
 * The callback receives the changed bit and its new value.
 * The supported range is 0 <= n < 64.
 ******************************************************************************/
void forEachGrayCodeChange(int n, auto f) {
    ull prev = 0;
    for (ull step = 1; step < (ull(1) << n); step++) {
        ull curr = grayCode(step);
        int bit = __builtin_ctzll(curr ^ prev);
        f(bit,bool(curr >> bit & 1));
        prev = curr;
    }
}
} // namespace algebra
} // namespace algos
#endif // __ALGEBRA_HPP__