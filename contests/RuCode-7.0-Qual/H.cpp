#pragma GCC optimize("Ofast")
#ifndef __TEMPLATE_HPP__
#define __TEMPLATE_HPP__
#include <climits>
#include <unordered_map>
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
// marco for random variable name:
#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b
#define SomeVar CONCAT(var, CONCAT(_, CONCAT(__LINE__, CONCAT(_, __COUNTER__))))
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
using vpll = std::vector<pll>;
using vvpll = std::vector<vpll>;
using vs = std::vector<std::string>;
using tiii = std::tuple<int,int,int>;
using tiil = std::tuple<int,int,ll>;
using vtiii = std::vector<tiii>;
using vtiil = std::vector<tiil>;
// Comparators:
#define GEN_COMPARATORS(CLASS) \
    inline bool operator >(const CLASS& a, const CLASS& b) { return b < a; }    \
    inline bool operator<=(const CLASS& a, const CLASS& b) { return !(a > b); } \
    inline bool operator>=(const CLASS& a, const CLASS& b) { return !(a < b); } \
    inline bool operator!=(const CLASS& a, const CLASS& b) { return a < b || b < a; } \
    inline bool operator==(const CLASS& a, const CLASS& b) { return !(a != b); }
#define GEN_COMPARATORS_MEMBERS(CLASS) \
    bool operator >(const CLASS &other) const { return other < (*this); }    \
    bool operator<=(const CLASS &other) const { return !((*this) > other); } \
    bool operator>=(const CLASS &other) const { return !((*this) < other); } \
    bool operator!=(const CLASS &other) const { return (*this) < other || other < (*this); } \
    bool operator==(const CLASS &other) const { return !((*this) != other); }
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
}
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
// Input:
template<typename T> std::istream& operator>>(std::istream& is, std::vector<T>& vec) {
    for (auto &it : vec) is >> it;
    return is;
}

// ---- ---- ---- ---- ---- ---- OPERATORS FOR STL CONTAINERS ---- ---- ---- ---- ---- ----
#define INSERT(cont, to_front, to_back)  \
template<typename X, typename Y, typename... T> cont<X,T...>& operator<<(cont<X,T...>& c, const Y& x) { return to_back, c; } \
template<typename X, typename Y, typename... T> cont<X,T...>& operator>>(const Y& x, cont<X,T...>& c) { return to_front, c; }
 
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
    F1 f1; F2 f2;
    AutoRevert(const F1 &f1_, const F2 &f2_) : f1(f1_), f2(f2_) { f1(); }
    ~AutoRevert() { f2(); }
};

template<typename T>
struct AutoRecover {
    T &ref, val;
    AutoRecover(T &x) : ref(x), val(x) { }
    ~AutoRecover() { ref = val; }
};

// Operations with bits:
template<typename T> void setbit(T &mask, int bit, bool x) { (mask &= ~(T(1) << bit)) |= (T(x) << bit); }
template<typename T> bool getbit(T &mask, int bit) { return (mask >> bit & 1); }
template<typename T> void flipbit(T &mask, int bit) { mask ^= (T(1) << bit); }

// Convert vector to tuple: auto [x,y,z] = to_tuple<3>(vec);
template <typename F, size_t... Is>
auto gen_tuple_impl(F func, std::index_sequence<Is...> ) { return std::make_tuple(func(Is)...); }
template <size_t N, typename F>
auto gen_tuple(F func) { return gen_tuple_impl(func, std::make_index_sequence<N>{} ); }
template<size_t N, typename ... A>
auto to_tuple(const std::vector<A...> &v) { return gen_tuple<N>([&v](size_t i){return v[i];});}
// pack / unpack vector: unpack(vec, x, y, z)
void unpack(const auto &vec, auto &...b) { int i = -1; ((b = vec[++i]),...); }
void pack(auto &vec, const auto &...b) { int i = -1; ((vec[++i] = b),...); }
// -----------------------------------------------------------------------------
#endif // __TEMPLATE_HPP__
#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__
// ---- ---- ---- ---- ---- ---- DEBUG LIBRARY ---- ---- ---- ---- ---- ----
#define watch(...) debug && std::cerr << "{" << #__VA_ARGS__ << "} = " \
    << std::make_tuple(__VA_ARGS__) << std::endl

template<typename... X>
std::ostream& operator<<(std::ostream& os, const std::pair<X...>& p);

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_each_const(const std::tuple<Tp...> &, FuncT) { }

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_each_const(const std::tuple<Tp...>& t, FuncT f)
{ f(std::get<I>(t)),for_each_const<I + 1, FuncT, Tp...>(t, f); }


template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_each(std::tuple<Tp...> &, FuncT) { }

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_each(std::tuple<Tp...>& t, FuncT f)
{ f(std::get<I>(t)); for_each<I + 1, FuncT, Tp...>(t, f); }

struct Printer {
    std::ostream& os; bool was{0};
    Printer(std::ostream& os_) : os(os_) { }
    template<typename X> void operator()(X x);
    
};

template<typename Iterator>
std::ostream& print(std::ostream& os, Iterator begin, Iterator end)
{ return os << "{", std::for_each(begin,end,Printer(os)), os << "}"; }

#define OUTPUT(container) template<typename X, typename... T>           \
std::ostream& operator<<(std::ostream& os, const container<X,T...>& c)  \
{ return print(os, all(c)); }
OUTPUT(std::vector) OUTPUT(std::list) OUTPUT(std::deque)
OUTPUT(std::set) OUTPUT(std::unordered_set)
OUTPUT(std::multiset) OUTPUT(std::unordered_multiset)
OUTPUT(std::map) OUTPUT(std::multimap) OUTPUT(std::unordered_map)
#undef OUTPUT
    
#define OUTPUT2(container, get, pop) template<typename X, typename... T> \
std::ostream& operator<<(std::ostream& os, container<X,T...> c) {       \
    std::vector<X> v(c.size());                                         \
    for (unsigned i = 0; i != v.size(); v[i++] = c.get(),c.pop());      \
    return os << v; }                                                   
OUTPUT2(std::queue,front,pop)
OUTPUT2(std::stack,top,pop)
OUTPUT2(std::priority_queue,top,pop)
#undef OUTPUT2

template<typename... X>
std::ostream& operator<<(std::ostream& os, const std::tuple<X...>& t)
{ return os << "{", for_each_const(t, Printer(os)), os << "}"; }

template<typename X>
void Printer::operator()(X x)
{ os << (was?", ":(was=1,"")) << x; }

template<typename... X>
std::ostream& operator<<(std::ostream& os, const std::pair<X...>& p) 
{ return os << std::make_tuple(std::get<0>(p), std::get<1>(p)); }

int debug = 0;
#endif // __DEBUG_HPP__
template<typename A, typename B>
std::pair<A,B> operator-(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return std::pair<A,B>(a.first - b.first, a.second - b.second);
}
template<typename A, typename B>
std::pair<A,B> operator+(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return std::pair<A,B>(a.first + b.first, a.second + b.second);
}
template<typename T, typename A, typename B>
T cross(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return T(a.first) * b.second - T(a.second) * b.first;
}

template<typename T, typename A, typename B>
T doubleSquare(const std::pair<A,B> &a, const std::pair<A,B> &b, const std::pair<A,B> &c) {
    T res = cross<T>(a-b, c-b);
    if (res < 0)
        res = -res;
    return res;
}
template<typename T, typename A, typename B>
T dist2(const std::pair<A,B> &a) {
    return T(a.first)*a.first + T(a.second)*a.second;
}
template<typename T, typename A, typename B>
T dist2(const std::pair<A,B> &a, const std::pair<A,B> &b) {
    return dist2<T>(a-b);
}

void assert1(bool q) { while (!q); }
void assertIgnore(bool q) { while (!q); }

using Triangle = std::tuple<pii,pii,pii>;
bool inside(Triangle tr, pii p) {
    auto [A, B, C] = tr;
    auto S = doubleSquare<ll>(A,B,C);
    auto S1 = doubleSquare<ll>(p,B,C);
    auto S2 = doubleSquare<ll>(A,p,C);
    auto S3 = doubleSquare<ll>(A,B,p);
    return S == S1 + S2 + S3;
}
template<bool reversed = false>
std::pair<std::vector<Triangle>, bool> splitIntoTriangles(std::vector<pii> points) {
    //bool debug = 1;
    if (reversed)
        std::reverse(all(points));
    // дублируем последнюю точку
    points.push_back(points[0]);
    ll square = 0;
    for (int i = 0; i + 1 < isz(points); i++)
        square += cross<ll>(points[i], points[i+1]);
    square = std::abs(square);
    // начинаем строить выпуклую оболочку
    std::vector<pii> hull = {points[0], points[1]};
    std::vector<Triangle> triangles;
    for (int i = 2; i < isz(points); i++) {
        // добавляем текущую точку
        hull << points[i];
        // пока три последние точки образуют угол против часовой, добавляем треугольники
        while (isz(hull) >= 3) {
            // три последние точки
            auto &last = hull[isz(hull)-1];
            auto &mid = hull[isz(hull)-2];
            auto &first = hull[isz(hull)-3];
            // векторное произведение
            auto res = cross<ll>(first-mid, last-mid);
            if (res > 0)
                break;
            if (res == 0) {
                std::swap(last,mid);
                hull.pop_back();
                continue;
            }
            assert(res < 0);
            bool ok = true;
            for (int j = i+1; j + 1 < isz(points); j++) {
                ok &= !inside(Triangle{last,mid,first}, points[j]);
            }
            if (!ok)
                break;
            // выкидываем с добавлением треугольника
            // надо проверить что ни одна точка далее не принадлежит прямой
            // нет ни одной точки, которая принадлежит треугольнику
            if (!reversed) triangles.emplace_back(last,mid,first);
            else triangles.emplace_back(first,mid,last);
            watch("add", triangles.back());
            std::swap(last,mid);
            watch("remove", hull.back());
            hull.pop_back();
        }
        watch("hull after all removing", hull);
    }
    watch(hull);
    if (isz(hull) < 3) {
        for (auto &[A,B,C] : triangles) {
            square -= doubleSquare<ll>(A,B,C);
        }
        assert(square == 0);
    }
    return std::make_pair(std::move(triangles), isz(hull) < 3);
}

template<bool reversed = false>
std::pair<std::vector<Triangle>, bool> splitIntoTrianglesSlow(std::vector<pii> points) {
    //bool debug = 1;
    /*if (reversed)
        std::reverse(all(points));*/
    // дублируем последнюю точку
    points.push_back(points[0]);
    auto getSquare = [&](int i, int j) {
        return cross<ll>(points[i], points[j]);
    };
    ll square = 0;
    for (int i = 0; i + 1 < isz(points); i++)
        square += getSquare(i,i+1);
    //square);
    watch(square);
    std::vector<Triangle> triangles;
    while (isz(points) > 3) {
        watch(points);
        int was = 0;
        for (int i = 1; i + 1 < isz(points); i++) {
            // три точки берём
            auto A = points[i-1], B = points[i], C = points[i+1];
            // удалим якобы точку B
            ll tmp = square - getSquare(i-1,i) - getSquare(i,i+1) + getSquare(i-1, i+1);
            ll add = doubleSquare<ll>(A,B,C);
            watch(square, tmp, add);
            if (std::abs(tmp) + add == std::abs(square)) {
                // можем удалить эту точку
                triangles.emplace_back(A,B,C);
                points.erase(points.begin()+i);
                square = tmp;
                i--;
                was++;
            }
        }
        assert1(was > 0);
    }
    return std::make_pair(std::move(triangles), true);
}

pii pickPointOutside(pii A, pii B) {
    pii C1(A.first, B.second);
    pii C2(B.first, A.second);
    pii res = cross<ll>(A-C1, B-C1) < 0 ? C1 : C2;
    watch("pickPointOutside", A, B, res);
    return res;
}

std::pair<ld,ld> rectangle(int xmin, int ymin, int xmax, int ymax) {
    ll dx = xmax - xmin, dy = ymax - ymin;
    ld fi = (dx + 1) / 2 * dy;
    ld se = dx / 2 * dy;
    if (xmin % 2 != 0) std::swap(fi,se);
    watch("rectangle", xmin, ymin, xmax, ymax, fi, se);
    return {fi, se};
}

ll sum(ll n) {
// n^2 - (n-1)^2 + (n-2)^2 - (n-3)^2 + (n-4)^2 + ...
// wolfram: n*(n+1)/2
// check: 4^2-3^2+2^1-1=16-9+4-1=10
// check: 4 * 5 / 2 = 10
    return n * (n+1) / 2;
}

std::pair<ld, ld> solveBaseCaseLD(ll x, ll y) {
// triangle
// *
// **
// ***
// ****
    watch("solveBaseCaseLD",x,y);
    ld c = y / (2.0L * x);
    std::pair<ld, ld> res{c * sum(x), c * sum(x-1)};
    watch(res);
    return res;
}

std::pair<ld, ld> solveBaseCaseRU(ll x, ll y) {
// triangle
// ****
//  ***
//   **
//    *
    auto res = solveBaseCaseLD(x, y);
    if (x % 2 == 0)
        std::swap(res.first, res.second); // проверено
    return res;
}

std::pair<ld, ld> solveBaseCaseRU(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// ****
//  ***
//   **
//    *
    assert1(xmin <= xmax);
    assert1(ymin <= ymax);
    auto res = solveBaseCaseRU(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseLD(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// *
// **
// ***
// ****
    assert1(xmin <= xmax);
    assert1(ymin <= ymax);
    auto res = solveBaseCaseLD(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseRD(ll x, ll y) {
// triangle
//    *
//   **
//  ***
// ****
    watch("solveBaseCaseRD",x,y);
    auto res = solveBaseCaseLD(x, y);
    if (x % 2 == 0) // проверено
        std::swap(res.first, res.second);
    watch(res);
    return res;
}

std::pair<ld, ld> solveBaseCaseLU(ll x, ll y) {
// triangle
// ****
// ***
// **
// *   
    auto res = solveBaseCaseLD(x, y);
    return res;
}

std::pair<ld, ld> solveBaseCaseLU(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
// ****
// ***
// **
// *
    auto res = solveBaseCaseLU(xmax-xmin, ymax-ymin);
    if (xmin % 2 != 0) std::swap(res.first, res.second);
    return res;
}

std::pair<ld, ld> solveBaseCaseRD(ll xmin, ll ymin, ll xmax, ll ymax) {
// triangle
//    *
//   **
//  ***
// ****
    watch("solveBaseCaseRD", xmin, ymin, xmax, ymax);
    assert1(xmin <= xmax);
    assert1(ymin <= ymax);
    auto res = solveBaseCaseRD(xmax-xmin,ymax-ymin);
    watch("before swap", res);
    if (xmin % 2 != 0) {
        std::swap(res.first, res.second);
    }
    watch("after swap", res);
    return res;
}

std::pair<ld, ld> triangle(pii A, pii B, pii C) {
// B - corner
// AC - diagonal
    if (doubleSquare<ll>(A,B,C) == 0)
        return {0, 0};
    if (A.first > C.first)
        std::swap(A, C);
    assert1(A.first < C.first);
    ll xmin = std::min({A.first, B.first, C.first});
    ll xmax = std::max({A.first, B.first, C.first});
    ll ymin = std::min({A.second, B.second, C.second});
    ll ymax = std::max({A.second, B.second, C.second});
    pii LD(xmin,ymin), LU(xmin,ymax), RD(xmax,ymin), RU(xmax,ymax);
    watch(LD,B);
    watch(LU,B);
    watch(RD,B);
    watch(RU,B);
    std::pair<ld,ld> res;
    if (A.second > C.second) {
        if (B == LD) {
            watch("call solveBaseCaseLD");
            res = solveBaseCaseLD(xmin,ymin,xmax,ymax);
        }
        else {
            assert1(B == RU);
            watch("call solveBaseCaseRU");
            res = solveBaseCaseRU(xmin,ymin,xmax,ymax);
        }
    } else {
        assert1(A.second < C.second);
        if (B == RD) {
            watch("call solveBaseCaseRD");
            res = solveBaseCaseRD(xmin,ymin,xmax,ymax);
        }
        else {
            assert1(B == LU);
            watch("call solveBaseCaseLU");
            res = solveBaseCaseLU(xmin,ymin,xmax,ymax);
        }
    }
    watch("triangle", A,B,C,res);
    return res;
}

bool inter(pii A, pii B, int x, ld &y) {
    if (A.first > B.first) std::swap(A, B);
    if (x < A.first || x > B.first)
        return false;
    if (x == A.first) {
        y = A.second;
        return true;
    }
    if (x == B.first) {
        y = B.second;
        return true;
    }
    pii v = B - A;
    // A + t * (B - A) == {x, y}
    // A.first + t * v.first == x
    ld t = (x - A.first) / ld(v.first);
    y = A.second + t * v.second;
    return true;
}

ld solveVerticalCase(pii A, pii B, pii C, int x) {
    //bool debug = 1;
    std::vector<ld> y1, y2;
    ld y;
    if (inter(A,B,x,y)) y1 << y;
    if (inter(B,C,x,y)) y1 << y;
    if (inter(A,C,x,y)) y1 << y;
    if (inter(A,B,x+1,y)) y2 << y;
    if (inter(B,C,x+1,y)) y2 << y;
    if (inter(A,C,x+1,y)) y2 << y;
    std::sort(all(y1));
    std::sort(all(y2));
    watch("solveVerticalCase",A,B,C,x);
    ld res = (y1.back() - y1.front() + y2.back() - y2.front()) / 2;
    watch(y1,y2);
    watch(res);
    return res;
}


const bool check = [](){
    {   // test1:
        auto resToCheck = solveBaseCaseLD(4,4);
        auto trueRes = std::pair<ld,ld>(5, 3);
        assertIgnore(resToCheck == trueRes);
    }
    {   // test1:
        auto resToCheck = solveBaseCaseRD(4,4);
        auto trueRes = std::pair<ld,ld>(3, 5);
        assertIgnore(resToCheck == trueRes);
    }
    {   // test1:
        auto resToCheck = solveBaseCaseLU(4,4);
        auto trueRes = std::pair<ld,ld>(5, 3);
        assertIgnore(resToCheck == trueRes);
    }
    {   // test1:
        auto resToCheck = solveBaseCaseRU(4,4);
        auto trueRes = std::pair<ld,ld>(3, 5);
        assertIgnore(resToCheck == trueRes);
    }
    {   // test2:
        pii A{1, 1}, B{3, 1}, C{3, 3};
        auto trueRes1 = std::pair<ld,ld>(1.5, 0.5);
        auto resToCheck1 = solveBaseCaseRD(1,1,3,3);
        assertIgnore(resToCheck1 == trueRes1);
    }
    {   // test3:
        pii A{1, 1}, B{3, 1}, C{3, 3};
        auto trueRes1 = std::pair<ld,ld>(1.5, 0.5);
        auto resToCheck1 = solveBaseCaseRD(1,1,3,3);
        assertIgnore(resToCheck1 == trueRes1);
    }
    {   // test3:
        //debug = 1;
        pii A{1, 1}, B{2, 1}, C{2, 3};
        auto trueRes1 = std::pair<ld,ld>(0, 1);
        auto resToCheck1 = triangle(A,B,C);
        assertIgnore(resToCheck1 == trueRes1);
        //debug = 0;
    }
    {
        
    }
    //std::cout << "finish testing" << std::endl;
    return 0;
}();

ll orientedSquare(std::vector<pii> points) {
    ll res{};
    for (int i = 0; i < isz(points); i++) {
        auto A = points[i];
        auto B = points[(i+1)%isz(points)];
        res += cross<ll>(A,B);
    }
    return res;
}

void readAndScale(int &n, vpii &points) {
    std::cin >> n;
    points.resize(n);
    int minX = INT_MAX;
    int minY = INT_MAX;
    for (auto &[x,y] : points) {
        std::cin >> x >> y;
        remin(minX, x);
        remin(minY, y);
    }
    if (minX % 2 != 0) minX--;
    if (minY % 2 != 0) minY--;
    for (auto &[x,y] : points) {
        x -= minX, y -= minY;
        std::swap(x,y);
    }
}

int sign(auto x) { return x < 0 ? -1 : (x > 0 ? +1 : 0); }

const int LEFT = -1;
const int RIGHT = +1;
int rotation(pii first, pii mid, pii last) {
// > 0 --> right
// < 0 --> left
    return sign(cross<ll>(first-mid,last-mid));
}

std::pair<ld,ld> twoRectangles(pii A, pii B, pii C) {
    if (A.first > B.first) std::swap(A, B);
    if (A.first > C.first) std::swap(A, C);
    if (B.first > C.first) std::swap(B, C);
    assert(A.first <= B.first && B.first <= C.first);
    auto [ymin, ymax] = std::minmax({A.second,C.second});
    if (B.second >= ymax || B.second <= ymin || B.first == A.first || B.first == C.first) {
        remin(ymin, B.second);
        remax(ymax, B.second);
        return rectangle(A.first, ymin, C.first, ymax);
    }
    std::pair<ld,ld> rect = rectangle(A.first, ymin, C.first, ymax);
    // выше или ниже диагонали?
    if (rotation(A,C,B) <= 0) { // выше
        // A ниже чем C?
        if (A.second <= C.second)
            rect = rect - rectangle(A.first, B.second, B.first, ymax);
        else
            rect = rect - rectangle(B.first, B.second, C.first, ymax);
    } else { // ниже
        // A ниже чем C?
        if (A.second <= C.second)
            rect = rect - rectangle(B.first, ymin, C.first, B.second);
        else
            rect = rect - rectangle(A.first, ymin, B.first, B.second);
    }
    return rect;
}

std::pair<ld,ld> calcTriangle(pii A, pii B, pii C) {
    if (cross<ll>(A-B,C-B) > 0)
        std::swap(A, C);
    //int xmin = std::min<int>({A.first, B.first, C.first});
    //int xmax = std::max<int>({A.first, B.first, C.first});
    //int ymin = std::min<int>({A.second, B.second, C.second});
    //int ymax = std::max<int>({A.second, B.second, C.second});
    auto temp = twoRectangles(A,B,C);
    auto P1 = pickPointOutside(A,B);
    auto P2 = pickPointOutside(B,C);
    auto P3 = pickPointOutside(C,A);
    if (!(A.first == B.first || A.second == B.second))
        temp = temp - triangle(A,P1,B);
    if (!(B.first == C.first || B.second == C.second))
        temp = temp - triangle(B,P2,C);
    if (!(C.first == A.first || C.second == A.second))
        temp = temp - triangle(C,P3,A);
    return temp;
}

bool isPointOnSegment(pii P, pii A, pii B) {
    auto [x, y] = P;
    auto [xmin,xmax] = std::minmax({A.first, B.first});
    auto [ymin,ymax] = std::minmax({A.second, B.second});
    if (x < xmin || x > xmax || y < ymin || y > ymax)
        return false;
    return cross<ll>(A-P,B-P) == 0;
}

const int NONE = 0, POINT = 1, INSIDE = 2;
int intersects(pii A, pii B, pii C, pii D) {
    if (A == C || A == D || B == C || B == D)
        return POINT;
    if (isPointOnSegment(A,C,D) || isPointOnSegment(B,C,D) ||
        isPointOnSegment(C,A,B) || isPointOnSegment(D,A,B))
        return POINT;
    auto [xmin1,xmax1] = std::minmax({A.first, B.first});
    auto [ymin1,ymax1] = std::minmax({A.second, B.second});
    auto [xmin2,xmax2] = std::minmax({C.first, D.first});
    auto [ymin2,ymax2] = std::minmax({C.second, D.second});
    if (xmax1 < xmin2 || xmin1 > xmax2)
        return NONE;
    if (ymax1 < ymin2 || ymin1 > ymax2)
        return NONE;
    auto rot1 = rotation(A,B,C);
    auto rot2 = rotation(A,B,D);
    if (sign(rot1) * sign(rot2) < 0)
        return INSIDE;
    return NONE;
}

ld calcTriangleSlow(pii A, pii B, pii C) {
    auto [xMin, xMax] = std::minmax({A.first, B.first, C.first});
    ld ans{};
    int x = xMin;
    if (x % 2 != 0)
        x++;
    while (x+1 <= xMax) {
        assert(x % 2 == 0);
        ans += solveVerticalCase(A,B,C,x);
        x += 2;
    }
    return ans;
}
bool isAlmostEqual(ld x, ld y) {
    const ld EPS = 1e-10;
    return std::abs(x-y) / (1 + std::abs(x)) < EPS;
}
void stress(int xs, int xf) {
    //const int X = 10;
    for (int x1 = xs; x1 <= xf; x1++)
        for (int y1 = xs; y1 <= xf; y1++)
            for (int x2 = xs; x2 <= xf; x2++)
                for (int y2 = xs; y2 <= xf; y2++)
                    for (int x3 = xs; x3 <= xf; x3++)
                        for (int y3 = xs; y3 <= xf; y3++) {
                            pii A(x1,y1), B(x2,y2), C(x3,y3);
                            ll s = doubleSquare<ll>(A,B,C);
                            if (s == 0) continue;
                            ld fast = calcTriangle(A,B,C).first;
                            ld slow = calcTriangleSlow(A,B,C);
                            if (!isAlmostEqual(fast,slow)) {
                                debug = 1;
                                fast = calcTriangle(A,B,C).first;
                                watch(A,B,C);
                                watch(fast);
                                watch(slow);
                                std::exit(0);
                            }
                        }
}

bool liesBelow(pii P1, pii P2) {
    auto [x1,y1] = P1;
    auto [x2,y2] = P2;
    return (y1 < y2 || (y1 == y2 && x1 > x2));
}

bool liesAbove(pii P1, pii P2) {
    auto [x1,y1] = P1;
    auto [x2,y2] = P2;
    return (y1 > y2 || (y1 == y2 && x1 < x2));
}

bool angleLessThanPi(pii L, pii M, pii R) {
    return rotation(L,M,R) == LEFT;
}

bool angleGreaterThanPi(pii L, pii M, pii R) {
    return rotation(L,M,R) == RIGHT;
}

const int START = 0, SPLIT = 1, END = 2, MERGE = 3, REGULAR = 4;

auto getPrev(const auto &vec, int i) {
    i--;
    if (i < 0) i = isz(vec)-1;
    //i = (i-1+isz(vec))%isz(vec);
    //assert(0 <= i && i < isz(vec));
    return vec[i];
}

auto getNext(const auto &vec, int i) {
    i++;
    if (i == isz(vec))
        i = 0;
    //i = (i+1+isz(vec))%isz(vec);
    //assert(0 <= i && i < isz(vec));
    return vec[i];
}

auto getTypeOfVertex(const auto &P, int i) {
    pii L = getPrev(P, i), M = P[i], R = getNext(P, i);
    if (liesBelow(L,M) && liesBelow(R,M) && angleLessThanPi(L,M,R))
        return START;
    if (liesBelow(L,M) && liesBelow(R,M) && angleGreaterThanPi(L,M,R))
        return SPLIT;
    if (liesAbove(L,M) && liesAbove(R,M) && angleLessThanPi(L,M,R))
        return END;
    if (liesAbove(L,M) && liesAbove(R,M) && angleGreaterThanPi(L,M,R))
        return MERGE;
    return REGULAR;
}

std::string type2str(int t) {
    switch(t) {
        case START: return "start";
        case SPLIT: return "split";
        case END: return "end";
        case MERGE: return "merge";
        case REGULAR: return "regular";
        default: return "none";
    };
}
template<bool debug = 0>
bool isMonotone(vpii P) {
    if (isz(P) <= 3)
        return true;
    watch("begin of isMonotone");
    // начинаем с максимальной
    //bool debug = 1;
    watch(P);
    int imax = -1, ymax = INT_MIN;
    for (int i = 0; i < isz(P); i++) {
        watch(i, isz(P));
        if (P[i].second >= ymax) {
            imax = i;
            ymax = P[i].second;
        }
    }
    int len = 0;
    int i = imax;
    watch(imax, ymax);
    while (len <= isz(P) && P[i].second >= getNext(P, i).second) {
        len++;
        i++;
        i %= isz(P);
        watch(i, isz(P));
    }
    while (len <= isz(P) && P[i].second <= getNext(P, i).second) {
        len++;
        i++;
        i %= isz(P);
        watch(i, isz(P));
    }
    watch("end of isMonotone");
    return len >= isz(P);
}
void print(const char *filename, vvpii PP, vpii originalPoints, vpii D) {
    std::ofstream fout(filename);
    fout << isz(PP) << "\n";
    for (const auto &P : PP) {
        fout << isz(P) << "\n";
        for (auto &[x, y] : P)
            fout << x << ' ' << y << "\n";
    }
    fout << isz(D) << "\n";
    for (auto &[u, v] : D) {
        auto [xu, yu] = originalPoints[u];
        auto [xv, yv] = originalPoints[v];
        fout << xu << ' ' << yu << ' ' << xv << ' ' << yv << "\n";
    }
}
/*
struct Frac {
    ll p, q;
    Frac (ll p_ = 0, ll q_ = 1) : p(p_), q(q_) {
        ll g = std::gcd(std::abs(p), std::abs(q));
        p /= g;
        q /= g;
        if (q < 0) p *= -1, q *= -1;
        if (p == 0) q = 1;
    }
    Frac (int p_ , int q_ = 1) : Frac(ll(p_), ll(q_)) { }
    Frac operator+(const Frac &other) const {
        auto [p1,q1] = other;
        return Frac(p*q1+p1*q,q1*q);
    }
    Frac operator-(const Frac &other) const {
        auto [p1,q1] = other;
        return Frac(p*q1-p1*q,q1*q);
    }
    Frac operator*(const Frac &other) const {
        auto [p1,q1] = other;
        return Frac(p*p1,q*q1);
    }
    Frac operator/(const Frac &other) const {
        auto [p1,q1] = other;
        return Frac(p*q1,q*p1);
    }
    Frac operator-() const {
        return Frac(-p, q);
    }
    Frac& operator*=(const Frac &other) { return *this = *this * other; }
    Frac& operator/=(const Frac &other) { return *this = *this / other; }
    Frac& operator+=(const Frac &other) { return *this = *this + other; }
    Frac& operator-=(const Frac &other) { return *this = *this - other; }
};

Frac operator+(const auto& lhs, const Frac &fr) { return Frac(lhs) + fr; }
Frac operator-(const auto& lhs, const Frac &fr) { return Frac(lhs) - fr; }
Frac operator*(const auto& lhs, const Frac &fr) { return Frac(lhs) * fr; }
Frac operator/(const auto& lhs, const Frac &fr) { return Frac(lhs) / fr; }

bool operator<(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p < 0;
}
bool operator<=(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p <= 0;
}
bool operator>(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p > 0;
}
bool operator>=(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p >= 0;
}
bool operator==(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p == 0;
}
bool operator!=(const Frac &a, const Frac &b) {
    return (__int128)a.p * b.q - (__int128)a.q * b.p != 0;
}

std::ostream &operator<<(std::ostream &os, const Frac &fr) {
    return os << fr.p << "/" << fr.q;
}

using Fraction = Frac;*/

int currY, currX;

using Frac = ld;




template<bool debug = 0>
vpii findDiagonals(vpii P) {
    //std::priority_queue<tiii> pq;
    vtiii pq;
    for (int i = 0; i < isz(P); i++) {
        auto [x,y] = P[i];
        pq << tiii(y,-x,i);
    }
    std::sort(all(pq), std::greater<>());
    //const bool debug = 0;
    for (int i = 0; i < isz(P); i++) {
        watch(P[i], i+1, type2str(getTypeOfVertex(P, i)));
    }
    //std::vector<bool> calculated(isz(P), false);
    //std::vector<ld> cachedResult(isz(P));
    //std::vector<int> queueToCalculate;
    auto setCurrY = [&](int newCurrY) {
        //if (newCurrY == currY)
        //    return;
        //for (auto it : queueToCalculate)
        //    calculated[it] = false;
        //queueToCalculate.clear();
        currY = newCurrY;
    };
    auto setCurrX = [&](int newCurrX) {
        /*if (newCurrX == currX)
            return;*/
        currX = newCurrX;
    };
    //vvi helper(isz(P));
    vi helper(isz(P),-1);
    auto getHelper = [&](int i) {
        if (i < 0) i += isz(P);
        assert(0 <= i && i < isz(P));
        assert(helper[i] != -1);
        watch("get helper", i+1, helper[i]+1);
        return helper[i];
    };
    auto setHelper = [&](int i, int j) {
        if (i < 0) i += isz(P);
        assert(0 <= i && i < isz(P));
        if (helper[i] == i)
            helper[i] = j;
        else if (helper[i] != -1) {
            int k = helper[i];
            if (P[k].second == P[j].second) {
                //helper[i];
            } else if (P[k].second > P[j].second) {
                helper[i] = j;
            }
        } else
            helper[i] = j;
        watch("set helper", i+1, helper[i]+1);
        /*int prev = helper[i];
        if (prev == -1) {
            helper[i] = j;
            watch("set helper ", j+1, "for edge", i+1);
            return;
        }
        if (P[prev].second*/
        //std::cout << "set helper #" << j+1 << " for an edge #" << i+1 << std::endl;
    };
    auto getEdge = [&](int i) {
        if (i < 0) i += isz(P);
        if (i >= isz(P)) i -= isz(P);
        auto L = P[i], R = getNext(P, i);
        auto [ymin, ymax] = std::minmax({L.second, R.second});
        return tiii(ymin, ymax, i);
    };
    //auto getEdgeId = [&](int i) { return std::get<2>(getEdge(i)); };
    auto getEdgeId = [&](int i) {
        auto [y1,y2,j] = getEdge(i);
        if (y1 == y2) return -1;
        return j;
    };
    //vtiii T2;
    auto coordOfIntersection = [&](int i, int y) -> Frac {
        if (i < 0) i += isz(P);
        if (i >= isz(P)) {
            // special vertical edge
            return currX;
        }
        /*if (calculated[i]) {
            return cachedResult[i];
        }*/
        assert(0 <= i && i < isz(P));
        auto [x1,y1] = P[i];
        auto [x2,y2] = getNext(P, i);
        //ld B = ld(x2-x1)/(y2-y1);
        //Frac B((x2 - x1),(y2 - y1));
        //watch(B);
        //watch(y1 * B);
        //watch(x1 - y1 * B);
        //Frac A = x1 - y1 * B;
        // x1 - y1 * (x2-x1)/(y2-y1)
        // x1 - y1 * (x2-x1)/(y2-y1) + y * (x2-x1)/(y2-y1)
        // (x1 * (y2 - y1) + (y - y1) * (x2 - x1)) / (y2 - y1)
        // (x1 * y2 + y * x2 - y * x1 - y1 * x2) / (y2 - y1)
        assert(y2 != y1);
        //queueToCalculate << i;
        return /*cachedResult[i] = */ld((ld)x1 * y2 + (ld)y * x2 - (ld)y * x1 - (ld)y1 * x2) / (y2 - y1);
        //return Frac(((ll)x1 * y2 + (ll)y * x2 - (ll)y * x1 - (ll)y1 * x2),ll(y2 - y1));
        //return A + y * B;
    };
    /*auto priorityOfEdge = [&](int i) {
        if (i < 0) i += isz(P);
        assert(0 <= i && i < isz(P));
        return coordOfIntersection(i, P[i].second);
    };*/
    /*auto LessByIntersection = [&](const tiii &left, const tiii &right) {
        int j1 = std::get<2>(left);
        int j2 = std::get<2>(right);
        Frac x1 = coordOfIntersection(j1, currY);
        Frac x2 = coordOfIntersection(j2, currY);
        if (x1 > x2) return false;
        if (x1 < x2) return true;
        return left < right;
    };*/
    auto LessByIntersection = [&](const int &j1, const int &j2) {
        Frac x1 = coordOfIntersection(j1, currY);
        Frac x2 = coordOfIntersection(j2, currY);
        if (x1 > x2) return false;
        if (x1 < x2) return true;
        return j1 < j2;
    };
    std::set<int, decltype(LessByIntersection)> T(LessByIntersection);
    auto insertEdgeInT = [&](int i) {
        int ei = getEdgeId(i);
        if (ei == -1) return;
        auto y = P[i].second;
        setCurrY(y);
        //currY = y;
        T.insert(ei);
        /*
        T2.push_back(ei);
        int j = isz(T2)-2;
        while (j >= 0) {
            int j1 = std::get<2>(T2[j]);
            int j2 = std::get<2>(T2[j+1]);
            Frac x1 = coordOfIntersection(j1, y);
            Frac x2 = coordOfIntersection(j2, y);
            if (x1 > x2) {
                std::swap(T2[j], T2[j+1]);
                j--;
            } else {
                break;
            }
        }*/
    };
    auto deleteEdgeFromT = [&](int i) {
        /*{
            auto it = std::find(all(T2), getEdge(i));
            assert(it != T2.end());
            T2.erase(it);
        }*/
        int j = getEdgeId(i);
        if (j == -1) return;
        auto it = T.find(j);
        assert(it != T.end());
        T.erase(it);
        
    };
    // y1 + t * (y2-y1) = y => t = (y - y1)/(y2 - y1)
    // x1 + t * (x2-x1) = x => x1 + (y - y1) * (x2-x1) / (y2 - y1)
    // coeff = (x2 - x1) / (y2 - y1)
    // x1 + (y - y1) * coeff <= x
    // x1 - y1 * coeff + y * coeff <= x
    // A + y * B <= x -- по этим значениям всегда упорядоченность
    auto searchEdgeInT = [&](int i) {
        assert(0 <= i && i < isz(P));
        const auto [x, y] = P[i];
        /*int cand = -1;
        {
            for (int j = 1; j < isz(T2); j++) {
                int j1 = std::get<2>(T2[j-1]);
                int j2 = std::get<2>(T2[j]);
                assert(coordOfIntersection(j1, y) <= coordOfIntersection(j2, y));
            }
            for (const auto &[y1,y2,j] : T2)
                if (coordOfIntersection(j, y) <= x)
                    cand = j;
            assert(cand != -1);
        }*/
        setCurrY(y); setCurrX(x);
        //currY = y;
        //currX = x;
        /*
        if (auto x2 = coordOfIntersection(isz(P), y); x2 != x) {
            std::cout << "x = " << x << " vs x2 = " << x2 << std::endl;
            bool debug = 1;
            watch(x);
            watch(x2);
        }*/
        assert(coordOfIntersection(isz(P), y) == x);
        auto it = T.upper_bound(isz(P));
        assert(it != T.begin());
        int cand2 = *std::prev(it);
        //assert(cand == cand2);
        return cand2;
    };
    vpii diagonals;
    auto addEdgeInTriangles = [&](int u, int v) {
        if (getNext(P, u) != P[v] && getPrev(P, u) != P[v]) {
            diagonals.emplace_back(u,v);
            watch("make diagonal", u+1, v+1);
        }
    };
    for (auto [y,x,i] : pq) {
    //while (isz(pq)) {
        //auto [y,x,i] = pq--;
        x *= -1;
        watch(i+1,x,y);
        setCurrY(y);
        watch("view point #", i+1);
        //std::cout << "view point #" << i+1 << std::endl;
        switch (getTypeOfVertex(P,i)) {
            case START: {
                insertEdgeInT(i);
                setHelper(i, i);
                break;
            }
            case END: {
                addEdgeInTriangles(i, getHelper(i-1));
                /*for (auto help : getHelper(i-1))
                    if (getTypeOfVertex(P,help)>=0)
                        addEdgeInTriangles(i, help);*/
                deleteEdgeFromT(i-1);
                break;
            }
            case SPLIT: {
                int j = searchEdgeInT(i);
                addEdgeInTriangles(i, getHelper(j));
                /*for (auto help : getHelper(j))
                    addEdgeInTriangles(i, help);*/
                setHelper(j, i);
                insertEdgeInT(i);
                setHelper(i, i);
                break;
            }
            case MERGE: {
                //std::cout << "this is merge vertex!" << std::endl;
                addEdgeInTriangles(i, getHelper(i-1));
                //for (auto help : getHelper(i-1))
                //std::cout << "helper for this edge:" << help+1 << std::endl;
                //    if (getTypeOfVertex(P,help)>=0)
                //        addEdgeInTriangles(i, help);
                //    else {
                        //std::cout << "this vertex not a merge vertex!" << std::endl;
                //    }
                deleteEdgeFromT(i-1);
                int j = searchEdgeInT(i);
                addEdgeInTriangles(i, getHelper(j));
                //std::cout << "an edge " << j+1 << " has been found" << std::endl;
                //for (auto help : getHelper(j))
                    //if (getTypeOfVertex(P,help)>=0)
                        //addEdgeInTriangles(i, help);
                    //else {
                        //std::cout << "this vertex not a merge vertex!" << std::endl;
                    //}
                setHelper(j, i);
                break;
            }
            case REGULAR: {
                if (liesAbove(getPrev(P,i), P[i]) && liesBelow(getNext(P,i), P[i])) {
                    addEdgeInTriangles(i, getHelper(i-1));
                    //for (auto help : getHelper(i-1))
                        //if (getTypeOfVertex(P,help))
                            //addEdgeInTriangles(i, help);
                    deleteEdgeFromT(i-1);
                    insertEdgeInT(i);
                    setHelper(i, i);
                } else {
                    int j = searchEdgeInT(i);
                    addEdgeInTriangles(i, getHelper(j));
                    //for (auto help : getHelper(j))
                        //if (getTypeOfVertex(P,j))
                            //addEdgeInTriangles(i, help);
                    setHelper(j, i);
                }
                break;
            }
        };
    }
    if (debug) {
        print("debug.txt", {P}, P, diagonals);
    }
    return diagonals;
}

struct Node {
    Node * next = nullptr;
    Node * prev = nullptr;
    int where{}, id{};
    std::list<int> diagonals{};
    
    void setNext(Node *n) {
        next = n;
        n->prev = this;
    }
    void setPrev(Node *n) {
        prev = n;
        n->next = this;
    }
};

std::ostream &operator<<(std::ostream &os, const Node * node) {
    return os << "(node #" << node->id+1 << " in list " << node->where << ")";
}

vpii removeSameLine(vpii P) {
    //bool debug = 1;
    watch("remove same line: begin");
    vpii newP;
    for (int i = 0; i < isz(P); i++) {
        if (rotation(getPrev(P,i), P[i], getNext(P,i)) != 0) 
            newP << P[i];
    }
    watch("remove same line: end");
    return newP;
}

template<bool debug = 0>
vvpii splitByDiag(vpii P, vpii D) {
    if (isz(P) <= 2)
        return {};
    if (isz(P) == 3) {
        assert(D.empty());
        return {P};
    }
    std::vector<Node *> nodes;
    for (int i = 0; i < isz(P); i++)
        nodes.emplace_back(new Node{nullptr, nullptr, 0, i, {}});
    for (int i = 0; i < isz(nodes); i++)
        nodes[i]->setNext(nodes[(i+1)%isz(nodes)]);
    std::vector<std::pair<Node*, Node*>> diagonals;
    for (const auto &[u,v]:D) {
        assert(0 <= u && u < isz(nodes));
        assert(0 <= v && v < isz(nodes));
        int currDiag = isz(diagonals);
        diagonals.push_back({nodes[u], nodes[v]});
        nodes[u]->diagonals.push_back(currDiag);
        nodes[v]->diagonals.push_back(currDiag);
    }
    std::vector<Node *> listFi, listSe;
    auto isValidDiag = [&](int i) {
        auto [lhs, rhs] = diagonals[i];
        return lhs->where == rhs->where;
    };
    int cntPoly = 1;
    //const bool debug = 0;
    for (int id = 0; id < isz(diagonals); id++) {
        // будем делить относительно этой диагонали
        watch("split", id);
        auto [startFi, startSe] = diagonals[id];
        watch(startFi, startSe);
        auto currFi = startFi, currSe = startSe;
        listFi = {startFi};
        listSe = {startSe};
        while (currFi != startSe && currSe != startFi) {
            listFi.push_back(currFi = currFi->next);
            listSe.push_back(currSe = currSe->next);
        }
        // нужно скопировать две вершины
        nodes.push_back(new Node{nullptr, nullptr, cntPoly, startFi->id, {}});
        Node *copyFi = nodes.back();
        nodes.push_back(new Node{nullptr, nullptr, cntPoly, startSe->id, {}});
        Node *copySe = nodes.back();
        // выбираем список минимальной длины:
        if (listFi.back() != startSe) {
            std::swap(listFi, listSe);
            std::swap(copyFi, copySe);
            std::swap(startFi, startSe);
        }
        assert(listFi.back() == startSe);
        // проходим каждую вершину
        for (int i = 1; i + 1 < isz(listFi); i++) {
            // проходим для неё каждую диагональ
            auto &dd = listFi[i]->diagonals;
            for (auto it = dd.begin(); it != dd.end(); ) {
                // валидная диагональ или нет?
                if (!isValidDiag(*it)) {
                    it = dd.erase(it);
                    continue;
                }
                auto &[lhs, rhs] = diagonals[*it];
                if (lhs == startFi) (lhs = copyFi)->diagonals.push_back(*it);
                if (rhs == startFi) (rhs = copyFi)->diagonals.push_back(*it);
                if (lhs == startSe) (lhs = copySe)->diagonals.push_back(*it);
                if (rhs == startSe) (rhs = copySe)->diagonals.push_back(*it);
                it = std::next(it);
            }
        }
        for (int i = 1; i + 1 < isz(listFi); i++)
            listFi[i]->where = cntPoly;
        copyFi->setNext(listFi[1]);
        
        //copyFi->next = listFi[1];
        copySe->next = copyFi;
        copySe->setNext(copyFi);
        listFi[isz(listFi)-2]->setNext(copySe);
        startFi->setNext(startSe);
        watch(copyFi);
        for (Node *nd = copyFi->next; nd != copyFi; nd = nd->next) {
            watch(nd);
        }
        watch("the copy has been printed!");
        watch(startFi);
        watch(startSe);
        watch(copyFi);
        watch(copySe);
        cntPoly++;
    }
    std::vector<Node *> anyNode(cntPoly);
    for (auto it : nodes)
        anyNode[it->where] = it;
    vvpii answer(cntPoly);
    for (int i = 0; i < cntPoly; i++) {
        Node * start = anyNode[i];
        Node * curr = start;
        do {
            answer[i].push_back(P[curr->id]);
            curr = curr->next;
        } while (curr != start);
        //assert(isMonotone(answer[i]));
        answer[i] = removeSameLine(answer[i]);
    }
    if (debug) {
        print("debug2.txt", answer, P, {});
    }
    watch("splitByDiag: before return");
    for (auto &it : answer)
        assert(isMonotone(it));
    watch("splitByDiag: return");
    for (auto node : nodes)
        delete node;
    return answer;
}

std::mt19937 gen;
int randInt(int a, int b) {
    assert(a <= b);
    return std::uniform_int_distribution<int>(a,b)(gen);
}

vpii generatePoly(int xmin, int xmax, int ymin, int ymax, int n, int limit = 1e6) {
    //bool debug = 1;
    std::set<pii> used;
    auto randPoint = [&](){
        while (true) {
            int x = randInt(xmin, xmax);
            int y = randInt(ymin, ymax);
            if (!used.count(pii(x,y)))
                return pii(x, y);
        }
    };
    vpii kek;
    auto pushPoint = [&](pii p) {
        kek << p;
        used << p;
    };
    pushPoint(randPoint());
    pushPoint(randPoint());
    pushPoint(randPoint());
    while (isz(kek) < n) {
        int attempts = 0;
        while (attempts < limit) {
            attempts++;
            auto p = randPoint();
            int nP{}, nI{};
            for (int i = 0; i + 1 < isz(kek); i++) {
                int t = intersects(kek.back(), p, kek[i], kek[i+1]);
                nP += (t == POINT);
                nI += (t == INSIDE);
            }
            if (!(nI == 0 && nP == 1))
                continue;
            nP = nI = 0;
            for (int i = 0; i + 1 < isz(kek); i++) {
                int t = intersects(kek.front(), p, kek[i], kek[i+1]);
                nP += (t == POINT);
                nI += (t == INSIDE);
            }
            if (nI == 0 && nP == 1) {
                pushPoint(p);
                break;
            }
        }
        if (attempts >= 1000)
            break;
    }
    if (orientedSquare(kek) < 0)
        std::reverse(all(kek));
    return kek;
}

template<bool debug = 0>
vpii TriangulateMonotonePolygon(vpii P) {
    // we need to create chains
    // удалим точки, лежащие на одной прямой
    //bool debug = 1;
    if (isz(P) <= 3)
        return {};
    int ymax = INT_MIN, ymin = INT_MAX, imax = -1;
    for (int i = 0; i < isz(P); i++) {
        if (P[i].second >= ymax) {
            imax = i;
            ymax = P[i].second;
        }
        remin(ymin, P[i].second);
    }
    // если есть два максимума то мы проводим
    const int LEFT_CHAIN = 0,  RIGHT_CHAIN = 1;
    assert(imax != -1);
    vi chainType(isz(P), -1);
    vi chainPos(isz(P), -1);
    std::deque<int> left, right;
    int leftChainBegin = -1, leftChainEnd = -1;
    int i = 0;
    while (i < isz(P)) {
        if (P[i].second == ymax && getNext(P, i).second != ymax) {
            leftChainBegin = i;
            break;
        }
        i++;
    }
    assert(leftChainBegin != -1);
    leftChainEnd = leftChainBegin;
    int pos = 0;
    while (!(P[leftChainEnd].second == ymin && getPrev(P, leftChainEnd).second != ymin)) {
        chainType[leftChainEnd] = LEFT_CHAIN;
        chainPos[leftChainEnd] = pos++;
        leftChainEnd++;
        if (leftChainEnd == isz(P))
            leftChainEnd = 0;
    }
    chainType[leftChainEnd] = LEFT_CHAIN;
    if (chainPos[leftChainEnd] == -1)
        chainPos[leftChainEnd] = pos++;
    pos = 0;
    for (int i = (leftChainBegin-1+isz(P)) % isz(P); chainType[i] == -1; ) {
        chainType[i] = RIGHT_CHAIN;
        chainPos[i] = pos++;
        i--;
        if (i < 0) i = isz(P)-1;
    }        
    watch(__FUNCTION__);
    for (int i = 0; i < isz(P); i++) {
        auto [x,y] = P[i];
        watch(i+1,x,y,chainType[i],chainPos[i]);
    }
    // {y, цепочка, позиция в этой цепочке}
    auto cmp = [&](pii a, pii b) {
        auto [ya, ida] = a;
        auto [yb, idb] = b;
        if (ya < yb) return true;
        if (ya > yb) return false;
        if (chainType[ida] != chainType[idb]) {
            return chainType[ida] < chainType[idb];
        }
        return chainPos[ida] > chainPos[idb];
    };
    
    //std::priority_queue<pii, std::vector<pii>, decltype(cmp)> pq(cmp);
    vpii pq;
    for (int i = 0; i < isz(P); i++) {
        auto [x,y] = P[i];
        pq.push_back({y,i});
    }
    std::sort(pq.rbegin(), pq.rend(), cmp);
    vi S;
    //S << std::get<1>(--pq);
    //S << std::get<1>(--pq);
    S << std::get<1>(pq[0]);
    S << std::get<1>(pq[1]);
    
    vpii diagonals;
    auto addDiagonal = [&](int i, int j) {
        if (getNext(P, i) != P[j] && getPrev(P, i) != P[j]) {
            watch("add diagonal", i+1, j+1);
            diagonals.emplace_back(i, j);
            return true;
        }
        return false;
    };
    int prev = S.back();
    auto printStack = [&]() {
        watch("stack:");
        for (int i = 0; i < isz(S); i++) {
            int id = S[i];
            auto [x,y] = P[id];
            watch(id+1,x,y,chainType[id]);
        }
    };
    auto isSameChain = [&](int i, int j) {
        /*if (P[i].second == ymax || P[j].second == ymax)
            return true;*/
        return chainType[i] == chainType[j];
    };
    //while (isz(pq)) {
    for (const auto &[y, id] : pq) {
        //auto [y,id] = --pq;
        int x = P[id].first;
        watch("view", id+1,x, y);
        if (!isSameChain(id,S.back())) {
            watch("different chain");
            printStack();
            int last = S.back();
            while (isz(S) > 1) {
                addDiagonal(id, S--);
            }
            S = {last, id};
            printStack();
        } else {
            watch("same chain");
            printStack();
            pii first = P[id];
            int want = LEFT;
            int skip = RIGHT;
            if (chainType[id] == LEFT_CHAIN) {
                std::swap(want, skip);
            }
            while (isz(S) >= 2) {
                pii mid = P[S[isz(S)-1]];
                pii last = P[S[isz(S)-2]];
                ll rot = rotation(first, mid, last);
                
                watch(first,mid,last,rot==skip,rot==want);
                if (rot == skip) {
                    break;
                }
                if (rot != want) {
                    S--;
                    continue;
                }
                assert(rot == want);
                addDiagonal(id, S[isz(S)-2]);
                S--;
            }
            S << id;
        }
        prev = id;
    }
    return diagonals;
}

template<bool debug = 0>
std::vector<Triangle> fullAlgo(vpii inP) {
    ll fullSquare = orientedSquare(inP);
    inP = removeSameLine(inP);
    watch("full algo:begin");
    watch(inP);
    vpii D = findDiagonals<debug>(inP);
    watch("diagonals: done");
    vvpii PP = splitByDiag<debug>(inP, D);
    watch("split: done");
    std::vector<Triangle> answ;
    for (auto &P : PP) {
        P = removeSameLine(P);
        if (debug) {
            watch(P, "begin");
        }
        D = TriangulateMonotonePolygon<debug>(P);
        if (debug) {
            watch("call splitByDiag for triangles");
        }
        vvpii triangles = splitByDiag(P, D);
        if (debug) {
            watch("splitByDiag for triangles:done");
        }
        for (auto &t : triangles) {
            /*if (isz(t) != 3) {
                D = TriangulateMonotonePolygon<1>(P);
            }*/
            assert(isz(t) <= 3);
            if (isz(t) == 3) {
                answ.emplace_back(t[0], t[1], t[2]);
            }
            fullSquare -= orientedSquare(t);
        }
        //answ += isz(triangles);
        if (debug) {
            watch(P, "done");
        }
    }
    assert(fullSquare == 0);
    watch("full algo:done");
    return answ;
}


void testMonotone() {
    //bool debug = 1;
    //vpii P{{14,5},{12,6},{11,11},{8,10},{7,11},{3,9},{6,8},{5,5},{2,7},{1,3},{4,1},{7,2},{10,1},{9,4},{13,3}};
    //vpii P{{-3, 5}, {-1, 5}, {4, 5}, {-4, 8}, {-7, 9}, {-10, 5}, {6, -3}, {5, -2}, {-4, 4
//}, {9, 4}};
    //vpii P{{-7, 8}, {-4, 2}, {-9, -9}, {2, 9}, {1, 10}, {-1, 10}, {-5, 9}, {-4, 10}, {-6,
 //10}, {-9, 5}};
    //vpii P{{-10, 6}, {-9, 1}, {-6, -9}, {-6, -3}, {-4, -5}, {-3, -4}, {9, -3}, {-2, 4}, {
//-1, 0}, {-7, -1}};
    //vpii P{{7, -6}, {6, -6}, {6, -4}, {3, 9}, {4, -7}, {1, -10}, {8, -9}, {8, 0}, {7, -1}
//, {6, 7}};
    //vpii P{{3, 5}, {-2, 9}, {3, -5}, {3, -4}, {4, -7}, {9, -6}, {9, -5}, {8, -2}, {2, 7},
 //{7, -1}};
 vpii P{{9, 1}, {6, 1}, {10, 2}, {6, 2}, {10, 4}, {7, 5}, {5, 5}, {4, 10}, {-2, -1}, {
10, 1}};
    //vpii P{{5, -6}, {10, 9}, {7, 0}};
    std::cout << fullAlgo<1>(P) << std::endl;

    for (int nTests = 0; nTests <= 10000; nTests++) {
        watch("start generate P");
        while (true) {
            //P = generatePoly(-10,10,-10,10,10);
            //P = generatePoly(-100,100,-100,100,100);
            P = generatePoly(-1e9,1e9,-1e9,1e9,2000);
            ll s = orientedSquare(P);
            if (s != 0)
                break;
        }
        watch("P: generated");
        //print("poly2.txt", {P},P,{});
        //watch(P);
        //break;
        std::cout << fullAlgo<0>(P).size() << " ";
        //print("poly.txt", PP, P, D);
    }
    std::cout << "OK" << std::endl;
    std::exit(0);
}


int main() {
    //testMonotone();
    //TriangulateMonotonePolygon({{0,0},{2,1},{1,2},{2,3},{0,4},{-2,3},{-1,2},{-2,1}});
    /*for (int w = 1; w <= 10; w++)
        for (int x = 1; x <= 10; x++)
            stress(x,x+w);*/
    //stress();
    //bool debug = 1;
    int n; vpii points;
    readAndScale(n, points);
    ll sq = orientedSquare(points);
    if (sq < 0) {
        std::reverse(all(points));
        sq = -sq;
    }
    watch(sq);
    int xMin = INT_MAX, xMax = INT_MIN;
    for (auto [x,y] : points) {
        remax(xMax, x);
        remin(xMin, x);
    }
    
    std::vector<Triangle> triangles = fullAlgo(points);
    //if (n <= 1000) {
    //    watch(points);
    //    std::list<pii> list(all(points));
    //    while (isz(list) > 3) {
    //        // ищем вершину, являющуюся ухом
    //        for (auto it = list.begin(); it != list.end(); ) {
    //            auto next = (std::next(it) == list.end() ? list.begin() : std::next(it));
    //            auto prev = (it == list.begin() ? std::prev(list.end()) : std::prev(it));
    //            ll rot = rotation(*prev, *it, *next);
    //            if (rot == 0) {
    //                it = list.erase(it);
    //            } else if (rot < 0) {
    //                // проверим на ухо
    //                bool ok = true;
    //                for (auto p : list) {
    //                    bool bad = inside({*prev, *it, *next}, p);
    //                    bad &= !isPointOnSegment(p, *prev, *it);
    //                    bad &= !isPointOnSegment(p, *it, *next);
    //                    bad &= !isPointOnSegment(p, *prev, *next);
    //                    if (bad) {
    //                        ok = false;
    //                        break;
    //                    }
    //                }
    //                if (ok) {
    //                    triangles.emplace_back(*prev, *it, *next);
    //                    it = list.erase(it);
    //                } else {
    //                    it++;
    //                }
    //            } else {
    //                it++;
    //            }
    //        }
    //    }
    //    if (isz(list) == 3) {
    //        triangles.emplace_back(*list.begin(), *(++list.begin()), *(++++list.begin()));
    //    } else
    //        assert(isz(list) < 3);
    //} else {
    //    // берём любую точку и проводим для неё стороны
    //    //std::vector<Triangle> tr;
    //    /*bool ok;
    //    std::tie(triangles,ok) = splitIntoTriangles(points);*/
    //    for (int i = 1; i + 1 < isz(points); i++)
    //        triangles.emplace_back(points[0], points[i], points[i+1]);
    //    //assert(ok);
    //}
    std::pair<ld,ld> res{};
    //bool debug = 1;
    ld ans{};
    for (auto &[A,B,C] : triangles) {
        ans += calcTriangle(A,B,C).first;
        //ans += calcTriangleSlow(A,B,C);
    }
    /*
    for (auto &[A,B,C] : triangles) {
        watch(A,B,C);
        res = res + calcTriangle(A,B,C);
        sq -= doubleSquare<ll>(A,B,C);
    }
    assert(sq == 0);*/
    //std::cout << res.first << std::endl;
    std::cout << ans << std::endl;
}
