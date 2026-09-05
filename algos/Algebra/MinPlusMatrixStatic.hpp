#ifndef __MINPLUSMATRIXSTATIC_HPP__
#define __MINPLUSMATRIXSTATIC_HPP__
// The file "MinPlusMatrixStatic.hpp" is a part of library "algos", written by dmkz.
// You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos
#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
namespace algos {
namespace Matrix {
/**
 * A statically allocated square matrix over the min-plus semiring.
 *
 * Addition in this semiring is the minimum operation:
 *
 *     a (+) b = min(a, b)
 *
 * Multiplication in this semiring is ordinary addition:
 *
 *     a (*) b = a + b
 *
 * Therefore, matrix multiplication is defined as:
 *
 *     C[i][j] = min(A[i][k] + B[k][j]) over all k
 *
 * The matrix has compile-time capacity `Capacity` and runtime dimension
 * `size`. All matrices with the same template parameters share the runtime
 * dimension.
 *
 * Elements are stored in column-major order. Thus, all elements of one
 * column occupy a contiguous memory range.
 *
 * `Infinity` is the additive neutral element of the min-plus semiring.
 * All finite additions performed by the class must fit into type `T`.
 */
template<typename T = long long, T Infinity = std::numeric_limits<T>::max()/4, int Capacity = 10>
struct MinPlusMatrix {
    /**
     * Public constants, runtime matrix dimension and static storage.
     */
    static constexpr int capacity = Capacity;
    static constexpr T infinity = Infinity;
    static inline int n = Capacity;
    T data[Capacity*Capacity];
    /**
     * Constructs a matrix of the currently configured dimension filled with
     * infinity.
     *
     * If `diagonal` is finite, all diagonal elements are initialized with it.
     */
    explicit MinPlusMatrix(T diagonal = infinity) {
        fill(infinity);
        if (diagonal < infinity)
            for (int i = 0; i < n; i++)
                operator()(i,i) = diagonal;
    }
    /**
     * Sets the runtime dimension shared by this matrix specialization.
     */
    static void setSize(int n_) {
        assert(1 <= n_ && n_ <= Capacity);
        n = n_;
    }
    /**
     * Returns the current runtime dimension.
     */
    static int getSize() {
        return n;
    }
    /**
     * Returns the additive neutral matrix of the current dimension.
     */
    static MinPlusMatrix neutral() {
        return MinPlusMatrix();
    }
    /**
     * Sets the runtime dimension and returns its additive neutral matrix.
     */
    static MinPlusMatrix neutral(int n_) {
        setSize(n_);
        return neutral();
    }
    /**
     * Returns the multiplicative identity matrix of the current dimension.
     */
    static MinPlusMatrix identity() {
        return MinPlusMatrix(T(0));
    }
    /**
     * Sets the runtime dimension and returns its multiplicative identity
     * matrix.
     */
    static MinPlusMatrix identity(int n_) {
        setSize(n_);
        return identity();
    }
    /**
     * Returns a mutable reference to element (row, column).
     */
    T &operator()(int row, int column) {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[column*n+row];
    }
    /**
     * Returns a constant reference to element (row, column).
     */
    const T &operator()(int row, int column) const {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[column*n+row];
    }
    /**
     * Returns a pointer to the first element of a column.
     */
    T *columnData(int column) {
        assert(0 <= column && column < n);
        return data+column*n;
    }
    /**
     * Returns a constant pointer to the first element of a column.
     */
    const T *columnData(int column) const {
        assert(0 <= column && column < n);
        return data+column*n;
    }
    /**
     * Fills all active matrix elements with the specified value.
     */
    void fill(T value) {
        std::fill(data,data+n*n,value);
    }
    /**
     * Computes min-plus matrix multiplication.
     *
     * The loop order is optimized for column-major storage. The innermost
     * loop reads one contiguous column of `left` and updates one contiguous
     * column of the result.
     */
    friend MinPlusMatrix operator*(const MinPlusMatrix &left, const MinPlusMatrix &right) {
        MinPlusMatrix result;
        for (int j = 0; j < n; j++) {
            T *resultColumn = result.columnData(j);
            const T *rightColumn = right.columnData(j);
            for (int k = 0; k < n; k++) {
                T rightValue = rightColumn[k];
                if (rightValue >= infinity) continue;
                const T *leftColumn = left.columnData(k);
                for (int i = 0; i < n; i++)
                    if (leftColumn[i] < infinity)
                        resultColumn[i] = std::min(resultColumn[i],leftColumn[i]+rightValue);
            }
        }
        return result;
    }
    /**
     * Multiplies this matrix by another matrix in the min-plus semiring.
     */
    MinPlusMatrix &operator*=(const MinPlusMatrix &other) {
        return *this = *this*other;
    }
    /**
     * Applies the matrix to a column vector stored in an array.
     */
    void apply(T *vector) const {
        T result[Capacity];
        std::fill(result,result+n,infinity);
        for (int j = 0; j < n; j++) {
            T vectorValue = vector[j];
            if (vectorValue >= infinity) continue;
            const T *column = columnData(j);
            for (int i = 0; i < n; i++)
                if (column[i] < infinity)
                    result[i] = std::min(result[i],column[i]+vectorValue);
        }
        std::copy(result,result+n,vector);
    }
    /**
     * Applies the matrix to a dynamically allocated column vector.
     */
    void apply(std::vector<T> &vector) const {
        assert((int)vector.size() == n);
        apply(vector.data());
    }
    /**
     * Applies the matrix to a column vector stored in an array.
     */
    void operator()(T *vector) const {
        apply(vector);
    }
    /**
     * Applies the matrix to a dynamically allocated column vector.
     */
    void operator()(std::vector<T> &vector) const {
        apply(vector);
    }
    /**
     * Applies an arbitrary in-place transformation to every matrix column.
     *
     * Each column is stored contiguously and is passed directly to the
     * callable without creating a temporary buffer.
     */
    template<typename Function>
    void transformColumns(Function transform) {
        for (int j = 0; j < n; j++)
            transform(columnData(j));
    }
};
/**
 * Traits for storing composed min-plus transformations in a segment tree.
 *
 * The matrix dimension must be configured with setSize before constructing
 * or building the segment tree.
 *
 * If `lhs` represents an earlier segment and `rhs` represents a later
 * segment, their combined transformation is `rhs * lhs`.
 */
template<typename MatrixType>
struct TraitsMinPlusCompose {
    static inline int size = 0;
    /**
     * Sets the matrix dimension used by neutral transformations.
     */
    static void setSize(int size_) {
        assert(size_ > 0);
        size = size_;
        MatrixType::setSize(size);
    }
    /**
     * Returns the multiplicative identity transformation.
     */
    static MatrixType neutral() {
        assert(size > 0);
        return MatrixType::identity(size);
    }
    /**
     * Replaces an item with a new transformation.
     */
    static void update(MatrixType &dst, const MatrixType &src) {
        dst = src;
    }
    /**
     * Composes transformations of two consecutive segments.
     */
    static void merge(MatrixType &dst, const MatrixType &lhs, const MatrixType &rhs) {
        dst = rhs*lhs;
    }
};
} // namespace Matrix
} // namespace algos
#endif // __MINPLUSMATRIXSTATIC_HPP__