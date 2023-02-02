#ifndef __ALGEBRA_HPP__
#define __ALGEBRA_HPP__

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
} // namespace algebra
} // namespace algos
namespace std {
    template<typename T>
    auto begin(const algos::algebra::XorBasis<T>& basis) { return basis.begin(); }
    template<typename T>
    auto begin(algos::algebra::XorBasis<T>& basis) { return basis.begin(); }
    template<typename T>
    auto end(const algos::algebra::XorBasis<T>& basis) { return basis.begin(); }
    template<typename T>
    auto end(algos::algebra::XorBasis<T>& basis) { return basis.begin(); }
    template<typename T>
    auto size(const algos::algebra::XorBasis<T>& basis) { return basis.size(); }
}
#endif // __ALGEBRA_HPP__