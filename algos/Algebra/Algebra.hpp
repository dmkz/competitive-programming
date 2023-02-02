#ifndef __ALGEBRA_HPP__
#define __ALGEBRA_HPP__

namespace algos {
namespace algebra {
template<typename T>
struct XorBasis {
    
    T vec[sizeof(T) * 8]{};
    int sz{};
    
    bool add(T x) { return ({auto was = sz; (*this)+=x; sz > was;}); }

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
    
    T max() const { return std::accumulate(vec,vec+sz,T(0),std::bit_xor<T>()); }
};

} // namespace algebra
} // namespace algos
#endif // __ALGEBRA_HPP__