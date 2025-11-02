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

const int debug = 0;
#endif // __DEBUG_HPP__
#ifndef __SPARSETABLE_HPP__
#define __SPARSETABLE_HPP__

#ifndef isz
#define isz(x) (int)std::size(x)
#endif
namespace algos {
namespace SparseTable {
    
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
    
    T operator()(int L, int R) const {
        return calcFunc(L, R);
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

template<typename T>
struct GCD {
    T neutral() const {
        return T(0);
    }
    T operator()(const T&a, const T&b) const {
        return std::gcd(a, b);
    }
};
} // namespace SparseTable
} // namespace algos
#endif // __SPARSETABLE_HPP__
using namespace algos::SparseTable;

const int AMAX = (int)1e7+100;
int firstDiv[AMAX];
void precalc() {
    for (int x = 2; x * x < AMAX; x++)
        if (!firstDiv[x])
            for (int y = x * x; y < AMAX; y += x)
                if (!firstDiv[y])
                    firstDiv[y] = x;
    for (int x = 1; x < AMAX; x++)
        if (!firstDiv[x])
            firstDiv[x] = x;
}

vpii factor(int x) {
    vpii res;
    while (x > 1) {
        int p = firstDiv[x];
        if (res.empty() || res.back().first != p)
            res.push_back({p, 0});
        if (res.back().first == p)
            res.back().second++;
        x /= p;
    }
    return res;
}
/*
    2^3 2^2 2^2 2^0 2^0 2^0
*/
ll solve(const vi &a) {
    bool debug = 1;
    SparseTable<int, GCD<int>> st(a);
    ll answ = 0;
    for (int i = 0; i < isz(a); i++) {
        //watch(a);
        int curr = a[i], p = i;
        while (p < isz(a)) {
            int start = p;
            {
                int low = p, high = isz(a);
                while (high - low > 1) {
                    int mid = (low + high) / 2;
                    if (st(p, mid) == curr) {
                        low = mid;
                    } else {
                        high = mid;
                    }
                }
                p = high;
            }
            answ += curr * ll(p - start);
            if (p < isz(a))
                curr = std::gcd(curr, a[p]);
        }
    }
    return answ;
}
void solve() {
    bool debug = 1;
    int n; std::cin >> n;
    std::vector<vi> a(1, vi{});
    for (int i = 0; i < n; i++) {
        int x; std::cin >> x;
        auto divs = factor(x);
        bool ok = true;
        for (const auto &[p,k] : divs)
            if (k < 2)
                ok = false;
        if (!ok) {
            a.push_back({});
        } else {
            a.back().push_back(x);
        }
    }
    ll answ = 0;
    for (auto &aa : a)
        answ += solve(aa);
    std::cout << answ << std::endl;
}
bool isPrime(int x) {
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0)
            return false;
    return (x > 1);
}
void check() {
    int x = 1;
    int p = 1;
    while (true) {
        while (!isPrime(p))
            p++;
        if (x <= (int)1e7 / (p * p)) {
            x *= p * p;
            std::cout << p << "^2 ";
            p++;
        } else {
            break;
        }
    }
    std::cout << std::endl;
    std::exit(0);
}
main() {
    //check();
    precalc();
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
