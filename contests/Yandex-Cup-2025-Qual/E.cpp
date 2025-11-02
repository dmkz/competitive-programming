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
#ifndef __NUMERIC_HPP__
#define __NUMERIC_HPP__
namespace algos {
namespace numeric {
    
    template<typename T, typename N> 
    inline T binpow(T a, N n) {
        T r(1);
        while (n > 0) {
            if (n & 1) { r *= a; }
            a *= a; n >>= 1;
        }
        return r;
    }
    
    template<typename T, typename N>
    inline T geometricSum(T q, N n) {
        if (n == 0) return 0;
        if (n == 1) return 1;
        if (n % 2 == 0)
            return (q+1)*geometricSum(q*q,n/2);
        return q*geometricSum(q, n-1)+1;
    }
    
    template<int mod>
    struct IntMod {
        int value;
        IntMod(int value_ = 0) : value(value_) {
            if (value >= mod || value < 0) value %= mod;
            if (value < 0) value += mod;
        }
        IntMod(ll x) {
            if (x >= mod || x < 0) x %= mod;
            if (x < 0) x += mod;
            value = int(x);
        }
        IntMod& operator+=(IntMod num) {
            value += num.value;
            if (value >= mod) value -= mod;
            return *this;
        }
        IntMod& operator-=(IntMod num) {
            value -= num.value;
            if (value < 0) value += mod;
            return *this;
        }
        IntMod operator-() const { return IntMod(0) - *this; }
        IntMod operator+(IntMod num) const { return IntMod(*this) += num; }
        IntMod operator-(IntMod num) const { return IntMod(*this) -= num; }
        IntMod operator*(IntMod num) const { return IntMod(int(value * 1LL * num.value % mod)); }
        IntMod& operator*=(IntMod num) { return *this = *this * num; }
        IntMod operator/(IntMod num) const { return *this * binpow(num, mod-2); }
        IntMod& operator/=(IntMod num) { return *this = *this / num; }
        
        friend bool operator<(const IntMod<mod> &a, const IntMod<mod> &b){
            return a.value < b.value;
        }
        friend std::ostream& operator<<(std::ostream& os, const IntMod<mod>& num) {
            return os << num.value;
        }
        GEN_COMPARATORS_MEMBERS(IntMod<mod>)
    };

    template<int mod>
    struct Combinatorics {
        
        int N;
        std::vector<IntMod<mod>> fact, ifact;
        
        Combinatorics(int n_)
            : N(n_), fact(N+1,1), ifact(N+1,1)
        {
            for (int i = 2; i <= N; i++)
                fact[i] = fact[i-1] * i;
            ifact[N] = fact[0] / fact[N];
            for (int i = N-1; i >= 0; i--)
                ifact[i] = ifact[i+1] * (i+1);
        }
        
        IntMod<mod> operator()(int n, int k) const {
            return C(n, k);
        }
        
        IntMod<mod> C(int n, int k) const {
            if (k < 0 || k > n || n < 0) return 0;
            return fact[n] * ifact[k] * ifact[n-k];
        }
        
    };
    
    template<typename T>
    void gauss(std::vector<std::vector<T>> &a) {
        const int n = (int)a.size();
        assert((int)a[0].size()+1 == n);
        // решаем СЛАУ
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                T coeff = (a[j][i] / a[i][i]);
                for (int k = i; k <= n; k++)
                    a[j][k] -= a[i][k] * coeff;
            }
        }
        for (int i = 0; i < n; i++)
            a[i].back() /= a[i][i];
    }
    
    template<typename T>
    void gauss(std::vector<std::vector<T>> &a, std::vector<T> &b) {
        const int n = (int)a.size();
        assert((int)a[0].size() == n);
        assert((int)b.size() == n);
        // решаем СЛАУ
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) 
                if (i != j) {
                    T coeff = (a[j][i] / a[i][i]);
                    for (int k = i; k < n; k++)
                        a[j][k] -= a[i][k] * coeff;
                    b[j] -= coeff * b[i];
                }
        // находим ответ:
        for (int i = 0; i < n; i++)
            b[i] /= a[i][i];
    }
    
    template<typename T>
    struct Poly : public std::vector<T>
    {    
        Poly() : std::vector<T>(){}

        Poly(const std::vector<std::pair<T,T>> & points)
            : std::vector<T>(points.size())    
        {
            interpolate(points);
        }
        
        void interpolate(const auto & points)
        {
            const int n = (int)points.size();
            // строим систему линейных уравнений
            std::vector a(n, std::vector(n+1, T(0)));
            for (int i = 0; i < n; i++) {
                const auto [x, f] = points[i];
                T px = 1;
                for (int j = 0; j < n; j++) {
                    a[i][j] = px;
                    px *= x;
                }
                a[i][n] = f;
            }
            // решаем СЛАУ
            gauss(a);
            // находим ответ
            this->resize(n);
            for (int i = n-1; i >= 0; i--)
                (*this)[i] = a[i].back();
        }
        
        T operator()(T x) const {
            T px = 1, res = 0;
            for (const auto &c : *this) {
                res += c * px;
                px *= x;
            }
            return res;
        }
        
    };

    inline int addmod(int a, int b, int mod) {
        return (a += b) >= mod ? a -= mod : a;
    }
    
    inline int submod(int a, int b, int mod) {
        return (a -= b) < 0 ? a += mod : a;
    }
    
    inline int mulmod(int a, int b, int mod) {
        return int(1LL * a * b % mod);
    }
    
    inline int powmod(int x, int64_t n, int mod) {
        if (x < 2) { return x; }
        int res = 1;
        while (n > 0) {
            if (n & 1) { res = mulmod(res,x,mod); }
            n >>= 1; x = mulmod(x,x,mod);
        }
        return res;
    }

    inline int totient(int x) {
        int res = 1;
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                int p = 1;
                x /= i;
                while (x % i == 0) {
                    p *= i; x /= i;
                }
                res *= (i - 1) * p;
            }
        }
        if (x > 1) { res *= (x-1); }
        return res;
    }

    inline int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    inline vi primeDivisors(int x) {
        vi answ;
        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                answ.push_back(i);
                x /= i;
                while (x % i == 0) { x /= i; }
            }
        }
        if (x > 1) { answ.push_back(x); }
        return answ;
    }

    inline int primitiveRoot(const int mod) {
        int tot = totient(mod);
        vi divs = primeDivisors(tot);
        for (auto &it : divs) {
            it = tot / it;
        }
        for (int i = 2; i < mod; ++i) {
            bool ok = true;
            for (int p : divs) {
                if (powmod(i,p, mod) == 1) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                int root = i;
                return root;
            }
        }
        return -1;
    }

    inline int logmod(int root, int y, const int mod)
    {
        // root ^ x == y
        int k = (int)std::sqrt(mod);
        std::vector<pii> big, small;
        int inv = powmod(root, mod-2, mod);
        small.resize(k);
        small[0] = pii(y, 0);
        for (int i = 1; i < k; ++i) {
            auto prev = small[i-1];
            prev.first = mulmod(prev.first, inv, mod);
            prev.second++;
            small[i] = prev;
        }
        big.resize((mod+k-1)/k);
        int rootK = powmod(root,k, mod);
        big[0] = pii(1, 0);
        for (int i = 1; i < isz(big); ++i) {
            big[i].first = mulmod(big[i-1].first, rootK, mod);
            big[i].second = i * k;
        }
        std::sort(all(big));
        std::sort(all(small));
        for (auto &pair : big) {
            auto it = std::lower_bound(all(small), pii(pair.first, 0));
            if (it == small.end() || it->first != pair.first) {
                continue;
            }
            int p = pair.second + it->second;
            assert(powmod(root, p, mod) == y);
            return p;
        }
        return -1;
    }
} // namespace numeric
} // namespace algos
#endif // __NUMERIC_HPP__
#ifndef __SEGMENTTREELAZYTRAITS_HPP__
#define __SEGMENTTREELAZYTRAITS_HPP__
namespace algos {
namespace SegmentTreeLazyTraits {
    inline int getBase() { return 0; }
    /*******************************************************************************
     *  Use Traits<Value,Extra> for definition of:
     *      1)  neutral element for `Value`;
     *      2)  neutral element for `Extra`;
     *      3)  how should combine `Extra` with `Value`;
     *      4)  how should combine `Value` with `Value` (children to root);
     *      5)  how should combine `Extra` with `Extra`;
     *  See examples below: TraitsMinAdd<Value, Extra>
     ******************************************************************************/
    
    /*******************************************************************************
     *  Available traits, implemented in header file SegmentTreeLazyTraits.hpp
     ******************************************************************************/
    template<typename Value, typename Extra> struct LazyMinAdd;
    template<typename Value, typename Extra> struct LazyMaxAdd;
    template<typename Value, typename Extra> struct LazySumSet;
    template<typename Value, typename Extra> struct LazySumAdd;
    template<typename Value, typename Extra> struct LazySumMul;
    template<typename Value, typename Extra> struct LazyGeomSumMul;
    
    /*******************************************************************************
     *  Traits for minimal value on segment. 
     *  Get-query:    get minimal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazyMinAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::max(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::min(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };
    
    /*******************************************************************************
     *  Traits for maximal value on segment. 
     *  Get-query:    get maximal value in segment [l, r]
     *  Update-query: add const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazyMaxAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return std::numeric_limits<Value>::min(); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = std::max(getValue(lt), getValue(rt));
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };   
    
    /*******************************************************************************
     *  Traits for sum of values on segment. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: set const to each value in segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazySumSet {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return std::numeric_limits<Extra>::min(); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.extra() == extraNeutral() ? src.value() : src.len() * src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() = src.extra();
        }
    };
    /*******************************************************************************
     *  Traits for sum on segment with addition. 
     *  Get-query:    sum of values on segment [l, r]
     *  Update-query: add const to each value on segment [l, r]
     ******************************************************************************/
    template<typename Value, typename Extra>
    struct LazySumAdd {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(0); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() + src.extra() * src.len();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() += src.extra();
        }
    };
    
    template<typename Value, typename Extra>
    struct LazySumMul {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() { return Value(0); }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(1); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            return src.value() * src.extra();
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() *= src.extra();
        }
    };
    
    template<typename Value, typename Extra>
    struct LazyGeomSumMul {
        // Definition of neutral element for `Value`:
        static Value valueNeutral() {
            // 1 + b + b^2 + ... + b^len-1
            return Value(0);
        }
        // Definition of neutral element for `Extra`:
        static Extra extraNeutral() { return Extra(1); }
        // Definition of how should combine `Extra` with `Value`:
        template<typename Node>
        static Value getValue(const Node& src) {
            auto result = (src.value() == valueNeutral()
                        ? geometricSum(getBase(), src.len()) * binpow(getBase(), src.left())
                        : src.value()) * src.extra();
            return result;
        }
        // Definition of how should combine `Value` with `Value` (children to root):
        template<typename NodeRoot, typename NodeLt, typename NodeRt>
        static void pull(NodeRoot root, const NodeLt& lt, const NodeRt& rt) {
            root.value() = getValue(lt) + getValue(rt);
        }
        // Definition of how should combine `Extra` with `Extra`:
        template<typename NodeDst, typename NodeSrc>
        static void push(NodeDst dst, const NodeSrc& src) {
            dst.extra() *= src.extra();
        }
    };
    
} // namespace SegmentTreeLazyTraits
} // namespace algos
#endif // __SEGMENTTREELAZYTRAITS_HPP__
#ifndef __SEGMENTTREELAZY_HPP__
#define __SEGMENTTREELAZY_HPP__
namespace algos {
namespace SegmentTreeLazy {
using namespace algos::SegmentTreeLazyTraits;
    /*******************************************************************************
     *  SegmentTree<Value, Extra, Traits> - segment tree class with lazy propagation, 0-indexed
     *  Default operations: minimal value on segment and addition on segment for int64_t type
     *  Use Traits<Value,Extra> for definition of:
     *      1)  neutral element for `Value`;
     *      2)  neutral element for `Extra`;
     *      3)  how should combine `Extra` with `Value`;
     *      4)  how should combine `Value` with `Value` (children to root);
     *      5)  how should combine `Extra` with `Extra`;
     *  See examples below: TraitsMinAdd<Value, Extra>
     ******************************************************************************/
    
    /*******************************************************************************
     *  Available traits, implemented below 
     ******************************************************************************/
    template<typename Value, typename Extra> using TraitsMinAdd = LazyMinAdd<Value,Extra>;
    template<typename Value, typename Extra> using TraitsMaxAdd = LazyMaxAdd<Value,Extra>;
    template<typename Value, typename Extra> using TraitsSumSet = LazySumSet<Value,Extra>;
    template<typename Value, typename Extra> using TraitsSumMul = LazySumMul<Value,Extra>;
    
    /*******************************************************************************
     *  SegmentTree, see description above
     ******************************************************************************/
    template<typename Value = int64_t, typename Extra = int64_t, typename Traits = TraitsMinAdd<Value, Extra> >
    struct SegmentTree {
        
        /*******************************************************************************
         *  Node class
         ******************************************************************************/
        struct Node {
            Value value;
            
            Extra extra;
            
            Node(Value value_ = Traits::valueNeutral(), Extra extra_ = Traits::extraNeutral())
                : value(value_), extra(extra_) { }
            
            Value getValue(int l, int r) const { return Traits::getValue(NodeWrapper<Node>(l, r, *this)); }
        };
        
        /*******************************************************************************
         *  NodeWrapper class
         ******************************************************************************/
        template<typename NodeType>
        struct NodeWrapper {
            int l, r;
            NodeType node;
            NodeWrapper(int l_, int r_, NodeType node_)
                : l(l_), r(r_), node(node_) { }
            int  left() const { return l; }
            int right() const { return r; }
            int   mid() const { return (l+r)/2; }
            int   len() const { return r - l + 1; }
            Value& value() { return node.value; }
            Extra& extra() { return node.extra; }
            const Value& value() const { return node.value; }
            const Extra& extra() const { return node.extra; }
        };
        
        /*******************************************************************************
         *  SegmentTree public data: n - number of items, data - vector for nodes
         ******************************************************************************/
        int n; std::vector<Node> data;
        
        
        /*******************************************************************************
         *  Resize segment tree data to needed size
         ******************************************************************************/
        void resize(int n_) {
            n = n_;
            data.assign(2 * n - 1, Node());
        }
        
        /*******************************************************************************
         *  Lazy propagation from node to its children
         ******************************************************************************/
        void push(int v, int l, int r, int m) {
            if (data[v].extra != Traits::extraNeutral()) {
                Traits::push(
                    NodeWrapper<Node&>(l, m, data[v+1]), 
                    NodeWrapper<const Node&>(l, r, data[v])
                );
                Traits::push(
                    NodeWrapper<Node&>(m+1, r, data[v+2*(m-l+1)]), 
                    NodeWrapper<const Node&>(  l, r, data[v])
                );
                data[v].extra = Traits::extraNeutral();
            }
        }
        
        /*******************************************************************************
         *  Update node using children values
         ******************************************************************************/
        void pull(int v, int l, int r, int m) {
            assert(data[v].extra == Traits::extraNeutral());
            Traits::pull(
                NodeWrapper<Node&>(  l, r, data[v]), 
                NodeWrapper<const Node&>(  l, m, data[v+1]), 
                NodeWrapper<const Node&>(m+1, r, data[v+2*(m-l+1)])
            );
        }
        
        /*******************************************************************************
         *  Build segtree from array with given values
         ******************************************************************************/
        template<typename T>
        void build(const std::vector<T>& arr, const int v, const int tl, const int tr) {
            if (tl == tr) {
                data[v] = Node(arr[tl]);
            } else {
                const int tm = (tl + tr) / 2;
                build(arr, v+1,   tl, tm);
                build(arr, v+2*(tm-tl+1), tm+1, tr);
                pull(v, tl, tr, tm);
            }
        }
        
        template<typename T>
        void build(const std::vector<T>& arr) { 
            resize((int)arr.size());
            build(arr, 0, 0, n-1);
        }

        /*******************************************************************************
         *  Get-query on range [ql, qr]
         ******************************************************************************/
        Node get(int ql, int qr, const int v, const int tl, const int tr) {
            if (ql == tl && qr == tr) {
                return data[v];
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                Node ret;
                if (qr <= tm) {
                    ret = get(ql, qr, v+1,   tl, tm);
                } else if (ql > tm) {
                    ret = get(ql, qr, v+2*(tm-tl+1), tm+1, tr);
                } else {
                    const auto lt = get(  ql, tm, v+1,   tl, tm);
                    const auto rt = get(tm+1, qr, v+2*(tm-tl+1), tm+1, tr);
                    Traits::pull(
                        NodeWrapper<Node&>(  ql, qr, ret), 
                        NodeWrapper<const Node&>(  ql, tm, lt), 
                        NodeWrapper<const Node&>(tm+1, qr, rt)
                    );
                }
                pull(v, tl, tr, tm);
                return ret;
            }
        }
        
        Value get(const int ql, const int qr) { return get(ql, qr, 0, 0, n-1).getValue(ql, qr); }
        
        /*******************************************************************************
         *  Update query on range [ql, qr] by extra
         ******************************************************************************/
        void update(const int ql, const int qr, const Extra& extra, const int v, const int tl, const int tr) {
            if (ql == tl && tr == qr) {
                Traits::push(
                    NodeWrapper<Node&>(tl, tr, data[v]),
                    NodeWrapper<Node>(ql, qr, Node(Traits::valueNeutral(), extra))
                );
            } else {
                int tm = (tl + tr) / 2;
                push(v, tl, tr, tm);
                if (qr <= tm) {
                    update(ql, qr, extra, v+1, tl, tm);
                } else if (ql > tm) {
                    update(ql, qr, extra, v+2*(tm-tl+1),tm+1,tr);
                } else {
                    update(ql, tm, extra, v+1,   tl, tm);
                    update(tm+1, qr, extra, v+2*(tm-tl+1), tm+1, tr);
                }
                pull(v, tl, tr, tm);
            }
        }

        void update(const int ql, const int qr, const Extra& extra) {
            update(ql, qr, extra, 0, 0, n-1); 
        }

    };
    
} // namespace SegmentTreeLazy
} // namespace algos
#endif // __SEGMENTTREELAZY_HPP__
using namespace algos::numeric;
const int mod = (int)1e9+7;
using Int = IntMod<mod>;
using namespace algos::SegmentTreeLazy;
using SegTreeMul = SegmentTree<Int, Int,
                       TraitsSumMul<Int, Int>>;
using SegTreeAdd = SegmentTree<Int, Int,
                       LazySumAdd<Int, Int>>;
/*
    5 3
    1 3 1 2
    2 4 1 3
    3 4 5 6
    
    1 2 3 4
    * * *   1/2
      * * * 1/3
        * * 5/6
    1/2 * 2/3 + 1/3 * 1/2 = 1/3 + 1/6 = 3 / 6 = 1/2
    
    prod(1 - a[j]) * sum(a[i] / (1 - a[i]))
    P * S
    
    1/2 1/2 361111114 611111116 0 
*/
main() {
    int n, nQueries;
    std::cin >> n >> nQueries;
    SegTreeMul stMul;
    SegTreeAdd stAdd;
    //Fenwick<Int> stAdd(n+1);
    stMul.build(std::vector<Int>(n, 1));
    stAdd.build(std::vector<Int>(n, 0));
    std::vector<Int> prod(n, 1), sum(n, 0);
    while (nQueries --> 0) {
        int l, r, p, q;
        std::cin >> l >> r >> p >> q;
        l--, r--;
        Int ai = Int(p) / q;
        //for (int i = l; i <= r; i++) {
        //    prod[i] *= Int(1) - ai;
        //    sum[i] += ai / (Int(1) - ai);
        //}
        stMul.update(l, r, Int(1) - ai);
        stAdd.update(l, r, ai / (Int(1) - ai));
    }
    for (int i = 0; i < n; i++) {
        //assert(stMul.get(i, i) == prod[i]);
        //assert(stAdd.get(i, i) == sum[i]);
        std::cout << stMul.get(i, i) * stAdd.get(i, i) << std::endl;
        //std::cout << prod[i] * sum[i] << std::endl;
    }
    std::cout << std::endl;
}
