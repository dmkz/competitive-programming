#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__
/*******************************************************************************************
 * The file "Algorithm.hpp" is a part of competitive programming C++ library "algos".      *
 * You can find it here: https://github.com/dmkz/competitive-programming/tree/master/algos *
 *******************************************************************************************/
#include "template.hpp"
#include <utility>
#include <limits>
namespace algos {
namespace algorithm {
// Basic associative operations with neutral elements.
template<typename T> struct Max {
    T neutral() const { return std::numeric_limits<T>::lowest(); }
    T operator()(const T &a, const T &b) const { return std::max(a,b); }
};
template<typename T> struct Min {
    T neutral() const { return std::numeric_limits<T>::max(); }
    T operator()(const T &a, const T &b) const { return std::min(a,b); }
};
// F must be associative and provide neutral().
// pref[i] is the fold of [0,i), so pref has size n+1.
// suff[i] is the fold of [i,n), so suff has size n+1.
// Excluding [l,r) gives func(pref[l],suff[r]): l and r may equal 0 and n.
template<typename T, typename F = Max<T>>
struct ExcludeRange {
    std::vector<T> pref, suff;
    F func{};
    ExcludeRange(const std::vector<T> &a, F func_ = {}) : func(std::move(func_)) {
        pref.assign(isz(a)+1,func.neutral());
        suff.assign(isz(a)+1,func.neutral());
        for (int i = 0; i < isz(a); i++)
            pref[i+1] = func(pref[i],a[i]);
        for (int i = isz(a)-1; i >= 0; i--)
            suff[i] = func(a[i],suff[i+1]);
    }
    T without(int l, int r) const {
        assert(0 <= l && l <= r && r < isz(pref));
        return func(pref[l],suff[r]);
    }
    T operator()(int i) const {
        assert(0 <= i && i+1 < isz(pref));
        return without(i,i+1);
    }
    T operator()(int l, int r) const {
        return without(l,r);
    }
};
// Stores the two largest values. Candidate identifiers must be unique.
template<typename T, typename Cmp = std::less<T>>
struct TopTwo {
    T first{}, second{};
    int firstId{-1};
    bool hasFirst{}, hasSecond{};
    Cmp cmp{};
    void add(const T &x, int id) {
        if (!hasFirst || cmp(first,x))
            second=first, hasSecond=hasFirst, first=x, firstId=id, hasFirst=true;
        else if (!hasSecond || cmp(second,x))
            second=x, hasSecond=true;
    }
    T without(int id) const {
        assert(hasFirst && (firstId != id || hasSecond));
        return (firstId == id ? second : first);
    }
};
// Queue with minimum queries in amortized O(1).
template<typename T, typename F = Min<T>>
struct MinQueue {
    std::vector<std::pair<T,T>> in, out;
    F func{};
    void push(const T &x) { in.push_back({x,(in.empty() ? x : func(in.back().second,x))}); }
    void normalize() {
        while (out.empty() && !in.empty()) {
            T x = in.back().first; in.pop_back();
            out.push_back({x,(out.empty() ? x : func(x,out.back().second))});
        }
    }
    void pop() { normalize(); assert(!out.empty()); out.pop_back(); }
    const T &front() { normalize(); assert(!out.empty()); return out.back().first; }
    T getMin() const {
        assert(!empty());
        return (in.empty() ? out.back().second : (out.empty() ? in.back().second : func(in.back().second,out.back().second)));
    }
    bool empty() const { return in.empty() && out.empty(); }
    int size() const { return isz(in)+isz(out); }
};
// Monotonic stack. By default, elements smaller than a new element are removed.
template<typename T, typename Cmp = std::less<T>>
struct MonoStack {
    std::vector<T> data;
    Cmp cmp{};
    void push(const T &x) {
        while (!data.empty() && cmp(data.back(),x)) data.pop_back();
        data.push_back(x);
    }
    void pop() { assert(!data.empty()); data.pop_back(); }
    const T &top() const { assert(!data.empty()); return data.back(); }
    bool empty() const { return data.empty(); }
    int size() const { return isz(data); }
};
// Returns the first x in [l,r) for which pred(x) is true, or r if it does not exist.
template<typename Int, typename Pred>
Int binarySearch(Int l, Int r, Pred pred) {
    while (l < r) {
        Int m = l+(r-l)/2;
        if (pred(m)) r = m;
        else l = m+1;
    }
    return l;
}
} // namespace algorithm
} // namespace algos
#endif // __ALGORITHM_HPP__