#ifndef __TREAP_HPP__
#define __TREAP_HPP__
#include <algorithm>
#include <cstdint>
#include <deque>
#include <limits>
#include <utility>
#include <vector>
/*******************************************************************************************
 * The file "Treap.hpp" is a part of competitive programming C++ library "algos".          *
 *                                                                                         *
 * It implements a randomized Cartesian tree which can be used both as:                    *
 *     1) an implicit treap, where elements are addressed by positions;                    *
 *     2) an ordered treap, where elements are addressed by keys.                          *
 *                                                                                         *
 * Traits define aggregation, lazy propagation, key extraction and key comparison.         *
 * Node pointers stay valid because nodes are stored in std::deque.                        *
 *******************************************************************************************/
namespace algos {
namespace treap {
    /*******************************************************************************
     * Default traits: subtree sum and addition to every value in a subtree.
     * Value, aggregate, lazy operation and key have the same type T.
     ******************************************************************************/
    template<typename T> struct SumAdd {
        using Agg = T; using Lazy = T; using Key = T;
        static Agg aggNeutral() { return Agg(0); }
        static Lazy lazyNeutral() { return Lazy(0); }
        static bool isLazyNeutral(const Lazy &x) { return x == lazyNeutral(); }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &value) { return value; }
        static Agg combine(const Agg &left, const T &value, const Agg &right) {
            return left + value + right;
        }
        static void apply(T &value, Agg &agg, const Lazy &lazy, int size) {
            value += lazy, agg += lazy * size;
        }
        static void compose(Lazy &current, const Lazy &added) {
            current += added;
        }
    };
    /*******************************************************************************
     * Subtree minimum and addition to every value in a subtree.
     ******************************************************************************/
    template<typename T> struct MinAdd {
        using Agg = T; using Lazy = T; using Key = T;
        static Agg aggNeutral() { return std::numeric_limits<T>::max(); }
        static Lazy lazyNeutral() { return Lazy(0); }
        static bool isLazyNeutral(const Lazy &x) { return x == lazyNeutral(); }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &value) { return value; }
        static Agg combine(const Agg &left, const T &value, const Agg &right) {
            return std::min(left, std::min(value, right));
        }
        static void apply(T &value, Agg &agg, const Lazy &lazy, int) {
            value += lazy, agg += lazy;
        }
        static void compose(Lazy &current, const Lazy &added) {
            current += added;
        }
    };
    /*******************************************************************************
     * Subtree maximum and addition to every value in a subtree.
     ******************************************************************************/
    template<typename T> struct MaxAdd {
        using Agg = T; using Lazy = T; using Key = T;
        static Agg aggNeutral() { return std::numeric_limits<T>::lowest(); }
        static Lazy lazyNeutral() { return Lazy(0); }
        static bool isLazyNeutral(const Lazy &x) { return x == lazyNeutral(); }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &value) { return value; }
        static Agg combine(const Agg &left, const T &value, const Agg &right) {
            return std::max(left, std::max(value, right));
        }
        static void apply(T &value, Agg &agg, const Lazy &lazy, int) {
            value += lazy, agg += lazy;
        }
        static void compose(Lazy &current, const Lazy &added) {
            current += added;
        }
    };
    /*******************************************************************************
     * Subtree sum and assignment of one value to every item in a subtree.
     * A separate flag is needed because assignment to zero is a valid operation.
     ******************************************************************************/
    template<typename T>
    struct SumSet {
        struct Lazy {
            T value{}; bool has{};
            Lazy() { }
            Lazy(const T &value_) : value(value_), has(true) { }
        };
        using Agg = T; using Key = T;
        static Agg aggNeutral() { return Agg(0); }
        static Lazy lazyNeutral() { return Lazy(); }
        static bool isLazyNeutral(const Lazy &x) { return !x.has; }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &value) { return value; }
        static Agg combine(const Agg &left, const T &value, const Agg &right) {
            return left + value + right;
        }
        static void apply(T &value, Agg &agg, const Lazy &lazy, int size) {
            if (!lazy.has) return;
            value = lazy.value, agg = lazy.value * T(size);
        }
        static void compose(Lazy &current, const Lazy &added) {
            if (added.has) current = added;
        }
    };
    /*******************************************************************************
     * Subtree sum and mul&add transformation x := mul * x + add.
     *
     * If the current pending operation is f and a new operation is g, lazy
     * composition stores g(f(x)). Therefore:
     *     mul := current.mul * added.mul
     *     add := current.add * added.mul + added.add
     ******************************************************************************/
    template<typename T> struct SumMulAdd {
        struct Lazy {
            T mul{1}, add{};
            Lazy() { }
            Lazy(const T &mul_, const T &add_) : mul(mul_), add(add_) { }
        };
        using Agg = T; using Key = T;
        static Agg aggNeutral() { return Agg(0); }
        static Lazy lazyNeutral() { return Lazy(); }
        static bool isLazyNeutral(const Lazy &x) { return x.mul == T(1) && x.add == T(0); }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &value) { return value; }
        static Agg combine(const Agg &left, const T &value, const Agg &right) {
            return left + value + right;
        }
        static void apply(T &value, Agg &agg, const Lazy &lazy, int size) {
            value = value * lazy.mul + lazy.add;
            agg = agg * lazy.mul + lazy.add * T(size);
        }
        static void compose(Lazy &current, const Lazy &added) {
            current.add = current.add * added.mul + added.add;
            current.mul *= added.mul;
        }
    };
    /*******************************************************************************
     * Traits without useful aggregation or lazy propagation.
     * They are convenient for an ordinary ordered or implicit treap.
     ******************************************************************************/
    template<typename T> struct Basic {
        using Agg = int; using Lazy = int; using Key = T;
        static Agg aggNeutral() { return 0; }
        static Lazy lazyNeutral() { return 0; }
        static bool isLazyNeutral(const Lazy &) { return true; }
        static Key key(const T &value) { return value; }
        static bool less(const Key &a, const Key &b) { return a < b; }
        static Agg makeAgg(const T &) { return 0; }
        static Agg combine(const Agg &, const T &, const Agg &) { return 0; }
        static void apply(T &, Agg &, const Lazy &, int) { }
        static void compose(Lazy &, const Lazy &) { }
    };
    template<typename T, typename Traits = SumAdd<T>>
    struct Treap {
        using Agg = typename Traits::Agg;
        using Lazy = typename Traits::Lazy;
        using Key = typename Traits::Key;
        struct Node {
            Node *l{}, *r{};
            T value;
            Agg agg;
            Lazy lazy;
            int id{}, size{1};
            uint64_t priority{};
            bool reversed{};
            Node(const T &value_, int id_, uint64_t priority_)
                : value(value_), agg(Traits::makeAgg(value_)),
                  lazy(Traits::lazyNeutral()), id(id_), priority(priority_) {
            }
        };
        using Ptr = Node*;
        std::deque<Node> pool;
        int nextId{};
        static constexpr uint64_t RANDOM_ADD = 0x9e3779b97f4a7c15ULL;
        static constexpr uint64_t RANDOM_MUL1 = 0xbf58476d1ce4e5b9ULL;
        static constexpr uint64_t RANDOM_MUL2 = 0x94d049bb133111ebULL;
        static uint64_t splitmix64(uint64_t x) {
            x += RANDOM_ADD;
            x = (x ^ (x >> 30)) * RANDOM_MUL1;
            x = (x ^ (x >> 27)) * RANDOM_MUL2;
            return x ^ (x >> 31);
        }
        static int size(Ptr t) {
            return t ? t->size : 0;
        }
        static const Agg &aggRef(Ptr t) {
            if (t) return t->agg;
            static const Agg neutral = Traits::aggNeutral();
            return neutral;
        }
        static Agg agg(Ptr t) {
            return t ? t->agg : Traits::aggNeutral();
        }
        Ptr newNode(const T &value) {
            int id = nextId++;
            pool.emplace_back(value, id, splitmix64(uint64_t(id)+1));
            return &pool.back();
        }
        static void apply(Ptr t, const Lazy &lazy) {
            if (!t) return;
            Traits::apply(t->value, t->agg, lazy, t->size);
            Traits::compose(t->lazy, lazy);
        }
        static void reverse(Ptr t) {
            if (!t) return;
            std::swap(t->l, t->r);
            t->reversed = !t->reversed;
        }
        static void push(Ptr t) {
            if (!t) return;
            if (t->reversed) reverse(t->l), reverse(t->r), t->reversed = false;
            if (!Traits::isLazyNeutral(t->lazy)) {
                apply(t->l, t->lazy), apply(t->r, t->lazy);
                t->lazy = Traits::lazyNeutral();
            }
        }
        static void pull(Ptr t) {
            if (!t) return;
            t->size = 1 + size(t->l) + size(t->r);
            t->agg = Traits::combine(aggRef(t->l), t->value, aggRef(t->r));
        }
        static Ptr merge(Ptr a, Ptr b) {
            if (!a) return b;
            if (!b) return a;
            push(a); push(b);
            if (a->priority > b->priority) {
                a->r = merge(a->r, b);
                return (pull(a), a);
            }
            b->l = merge(a, b->l);
            return (pull(b), b);
        }
        static void splitSize(Ptr t, int k, Ptr &a, Ptr &b) {
            if (!t) { a = b = nullptr; return; }
            push(t);
            if (size(t->l) >= k) {
                splitSize(t->l, k, a, t->l);
                pull(t), b = t;
            } else {
                splitSize(t->r, k-size(t->l)-1, t->r, b);
                pull(t), a = t;
            }
        }
        static bool lessKey(const Key &a, int aid, const Key &b, int bid) {
            if (Traits::less(a, b)) return true;
            if (Traits::less(b, a)) return false;
            return aid < bid;
        }
        static bool lessNode(Ptr t, const Key &key, int id) {
            return lessKey(Traits::key(t->value), t->id, key, id);
        }
        static void splitKeyId(Ptr t, const Key &key, int id, Ptr &a, Ptr &b) {
            if (!t) { a = b = nullptr; return; }
            push(t);
            if (lessNode(t, key, id)) {
                splitKeyId(t->r, key, id, t->r, b);
                pull(t), a = t;
            } else {
                splitKeyId(t->l, key, id, a, t->l);
                pull(t), b = t;
            }
        }
        static void splitKey(Ptr t, const Key &key, Ptr &a, Ptr &b) {
            splitKeyId(t, key, 0, a, b);
        }
        static void splitKeyUpper(Ptr t, const Key &key, Ptr &a, Ptr &b) {
            splitKeyId(t, key, std::numeric_limits<int>::max(), a, b);
        }
        static Ptr unite(Ptr a, Ptr b) {
            if (!a) return b;
            if (!b) return a;
            push(a), push(b);
            if (a->priority < b->priority) std::swap(a, b);
            Ptr x, y;
            splitKeyId(b, Traits::key(a->value), a->id, x, y);
            a->l = unite(a->l, x);
            a->r = unite(a->r, y);
            return (pull(a), a);
        }
        Ptr insertAt(Ptr root, int pos, const T &value) {
            Ptr a, b;
            splitSize(root, pos, a, b);
            return merge(a, merge(newNode(value), b));
        }
        Ptr insert(Ptr root, const T &value) {
            Ptr node = newNode(value), a, b;
            splitKeyId(root, Traits::key(value), node->id, a, b);
            return merge(a, merge(node, b));
        }
        static Ptr eraseAt(Ptr root, int pos) {
            Ptr a, b, c;
            splitSize(root, pos, a, b);
            splitSize(b, 1, b, c);
            return merge(a, c);
        }
        static Ptr kth(Ptr t, int k) {
            while (t) {
                push(t);
                int leftSize = size(t->l);
                if (k < leftSize) t = t->l;
                else if (k == leftSize) return t;
                else k -= leftSize+1, t = t->r;
            }
            return nullptr;
        }
        static int lowerBound(Ptr t, const Key &key) {
            int result = 0;
            while (t) {
                push(t);
                if (Traits::less(Traits::key(t->value), key)) {
                    result += size(t->l)+1;
                    t = t->r;
                } else t = t->l;
            }
            return result;
        }
        static int upperBound(Ptr t, const Key &key) {
            int result = 0;
            while (t) {
                push(t);
                if (!Traits::less(key, Traits::key(t->value))) {
                    result += size(t->l)+1;
                    t = t->r;
                } else t = t->l;
            }
            return result;
        }
        static int countLess(Ptr t, const Key &key) { return lowerBound(t, key); }
        static int countLessEqual(Ptr t, const Key &key) { return upperBound(t, key); }
        static Agg aggLess(Ptr t, const Key &key) {
            if (!t) return Traits::aggNeutral();
            push(t);
            if (Traits::less(Traits::key(t->value), key))
                return Traits::combine(aggRef(t->l), t->value, aggLess(t->r, key));
            return aggLess(t->l, key);
        }
        static Agg fold(Ptr &root, int l, int r) {
            Ptr a, b, c;
            splitSize(root, l, a, b);
            splitSize(b, r-l, b, c);
            Agg result = agg(b);
            root = merge(a, merge(b, c));
            return result;
        }
        static void applyRange(Ptr &root, int l, int r, const Lazy &lazy) {
            Ptr a, b, c;
            splitSize(root, l, a, b);
            splitSize(b, r-l, b, c);
            apply(b, lazy);
            root = merge(a, merge(b, c));
        }
        static void reverseRange(Ptr &root, int l, int r) {
            Ptr a, b, c;
            splitSize(root, l, a, b);
            splitSize(b, r-l, b, c);
            reverse(b);
            root = merge(a, merge(b, c));
        }
        static std::vector<T> toVector(Ptr root) {
            std::vector<T> result;
            result.reserve(size(root));
            toVector(root, result);
            return result;
        }
        static void toVector(Ptr t, std::vector<T> &result) {
            if (!t) return;
            push(t);
            toVector(t->l, result);
            result.push_back(t->value);
            toVector(t->r, result);
        }
    };
} // namespace treap
} // namespace algos
#endif // __TREAP_HPP__