#ifndef __TEMPLATE_HPP__
#define __TEMPLATE_HPP__
#include <random>
#include <chrono>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <deque>
#include <stack>
#include <functional>
#include <bitset>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cassert>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <cstdint>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
const auto ready = [](){
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    return 1;
}();
// Defines:
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = std::vector<int>;
using vl = std::vector<ll>;
using vvi = std::vector<vi>;
using vvl = std::vector<vl>;
using pii = std::pair<int,int>;
using pil = std::pair<int,ll>;
using pli = std::pair<ll,int>;
using pll = std::pair<ll,ll>;
using vpii = std::vector<pii>;
using vvpii = std::vector<vpii>;
using vs = std::vector<std::string>;
// Comparators:
#define GEN_COMPARATORS(A) \
    bool operator >(const A& a, const A& b) { return b < a; }    \
    bool operator<=(const A& a, const A& b) { return !(a > b); } \
    bool operator>=(const A& a, const A& b) { return !(a < b); } \
    bool operator!=(const A& a, const A& b) { return a < b || b < a; } \
    bool operator==(const A& a, const A& b) { return !(a != b); }
namespace std {
#if __cplusplus < 201703L
    // Containers:
    template <typename T> constexpr auto size(const T& t) -> decltype(t.size()) { return t.size(); }
    // 1D arrays:
    template<typename T, int N> auto size(const T (&)[N]) { return N; }
#endif
    // 2D arrays:
    template<typename T, int N, int M> auto size(const T (&)[N][M]) { return N * M; }
    template<typename T, int N, int M> auto begin(T (&a)[N][M]) { return &a[0][0]; }
    template<typename T, int N, int M> auto end(T (&a)[N][M]) { return &a[0][0] + N * M; }
    // 3D arrays:
    template<typename T, int N, int M, int K> auto size(const T (&)[N][M][K]) { return N * M * K; }
    template<typename T, int N, int M, int K> auto begin(T (&a)[N][M][K]) { return &a[0][0][0]; }
    template<typename T, int N, int M, int K> auto end(T (&a)[N][M][K]) { return &a[0][0][0] + N * M * K; }
    // Algorithms:
    template<typename C> void reuniq(C& c) { c.erase(unique(all(c)), end(c)); }
    template<typename C, typename X> int lowpos(const C& c, X x) {
        return int(lower_bound(all(c), x) - begin(c));
    }
    template<typename C, typename X> int uppos(const C& c, X x) {
        return int(upper_bound(all(c), x) - begin(c));
    }
    template<typename X, typename Y> X& remin(X& x, const Y& y) { return x = (y < x) ? y : x; }
    template<typename X, typename Y> X& remax(X& x, const Y& y) { return x = (x < y) ? y : x; }
}
// Input:
template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto &it : vec) is >> it;
    return is;
}

// ---- ---- ---- ---- ---- ---- OPERATORS FOR STL CONTAINERS ---- ---- ---- ---- ---- ----
#define INSERT(cont, to_front, to_back)  \
template<typename X, typename... T> cont<X,T...>& operator<<(cont<X,T...>& c, const X& x) { return to_back, c; } \
template<typename X, typename... T> cont<X,T...>& operator>>(const X& x, cont<X,T...>& c) { return to_front, c; }
 
INSERT(std::vector, (c.insert(c.begin(), x)), (c.push_back(x)))
INSERT(std::queue, (c.push(x)), (c.push(x)))
INSERT(std::stack, (c.push(x)), (c.push(x)))
INSERT(std::priority_queue, (c.push(x)), (c.push(x)))
INSERT(std::deque, (c.push_front(x)), (c.push_back(x)))
INSERT(std::list, (c.push_front(x)), (c.push_back(x)))
INSERT(std::set, (c.insert(x)), (c.insert(x)))
INSERT(std::unordered_set, (c.insert(x)), (c.insert(x)))
INSERT(std::multiset, (c.insert(x)), (c.insert(x)))
#undef INSERT
 
#define REMOVE(cont, from_front, from_back) \
template<typename X, typename... T> X operator--(cont<X,T...>& c,int) { X x; from_back; return x; } \
template<typename X, typename... T> X operator--(cont<X,T...>& c) { X x; from_front; return x; }
 
REMOVE(std::vector,(x=c.front(),c.erase(c.begin())),(x=c.back(),c.pop_back()))
REMOVE(std::deque,(x=c.front(),c.pop_front()),(x=c.back(),c.pop_back()))
REMOVE(std::queue,(x=c.front(),c.pop()),(x=c.front(),c.pop()))
REMOVE(std::stack,(x=c.top(),c.pop()),(x=c.top(),c.pop()))
REMOVE(std::priority_queue,(x=c.top(),c.pop()),(x=c.top(),c.pop()))
REMOVE(std::list,(x=c.front(),c.pop_front()),(x=c.back(),c.pop_back()))
REMOVE(std::set,(x=*c.begin(),c.erase(c.begin())),(x=*std::prev(c.end()),c.erase(std::prev(c.end()))))
REMOVE(std::multiset,(x=*c.begin(),c.erase(c.begin())),(x=*std::prev(c.end()),c.erase(std::prev(c.end()))))
REMOVE(std::unordered_set,(x=*c.begin(),c.erase(c.begin())),(x=*std::prev(c.end()),c.erase(std::prev(c.end()))))
REMOVE(std::map,(x=*c.begin(),c.erase(c.begin())),(x=*std::prev(c.end()),c.erase(std::prev(c.end()))))
REMOVE(std::unordered_map,(x=*c.begin(),c.erase(c.begin())),(x=*std::prev(c.end()),c.erase(std::prev(c.end()))))
#undef REMOVE
 
#define EXTRACT(cont) \
template<typename X, typename... T> cont<X,T...>& operator>>(cont<X,T...>& c, X& x) { return x=c--,c; } \
template<typename X, typename... T> cont<X,T...>& operator<<(X& x, cont<X,T...>& c) { return x=--c,c; }
 
EXTRACT(std::vector) EXTRACT(std::list) EXTRACT(std::deque) EXTRACT(std::queue)
EXTRACT(std::stack) EXTRACT(std::priority_queue) EXTRACT(std::set) 
EXTRACT(std::map) EXTRACT(std::multiset) EXTRACT(std::unordered_set)
#undef EXTRACT
 
#define MOVE(cont)                                                    \
template<typename X, typename... T>                                   \
cont<X,T...>& operator>>(cont<X,T...>& l, cont<X,T...>& r)            \
{{ while (isz(l)) l-- >> r;} return r; }                              \
template<typename X, typename... T>                                   \
cont<X,T...>& operator<<(cont<X,T...>& l, cont<X,T...>& r)            \
{{ while (isz(r)) l << --r;} return l; }                              
MOVE(std::list) MOVE(std::deque) MOVE(std::queue) MOVE(std::set) MOVE(std::multiset)
MOVE(std::stack) MOVE(std::priority_queue) MOVE(std::unordered_set)
#undef MOVE
 
template<typename X, typename... T>
std::vector<X,T...>& operator>>(std::vector<X,T...>& l, std::vector<X,T...>& r)
{ return r.insert(r.begin(),all(l)),l.clear(), r; }
 
template<typename X, typename... T>
std::vector<X,T...>& operator<<(std::vector<X,T...>& l, std::vector<X,T...>& r)
{ return l.insert(l.end(),all(r)),r.clear(), l; }

// Auto-revert:
template<typename F1, typename F2>
struct AutoRevert {
    F1 f1;
    F2 f2;
    AutoRevert(const F1 &func1, const F2 &func2)
        : f1(func1)
        , f2(func2)
    {
        f1();
    }
    ~AutoRevert()
    {
        f2();
    }
};

// Operations with bits:
template<typename T>
void setbit(T &mask, int bit, bool x) {
    mask &= ~(T(1) << bit);
    mask |= (T(x) << bit);
}

template<typename T>
bool getbit(T &mask, int bit) {
    return (mask >> bit & 1);
}

template<typename T>
void flipbit(T &mask, int bit) {
    mask ^= (T(1) << bit);
}

// -----------------------------------------------------------------------------
#endif // __TEMPLATE_HPP__
