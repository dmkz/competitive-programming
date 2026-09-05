#ifndef __MINPLUSMATRIX_HPP__
#define __MINPLUSMATRIX_HPP__
// File "MinPlusMatrix.hpp" is a part of library "algos", written by dmkz.
// You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos
#include <algorithm>
#include <cassert>
#include <limits>
#include <vector>
namespace algos {
namespace Matrix {
/**
 * A dynamically sized square matrix over the min-plus semiring.
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
 * The matrix dimension is specified in the constructor. A matrix of size n
 * allocates exactly n * n elements.
 *
 * Elements are stored in column-major order. Thus, all elements of one
 * column occupy a contiguous memory range. Element (row, column) is stored
 * at index:
 *
 *     column * size + row
 *
 * `Infinity` is the additive neutral element of the min-plus semiring.
 * All finite additions performed by the class must fit into type `T`.
 */
template<typename T = long long, T Infinity = std::numeric_limits<T>::max()/4>
struct MinPlusMatrix {
    /**
     * Public matrix dimension, infinity value and storage.
     */
    int n = 0;
    static constexpr T infinity = Infinity;
    std::vector<T> data;
    /**
     * Constructs an empty matrix.
     *
     * This constructor is useful for containers. Arithmetic operations
     * require matrices with equal positive dimensions.
     */
    MinPlusMatrix() = default;
    /**
     * Constructs an n by n matrix filled with infinity.
     *
     * If `diagonal` is finite, all diagonal elements are initialized with it.
     * In particular, MinPlusMatrix(n, T(0)) constructs an identity matrix.
     */
    explicit MinPlusMatrix(int n_, T diagonal = infinity)
        : n(n_), data((std::size_t)n_*n_,infinity)
    {
        assert(n >= 0);
        if (diagonal < infinity)
            for (int i = 0; i < n; i++)
                operator()(i,i) = diagonal;
    }
    /**
     * Returns the matrix dimension.
     */
    int size() const {
        return n;
    }
    /**
     * Returns the additive neutral matrix of the specified dimension.
     *
     * Every element of this matrix is infinity.
     */
    static MinPlusMatrix neutral(int n) {
        return MinPlusMatrix(n);
    }
    /**
     * Returns the multiplicative identity matrix of the specified dimension.
     *
     * Its diagonal elements are zero and all other elements are infinity.
     */
    static MinPlusMatrix identity(int n) {
        return MinPlusMatrix(n,T(0));
    }
    /**
     * Returns a mutable reference to element (row, column).
     */
    T &operator()(int row, int column) {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[(std::size_t)column*n+row];
    }
    /**
     * Returns a constant reference to element (row, column).
     */
    const T &operator()(int row, int column) const {
        assert(0 <= row && row < n);
        assert(0 <= column && column < n);
        return data[(std::size_t)column*n+row];
    }
    /**
     * Returns a pointer to the first element of a column.
     *
     * The returned range [columnData(column), columnData(column) + n)
     * is contiguous in memory.
     */
    T *columnData(int column) {
        assert(0 <= column && column < n);
        return data.data()+(std::size_t)column*n;
    }
    /**
     * Returns a constant pointer to the first element of a column.
     */
    const T *columnData(int column) const {
        assert(0 <= column && column < n);
        return data.data()+(std::size_t)column*n;
    }
    /**
     * Fills all matrix elements with the specified value.
     */
    void fill(T value) {
        std::fill(data.begin(),data.end(),value);
    }
    /**
     * Computes min-plus matrix multiplication.
     *
     * For `left * right`, the resulting matrix satisfies:
     *
     *     result[i][j] =
     *         min(left[i][k] + right[k][j]) over all k
     *
     * The loop order is chosen for column-major storage:
     *
     *     result column -> intermediate index -> row
     *
     * The innermost loop accesses contiguous columns of `left` and `result`.
     */
    friend MinPlusMatrix operator*(const MinPlusMatrix &left, const MinPlusMatrix &right) {
        assert(left.n == right.n);
        int n = left.n;
        MinPlusMatrix result(n);
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
     * Applies the matrix to a column vector in place.
     *
     * The input array must contain at least n elements. The resulting vector
     * satisfies:
     *
     *     result[i] =
     *         min(matrix[i][j] + vector[j]) over all j
     *
     * The input and output vectors may refer to the same array.
     */
    void apply(T *vector) const {
        std::vector<T> result(n,infinity);
        for (int j = 0; j < n; j++) {
            T vectorValue = vector[j];
            if (vectorValue >= infinity) continue;
            const T *column = columnData(j);
            for (int i = 0; i < n; i++)
                if (column[i] < infinity)
                    result[i] = std::min(result[i],column[i]+vectorValue);
        }
        std::copy(result.begin(),result.end(),vector);
    }
    /**
     * Applies the matrix to a vector in place.
     *
     * The vector size must be equal to the matrix dimension.
     */
    void apply(std::vector<T> &vector) const {
        assert((int)vector.size() == n);
        apply(vector.data());
    }
    /**
     * Applies the matrix to a column vector in place.
     *
     * This operator is equivalent to calling apply(vector).
     */
    void operator()(T *vector) const {
        apply(vector);
    }
    /**
     * Applies the matrix to a vector in place.
     *
     * This operator is equivalent to calling apply(vector).
     */
    void operator()(std::vector<T> &vector) const {
        apply(vector);
    }
    /**
     * Applies an arbitrary in-place transformation to every matrix column.
     *
     * The callable must accept a pointer to n contiguous elements:
     *
     *     transform(T *column)
     *
     * No temporary column buffers or additional copies are created.
     */
    template<typename Function>
    void transformColumns(Function transform) {
        for (int j = 0; j < n; j++)
            transform(columnData(j));
    }
};
/**
 * Traits for storing composed dynamically sized min-plus transformations
 * in a segment tree.
 *
 * The matrix dimension must be configured with setSize before constructing
 * or building the segment tree.
 *
 * If `lhs` represents an earlier segment and `rhs` represents a later
 * segment, their combined transformation is:
 *
 *     rhs * lhs
 *
 * because a column vector is first multiplied by `lhs` and then by `rhs`.
 */
template<typename MatrixType>
struct TraitsMinPlusCompose {
    static inline int size = 0;
    /**
     * Sets the dimension used to construct neutral matrices.
     */
    static void setSize(int size_) {
        assert(size_ > 0);
        size = size_;
    }
    /**
     * Returns the multiplicative identity transformation.
     */
    static MatrixType neutral() {
        assert(size > 0);
        return MatrixType::identity(size);
    }
    /**
     * Replaces a segment tree item with a new transformation.
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
#endif // __MINPLUSMATRIX_HPP__