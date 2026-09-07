#ifndef __MINPLUSMATRIXSTATIC_HPP__
#define __MINPLUSMATRIXSTATIC_HPP__
/*******************************************************************************************
 * File "MinPlusMatrixStatic.hpp" is a part of competitive programming C++ library "algos" *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <limits>
#include <vector>
namespace algos {
namespace Matrix {
/**
 * A statically allocated square matrix over a semiring.
 *
 * `Select` combines alternative paths and `Extend` concatenates paths.
 * `SelectIdentity` is the neutral element of Select.
 * `ExtendIdentity` is the neutral element of Extend.
 *
 * Elements are stored in column-major order.
 */
template<typename T, T SelectIdentity, T ExtendIdentity, typename Select, typename Extend,
         int Capacity = 10>
struct SemiringMatrixStatic {
    static constexpr int capacity = Capacity;
    static constexpr T selectIdentity = SelectIdentity;
    static constexpr T extendIdentity = ExtendIdentity;
    static inline int n = Capacity;
    T data[Capacity*Capacity];
    explicit SemiringMatrixStatic(T diagonal = selectIdentity) {
        fill(selectIdentity);
        if (diagonal != selectIdentity)
            for (int i = 0; i < n; i++)
                operator()(i,i) = diagonal;
    }
    static void setSize(int n_) {
        assert(1 <= n_ && n_ <= Capacity);
        n = n_;
    }
    static int getSize() { return n; }
    static SemiringMatrixStatic neutral() {
        return SemiringMatrixStatic();
    }
    static SemiringMatrixStatic neutral(int n_) {
        setSize(n_);
        return neutral();
    }
    static SemiringMatrixStatic identity() {
        return SemiringMatrixStatic(extendIdentity);
    }
    static SemiringMatrixStatic identity(int n_) {
        setSize(n_);
        return identity();
    }
    T &operator()(int row, int column) {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[column*n+row];
    }
    const T &operator()(int row, int column) const {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[column*n+row];
    }
    T *columnData(int column) {
        assert(0 <= column && column < n);
        return data+column*n;
    }
    const T *columnData(int column) const {
        assert(0 <= column && column < n);
        return data+column*n;
    }
    void fill(T value) {
        std::fill(data,data+n*n,value);
    }
    friend bool operator==(const SemiringMatrixStatic &a, const SemiringMatrixStatic &b) {
        return std::equal(a.data,a.data+n*n,b.data);
    }
    friend bool operator!=(const SemiringMatrixStatic &a, const SemiringMatrixStatic &b) {
        return !(a == b);
    }
    friend SemiringMatrixStatic operator*(const SemiringMatrixStatic &left,
                                          const SemiringMatrixStatic &right)
    {
        SemiringMatrixStatic result;
        Select select;
        Extend extend;
        for (int j = 0; j < n; j++) {
            T *resultColumn = result.columnData(j);
            const T *rightColumn = right.columnData(j);
            for (int k = 0; k < n; k++) {
                T rightValue = rightColumn[k];
                if (rightValue == selectIdentity) continue;
                const T *leftColumn = left.columnData(k);
                for (int i = 0; i < n; i++)
                    if (leftColumn[i] != selectIdentity)
                        resultColumn[i] = select(resultColumn[i],
                                                 extend(leftColumn[i],rightValue));
            }
        }
        return result;
    }
    SemiringMatrixStatic &operator*=(const SemiringMatrixStatic &other) {
        return *this = *this*other;
    }
    void apply(T *vector) const {
        T result[Capacity];
        std::fill(result,result+n,selectIdentity);
        Select select;
        Extend extend;
        for (int j = 0; j < n; j++) {
            T vectorValue = vector[j];
            if (vectorValue == selectIdentity) continue;
            const T *column = columnData(j);
            for (int i = 0; i < n; i++)
                if (column[i] != selectIdentity)
                    result[i] = select(result[i],extend(column[i],vectorValue));
        }
        std::copy(result,result+n,vector);
    }
    template<std::size_t N>
    void apply(std::array<T,N> &vector) const {
        assert((int)N >= n);
        apply(vector.data());
    }
    void apply(std::vector<T> &vector) const {
        assert((int)vector.size() == n);
        apply(vector.data());
    }
    void operator()(T *vector) const { apply(vector); }
    template<std::size_t N>
    void operator()(std::array<T,N> &vector) const { apply(vector); }
    void operator()(std::vector<T> &vector) const { apply(vector); }
    template<typename Function>
    void transformColumns(Function transform) {
        for (int j = 0; j < n; j++)
            transform(columnData(j));
    }
    SemiringMatrixStatic transposed() const {
        SemiringMatrixStatic result;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                result(j,i) = operator()(i,j);
        return result;
    }
    SemiringMatrixStatic pow(long long exponent) const {
        assert(exponent >= 0);
        SemiringMatrixStatic base = *this;
        SemiringMatrixStatic result = identity();
        while (exponent > 0) {
            if (exponent&1) result *= base;
            base *= base;
            exponent >>= 1;
        }
        return result;
    }
};
/**
 * Minimum operation used as semiring addition.
 */
template<typename T>
struct Minimum {
    T operator()(const T &a, const T &b) const { return std::min(a,b); }
};
/**
 * Maximum operation used as semiring addition.
 */
template<typename T>
struct Maximum {
    T operator()(const T &a, const T &b) const { return std::max(a,b); }
};
/**
 * Ordinary addition used as semiring multiplication.
 */
template<typename T>
struct Plus {
    T operator()(const T &a, const T &b) const { return a+b; }
};
template<typename T = long long, T Infinity = std::numeric_limits<T>::max()/4,
         int Capacity = 10>
using MinPlusMatrix = SemiringMatrixStatic<T,Infinity,T(0),Minimum<T>,Plus<T>,Capacity>;
template<typename T = long long, T NegativeInfinity = std::numeric_limits<T>::lowest()/4,
         int Capacity = 10>
using MaxPlusMatrix = SemiringMatrixStatic<T, NegativeInfinity, T(0), Maximum<T>,
                                           Plus<T>, Capacity>;
/**
 * Traits for composing transformations in their array order.
 */
template<typename MatrixType>
struct TraitsCompose {
    static inline int size = 0;
    static void setSize(int size_) {
        assert(size_ > 0);
        size = size_;
        MatrixType::setSize(size);
    }
    static MatrixType neutral() {
        assert(size > 0);
        return MatrixType::identity(size);
    }
    static void update(MatrixType &dst, const MatrixType &src) {
        dst = src;
    }
    static void merge(MatrixType &dst, const MatrixType &lhs, const MatrixType &rhs) {
        dst = rhs*lhs;
    }
};
template<typename MatrixType>
using TraitsMinPlusCompose = TraitsCompose<MatrixType>;
} // namespace Matrix
} // namespace algos
#endif // __MINPLUSMATRIXSTATIC_HPP__