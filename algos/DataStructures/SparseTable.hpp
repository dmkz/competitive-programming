// problem: 818E
#pragma once
#include <bits/stdc++.h>

#ifndef isz
#define isz(x) (int)std::size(x)
#endif

template<typename T, typename Func, bool useFunctor = false>
struct SparseTable {

    std::vector<std::vector<T>> data;

    Func func;

    SparseTable(const Func &func_ = Func())
        : func(func_)
    {}
    
    SparseTable(const auto &vec, const Func &func_ = Func())
        : func(func_)
    { build(vec); }
    
    void build(const auto &a) {
        data.assign(std::__lg(isz(a))+1, a);
        for (int p = 1; p < isz(data); p++)
            for (int i = 0; i + (1 << p) - 1 < isz(a); i++)
                data[p][i] = getFunc()
                (
                    data[p-1][i],
                    data[p-1][i+(1<<(p-1))]
                );
    }

    Func getFunc() const {
        return (useFunctor ? func : Func());
    }

    T calcFunc(int L, int R) const {
        assert(L <= R); // отрезок [L, R] - корректный
        const int p = std::__lg(R-L+1);
        return getFunc()(data[p][L], data[p][R+1-(1<<p)]);
    }
    
    T calcFuncInLog(int L, int R) const {
        T value = getFunc().neutral();
        for (int len = R - L + 1, bit = std::__lg(len); bit >= 0; bit--) {
            if ((len >> bit) & 1) {
                value = getFunc()(value, data[bit][L]);
                L += (1 << bit);
            }
        }
        return value;
    }
    
    int binary_lifting(int pos, auto decideMoveRight) const {
        T value = getFunc().neutral();
        for (int p = isz(data)-1; p >= 0; p--) {
            if (pos + (1 << p) - 1 >= isz(data[p]))
                continue; // вышли за пределы массива
            T nextValue = getFunc()(value, data[p][pos]);
            if (decideMoveRight(nextValue)) {
                pos += (1 << p);
                value = nextValue;
            }
        }
        return pos;
    }
    
};

struct MultByModulo {
    
    int mod;
    
    MultByModulo(int mod_ = 0) : mod(mod_) { }
    
    int neutral() const {
        return 1 % mod;
    }
    
    int operator()(int left, int right) const {
        return int((left * 1LL * right) % mod);
    }
    
};

bool extendIfNonZero(int prod) {
    return prod != 0;
}

template<typename T>
struct Min {
    T neutral() const {
        return std::numeric_limits<T>::max();
    }
    T operator()(const T&a, const T&b) const {
        return std::min(a, b);
    }
};

template<typename T>
struct Max {
    T neutral() const {
        return std::numeric_limits<T>::min();
    }
    T operator()(const T&a, const T&b) const {
        return std::max(a, b);
    }
};