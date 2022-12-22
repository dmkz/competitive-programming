//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
std::mutex mtx;
const auto ready = [](){
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    return 1;
}();
// ---- ---- ---- ---- ---- ---- DEBUG LIBRARY ---- ---- ---- ---- ---- ----
#define watch(...) { \
    std::lock_guard lock(mtx); \
    debug && std::cout << "{" << #__VA_ARGS__ << "} = " \
    << std::make_tuple(__VA_ARGS__) << std::endl; \
}

template<typename... X>
std::ostream& operator<<(std::ostream& os, const std::pair<X...>& p) 
{ return os << std::make_tuple(std::get<0>(p), std::get<1>(p)); }

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
    template<typename X> void operator()(X x) 
    { os << (was?", ":(was=1,"")) << x; }
};

template<typename... X>
std::ostream& operator<<(std::ostream& os, const std::tuple<X...>& t)
{ return os << "{", for_each_const(t, Printer(os)), os << "}"; }

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
#undef RANGE_OUTPUT
    
#define OUTPUT2(container, get, pop) template<typename X, typename... T> \
std::ostream& operator<<(std::ostream& os, container<X,T...> c) {       \
    std::vector<X> v(c.size());                                         \
    for (unsigned i = 0; i != v.size(); v[i++] = c.get(),c.pop());      \
    return os << v; }                                                   
OUTPUT2(std::queue,front,pop)
OUTPUT2(std::stack,top,pop)
OUTPUT2(std::priority_queue,top,pop)
#undef OUTPUT
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
// Comparators:
/*
template<typename A, typename B> bool operator >(const A& a, const B& b) { return b < a; }
template<typename A, typename B> bool operator<=(const A& a, const B& b) { return !(a > b); }
template<typename A, typename B> bool operator>=(const A& a, const B& b) { return !(a < b); }
template<typename A, typename B> bool operator!=(const A& a, const B& b) { return a < b || b < a; }
template<typename A, typename B> bool operator==(const A& a, const B& b) { return !(a != b); }*/
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
    template<typename C, typename I, typename X> int lowpos(const C& c, const I& b, const I& e, X x) {
        return int(lower_bound(b,e,x) - begin(c));
    }
    template<typename C, typename I, typename X> int uppos(const C& c, const I& b, const I& e, X x) {
        return int(upper_bound(b,e,x) - begin(c));
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

// Variables:
const int debug = 1;
// -----------------------------------------------------------------------------
std::string keepAfter(std::string s, std::string t) {
    auto p = s.find(t);
    assert(p != s.npos);
    return s.substr(p, isz(t));
}
std::string trim(std::string s) {
    for (int i = 0; i < 2; i++) {
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        std::reverse(all(s));
    }
    return s;
}

namespace Rand {
    std::mt19937 gen;
};
    

namespace Hash {
    const ull mod = (ull(1) << 61) - 1; // prime mod of hashing
    std::vector<ull> pow{1};
    const int base = [](){
        std::uniform_int_distribution<int> dist((int)1.9e9, (int)2e9);
        int tmp = dist(Rand::gen);
        return tmp % 2 == 0 ? tmp - 1 : tmp;
    }();
    
    struct PolyHash {
        // -------- Static functions --------
        static inline ull add(ull a, ull b) {
            // Calculate (a + b) % mod, 0 <= a < mod, 0 <= b < mod
            return (a += b) < mod ? a : a - mod;
        }
        
        static inline ull sub(ull a, ull b) {
            // Calculate (a - b) % mod, 0 <= a < mod, 0 <= b < mod
            return (a -= b) < mod ? a : a + mod;
        }

        static inline ull mul(ull a, ull b){
            // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
            ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
            ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
            ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
            ret = (ret & mod) + (ret >> 61);
            ret = (ret & mod) + (ret >> 61);
            return ret-1;
        }
        
        // -------- Variables of class --------
        std::vector<ull> pref; // polynomial hash on prefix
        
        // Constructor from string:
        PolyHash(const std::string& s) 
            : pref(s.size()+1u, 0) 
        {
            // Pre-calculate powers of base:
            while (pow.size() <= s.size()) {
                pow.push_back(mul(pow.back(), base));
            }
            // Calculate polinomial hash on prefix:
            for (int i = 0; i < (int)s.size(); ++i) {
                pref[i+1] = add(mul(pref[i], base), s[i]);
            }
        }
        
        // Constructor from vector:
        template<typename T> PolyHash(const std::vector<T>& v) 
            : pref(v.size()+1u, 0) 
        {
            // Pre-calculate powers of base:
            while (pow.size() <= v.size()) {
                pow.push_back(mul(pow.back(), base));
            }
            // Calculate polinomial hash on prefix:
            for (int i = 0; i < (int)v.size(); ++i) {
                pref[i+1] = add(mul(pref[i], base), v[i]);
            }
        }
        
        // Get hash from [pos, pos+len-1] segment of string
        inline ull operator()(const int pos, const int len) const {
            return sub(pref[pos+len], mul(pref[pos], pow[len]));
        }
    };
}

struct Item {
    int t{};
    std::array<int, 4> resources{};
    std::array<int, 4> robots{};
    std::array<std::multiset<int>, 4> wait{};
    
    uint64_t getHash() const {
        using namespace Hash;
        uint64_t res{};
        res = PolyHash::add(PolyHash::mul(res, base), t+1);
        for (int i = 0; i < 4; i++)
            res = PolyHash::add(PolyHash::mul(res, base), resources[i]+1);
        for (int i = 0; i < 4; i++)
            res = PolyHash::add(PolyHash::mul(res, base), robots[i]+1);
        for (int i = 0; i < 4; i++)
            for (const auto &it : wait[i])
                res = PolyHash::add(PolyHash::mul(res, base), it+1);
        return res;
    }
    
    void addWait(int nextTime, int id) {
        wait[id] << nextTime;
    }
    
    void step() {
        t++;
        for (int i = 0; i < 4; i++)
            resources[i] += robots[i];
        for (int i = 0; i < 4; i++) {
            for (auto it = wait[i].begin(); it != wait[i].end(); ) {
                if (*it == t) {
                    robots[i]++;
                    it = wait[i].erase(it);
                } else {
                    it++;
                }
            }
        }
    }
    
    std::vector<Item> next(const std::array<int, 4> &cost1,
                           const std::array<int, 4> &cost2,
                           const std::array<int, 4> &cost3) const 
    {
        std::vector<Item> res;
        // пробуем построить робота
        for (int i = 0; i < 4; i++) {
            if (resources[0] >= cost1[i] &&
                resources[1] >= cost2[i] &&
                resources[2] >= cost3[i] )
            {
                Item tmp = *this;
                tmp.resources[0] -= cost1[i];
                tmp.resources[1] -= cost2[i];
                tmp.resources[2] -= cost3[i];
                tmp.addWait(t+1,i);
                res.push_back(std::move(tmp));
            }
        }
        // добываем ресурсы
        res.push_back(*this);
        res.back().step();
        return res;
    }
    
    std::vector<Item> nextTime(const std::array<int, 4> &cost1,
                               const std::array<int, 4> &cost2,
                               const std::array<int, 4> &cost3) const 
    {
        // {ожидание}
        for (int i = 0; i < 4; i++)
            assert(isz(wait[i]) == 0);
        std::map<std::array<int, 4>, bool> visited;
        std::vector<std::array<int, 4>> q = {{0,0,0,0}};
        visited[{0,0,0,0}] = 1;
        std::vector<Item> answ;
        for (int i = 0; i < isz(q); i++) {
            // строим роботов всеми возможными способами
            // пробуем построить робота
            auto res = resources;
            for (int j = 0; j < 4; j++) {
                res[0] -= q[i][j]*cost1[j];
                res[1] -= q[i][j]*cost2[j];
                res[2] -= q[i][j]*cost3[j];
            }
            
            answ.push_back(*this);
            
            for (int j = 0; j < 4; j++) {
                answ.back().resources[j] = res[j];
            }
            answ.back().step();
            for (int j = 0; j < 4; j++) {
                answ.back().robots[j] += q[i][j];
            }
            for (int j = 0; j < 4; j++) {
                if (res[0] >= cost1[j] &&
                    res[1] >= cost2[j] &&
                    res[2] >= cost3[j] )
                {
                    auto tmp = q[i];
                    tmp[j]++;
                    if (!visited[tmp]) {
                        visited[tmp] = 1;
                        q.push_back(tmp);
                    }
                }
            }
        }
        // добываем ресурсы
        return answ;
    }
};

std::ostream &operator<<(std::ostream &os, const Item &item) {
    os << "{t:" << item.t;
    print(os << ",res:",all(item.resources));
    print(os << ",rob:",all(item.robots));
    print(os << ",wai:",all(item.wait));
    return os << "}";
}

bool operator<(const Item &a, const Item &b) {
    if (a.t < b.t) return true;
    if (a.t > b.t) return false;
    if (a.resources < b.resources) return true;
    if (a.resources > b.resources) return false;
    if (a.robots < b.robots) return true;
    if (a.robots > b.robots) return false;
    return a.wait < b.wait;
}

uint64_t getRangeHash(auto begin, auto end) {
    using namespace Hash;
    uint64_t res{};
    while (begin != end)
        res = PolyHash::add(PolyHash::mul(res, base), (*begin++)+1);
    return res;
}

using Pair = std::array<uint8_t, 8>;
using PairCompressed = uint64_t;

auto compress(const Pair& pr) {
    PairCompressed res = 0;
    for (int i = 0; i < 8; i++) {
        res *= 256;
        res += pr[i];
    }
    return res;
}

auto decompressToPair(uint64_t mask) {
    Pair pr{};
    for (int i = 7; i >= 0; i--, mask /= 256) {
        pr[i] = mask % 256;
    }
    return pr;
}    

struct MyCompare {

    bool operator()(const uint64_t &lhs,
                    const uint64_t &rhs) const
    {
        return (*this)(decompressToPair(lhs),decompressToPair(rhs));
    }

    bool operator()(const std::array<uint8_t, 8> &lhs,
                    const std::array<uint8_t, 8> &rhs) const
    {
        for (int i = 3; i >= 0; i--) {
            // first - most important resource
            if (lhs[i] > rhs[i]) return true;
            if (lhs[i] < rhs[i]) return false;
            // second - most important robot
            if (lhs[i+4] > rhs[i+4]) return true;
            if (lhs[i+4] < rhs[i+4]) return false;
        }
        return false;
    }

};

struct Dynamic
{
    using State = std::array<int, 6>;

    std::unordered_map<uint64_t, int> dp;
    
    auto &getDP(const State &st) {
        return dp[getRangeHash(all(st))];
    }
    
    std::array<std::array<int, 3>, 4> cost{};
    
    std::set<State> curr, next;
    
    Dynamic(const std::array<int, 4> &cost1 = {},
            const std::array<int, 4> &cost2 = {},
            const std::array<int, 4> &cost3 = {})
    {
        curr = {};
        next = {{0,0,0,1,0,0}};
        for (int j = 0; j < 4; j++) {
            cost[j][0] = cost1[j];
            cost[j][1] = cost2[j];
            cost[j][2] = cost3[j];
        }
        for (int t = 1; t <= 24; t++) {
            curr = next;
            next.clear();
            pii max{0,0};
            for (const auto &st : curr) {
                std::remax(max, update(st));
            }
            watch(t, max);
        }
    }
    
    std::pair<int, int> update(State currState)
    {
        //print(std::cout << "curr = ", all(currState)) << std::endl;
        int currMax = getDP(currState);
        int nextMax = currMax;
        bool ok0{1},ok1{1},ok2{1},ok3{1};
        std::array<int, 4> lim{255,255,255,255};
        for (int j = 0; j < 4; j++)
            for(int i = 0; i < 3; i++) {
                int tmp = 255;
                if (cost[j][i] > 0) {
                    tmp = currState[i] / cost[j][i];
                }
                std::remin(lim[j], tmp);
            }
        //print(std::cout << "lim: ", all(lim));
        for (int n0 = 0; n0 <= lim[0]; n0++) {
            for (int n1 = 0; n1 <= lim[1]; n1++) {
                for (int n2 = 0; n2 <= lim[2]; n2++) {
                    for (int n3 = 0; n3 <= lim[3]; n3++) {
                        std::array<int, 3> nextTemp{};
                        bool ok = true;
                        for (int i = 0; i < 3; i++) {
                            nextTemp[i] = currState[i];
                            nextTemp[i] -= cost[0][i] * n0;
                            nextTemp[i] -= cost[1][i] * n1;
                            nextTemp[i] -= cost[2][i] * n2;
                            nextTemp[i] -= cost[3][i] * n3;
                            ok &= (nextTemp[i] >= 0);
                        }
                        if (ok) {
                            // считаем динамику
                            State nextState = currState;
                            for (int i = 0; i < 3; i++)
                                nextState[i] = nextTemp[i];
                            for (int i = 0; i < 3; i++)
                                nextState[i] += nextState[i+3];
                            nextState[3] += n0;
                            nextState[4] += n1;
                            nextState[5] += n2;
                            //print(std::cout << "\tnext = ", all(nextState)) << std::endl;
                            std::remax(nextMax, currMax + n3);
                            if (getDP(nextState) <= currMax + n3) {
                                getDP(nextState) = currMax + n3;
                                next.insert(nextState);
                            }
                        }
                    }
                }
            }
            //print(std::cout << "\tnext = ", all(nextState)) << std::endl;
        }
        return {currMax, nextMax};
    }
};


template<typename T, size_t N>
std::ostream &print_array(std::ostream &os, const std::array<T,N>& arr) {
    os << "{";
    for (size_t i = 0; i < N; i++) {
        if (i > 0) os << ",";
        os << (int)arr[i];
    }
    return os << "}";
}

struct Blueprint {
    int id{};
    std::array<int, 4> cost1{};
    std::array<int, 4> cost2{};
    std::array<int, 4> cost3{};
    std::array<std::array<int, 4>, 3> cost{};
    Blueprint(std::string s) {
        int code = sscanf(s.c_str(), "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.",
        &id, &cost1[0], &cost1[1], &cost1[2], &cost2[2],
        &cost1[3], &cost3[3]);
        watch(id, s);
        for (int j = 0; j < 4; j++) {
            cost[0][j] = cost1[j];
            cost[1][j] = cost2[j];
            cost[2][j] = cost3[j];
        }
        assert(code == 7);
        {
            std::lock_guard lock(mtx);
            std::cout << "id = " << id << std::endl;
            for (int i = 0; i < 4; i++) {
                
                std::cout << "robot #" << i << ": " << cost1[i] << ' ' << cost2[i] << ' ' << cost3[i] << std::endl;
            }
        }
        //Dynamic dp(cost1, cost2, cost3);
    }
    
    std::unordered_map<uint64_t, int> cache;
    
    int bfs(Item item) {
        std::map<int, std::set<Item>> levels;
        levels[item.t] = {item};
        int res = 0;
        for (int t = item.t; t <= 24; t++) {
            watch(t, isz(levels[t]));
            for (const auto &it : levels[t]) {
                //watch(it);
                auto next = it.nextTime(cost1, cost2, cost3);
                levels[t+1].insert(all(next));
                std::remax(res, it.resources[3]);
            }
        }
        return res;
    }
    std::map<uint64_t, uint64_t> from;
    int bfs3(Item item) {
        const int queueLimit = 10000; //INT_MAX;
        
        watch(sizeof(Pair));
        
        
        //std::map<int, std::vector<Pair>> levels;
        Pair start{};
        for (int i = 0; i < 4; i++) {
            start[i] = item.resources[i];
            start[i+4] = item.robots[i];
        }
        std::set<PairCompressed, MyCompare> currLevel, nextLevel;
        assert(decompressToPair(compress(start)) == start);
        nextLevel = {compress(start)};
        int best = 0, nextBest = 0;
        bool haveObsidian = false;
        for (int t = item.t; t <= 32; t++)
        {
            currLevel = nextLevel;
            nextLevel.clear();
            watch(id, t, isz(currLevel));            
            //nextLevel.reserve(8 * isz(currLevel));
            for (auto &itMask : currLevel) {
                const Pair &it = decompressToPair(itMask);
                std::remax(best, it[3]);
                //print_array(std::cout << "curr = ", it) << std::endl;
                std::array<int, 4> canBuild{INT_MAX, INT_MAX, INT_MAX, INT_MAX};
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 4; j++) {
                        int tmp = INT_MAX;
                        if (cost[i][j] > 0) {
                            tmp = it[i] / cost[i][j];
                        }
                        //watch(i,j,tmp,cost[i][j],(int)it[i]);
                        std::remin(canBuild[j], tmp);
                    }
                }
                //print_array(std::cout << " lim = ", canBuild) << std::endl;
                for (int i = 0; i < 4; i++) {
                    assert(canBuild[i] < INT_MAX);
                }
                std::array<int,4> x{};
                for (x[3] = canBuild[3]; x[3] >= 0; x[3]--)
                for (x[2] = canBuild[2]; x[2] >= 0; x[2]--)
                for (x[1] = canBuild[1]; x[1] >= 0; x[1]--)
                for (x[0] = canBuild[0]; x[0] >= 0; x[0]--)
                {
                    if (x[0] + x[1] + x[2] + x[3] > 1) continue;
                    std::array<int,4> next{};
                    for (int i = 0; i < 4; i++)
                        next[i] = it[i];
                    bool ok = true;
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 4; j++) {
                            next[i] -= x[j] * cost[i][j];
                            ok &= (next[i] >= 0);
                        }
                    }
                    if (ok) {
                        Pair nextState = it;
                        
                        for (int i = 0; i < 4; i++)
                            nextState[i] = next[i];
                        for (int i = 0; i < 4; i++)
                            nextState[i] += nextState[i+4];
                        for (int i = 0; i < 4; i++)
                            nextState[i+4] += x[i];
                        std::remax(nextBest, nextState[3]);
                        if (t <= 32) {
                            nextLevel.insert(compress(nextState));
                            from[compress(nextState)] = itMask;
                        }
                        if (isz(nextLevel) > queueLimit) {
                            nextLevel.erase(std::prev(nextLevel.end()));
                        }
                    }
                }
            }
        }
        auto node = *nextLevel.begin();
        /*std::cout << "path:\n";
        while(true) {
            auto arr = decompressToPair(node);
            print_array(std::cout, arr) << std::endl;
            if (auto it = from.find(node); it != from.end())
                node = it->second;
            else break;
        }*/
        return nextBest;
    }
    
    int bfs2(Item item) {
        using Pair = std::array<uint8_t, 8>;
        watch(sizeof(Pair));
        using PairCompressed = uint64_t;
        auto compress = [](const Pair& pr) {
            PairCompressed res = 0;
            for (int i = 0; i < 8; i++) {
                res *= 256;
                res += pr[i];
            }
            return res;
        };        
        auto decompressToPair = [](PairCompressed mask) {
            Pair pr{};
            for (int i = 7; i >= 0; i--, mask /= 256) {
                pr[i] = mask % 256;
            }
            return pr;
        };
        using Triple = std::array<uint8_t, 12>;
        watch(sizeof(Triple));
        //std::map<int, std::vector<Pair>> levels;
        Pair start{};
        for (int i = 0; i < 4; i++) {
            start[i] = item.resources[i];
            start[i+4] = item.robots[i];
        }
        std::unordered_set<PairCompressed> currLevel, nextLevel;
        assert(decompressToPair(compress(start)) == start);
        nextLevel = {compress(start)};
        int best = 0, nextBest = 0;
        bool haveObsidian = false;
        for (int t = item.t; t <= 24; t++)
        {
            currLevel = nextLevel;
            nextLevel.clear();
            watch(id, t, isz(currLevel));
            std::array<uint8_t, 4> canBuild{};
            auto getCost = [&](int j, int x) {
                std::array<uint8_t, 4> ar{};
                int tmp = cost1[j] * x;
                assert(tmp <= 255);
                ar[0] = uint8_t(tmp);
                tmp = cost2[j] * x;
                assert(tmp <= 255);
                ar[1] = uint8_t(tmp);
                tmp = cost3[j] * x;
                assert(tmp <= 255);
                ar[2] = uint8_t(tmp);
                return ar;
            };
            for (auto &itMask : currLevel) {
                Pair it = decompressToPair(itMask);
                for (int j = 0; j < 4; j++) {
                    int x = 0;
                    while (
                        it[0] >= cost1[j] * x &&
                        it[1] >= cost2[j] * x &&
                        it[2] >= cost3[j] * x) x++;
                    if (x > 255) x = 255;
                    std::remax(canBuild[j], uint8_t(x));
                }
                std::remax(best, it[3]);
            }
            //nextLevel.reserve(8 * isz(currLevel));
            for (auto &itMask : currLevel) {
                Pair it = decompressToPair(itMask);
                std::array<int, 4> res{};
                for(int i = 0; i < 4; i++) {
                    res[i] += it[i];
                }
                if (res[3] < best) continue;
                for (uint8_t x3 = 0; x3 <= canBuild[3]; x3++) {
                    bool ok1 = true;
                    auto tmp3 = getCost(3, x3);
                    for(int i = 0; i < 4; i++) {
                        res[i] -= tmp3[i];
                        ok1 &= (res[i] >= 0);
                    }
                    for (uint8_t x1 = 0; ok1 && x1 <= canBuild[1]; x1++) {
                        bool ok2 = true;
                        auto tmp1 = getCost(1, x1);
                        for(int i = 0; i < 4; i++) {
                            res[i] -= tmp1[i];
                            ok2 &= (res[i] >= 0);
                        }
                        for (uint8_t x2 = 0; ok2 && x2 <= canBuild[2]; x2++) {
                            bool ok3 = true;
                            auto tmp2 = getCost(2, x2);
                            for(int i = 0; i < 4; i++) {
                                res[i] -= tmp2[i];
                                ok3 &= (res[i] >= 0);
                            }
                            for (uint8_t x0 = 0; ok3 && x0 <= canBuild[0]; x0++) {
                                bool ok = true;
                                auto tmp0 = getCost(0, x0);
                                for(int i = 0; i < 4; i++) {
                                    res[i] -= tmp0[i];
                                    ok &= (res[i] >= 0);
                                }
                                if (ok) {
                                    Pair next{};
                                    for (int i = 0; i < 4; i++) {
                                        assert(res[i] <= 255);
                                        next[i] = uint8_t(res[i]);
                                        next[i+4] = it[i+4];
                                    }
                                    for (int i = 0; i < 4; i++)
                                        next[i] += next[i+4];
                                    next[4] += x0;
                                    next[5] += x1;
                                    next[6] += x2;
                                    next[7] += x3;
                                    if (nextBest <= next[3] && t < 24) {
                                        nextLevel.insert(compress(next));
                                    }
                                    std::remax(nextBest, next[3]);
                                }
                                for(int i = 0; i < 4; i++) {
                                    res[i] += tmp0[i];
                                }
                            }
                            for(int i = 0; i < 4; i++) {
                                res[i] += tmp2[i];
                            }
                        }
                        for(int i = 0; i < 4; i++) {
                            res[i] += tmp1[i];
                        }
                    }
                    for(int i = 0; i < 4; i++) {
                        res[i] += tmp3[i];
                    }
                }
            }
        }
        return nextBest;
    }
    
    int dfs(Item item) {
        auto hash = item.getHash();
        if (auto it = cache.find(hash); it != cache.end())
            return it->second;
        //watch(item);
        if (item.t == 20) {
            item.step();
            int res = item.resources[3];
            //watch("calculated", item, res);
            return res;
        }
        auto next = item.next(cost1, cost2, cost3);
        int res = 0;
        for (const auto &it : next)
            std::remax(res, dfs(it));
        assert(cache.find(hash) == cache.end());
        /*
        if (auto it = cache.find(item); it != cache.end()) {
            assert(
            watch("cycle", item);
        }
        watch("cache", item);*/
        //watch("cached", item, res);
        cache[hash] = res;
        if (isz(cache) % (1 << 17) == 0)
            watch(isz(cache));
        return res;
    }
    
    int result() {
        Item start;
        start.t = 1;
        start.robots[0] = 1;
        int res = bfs3(start);
        return res;
    }
};

bool operator==(const Blueprint& a, const Blueprint &b) {
    return a.cost1 == b.cost1 && a.cost2 == b.cost2 && a.cost3 == b.cost3;
}

bool operator!=(const Blueprint& a, const Blueprint &b) {
    return !(a == b);
}

int main() {
    std::string s;
    std::vector<std::thread> threads;
    std::vector<Blueprint> data;
    vvi ids;
    int total{};
    while(std::getline(std::cin, s)) {
        s = trim(s);
        //Blueprint blue(s);
        //threads.emplace_back([s](){           
            Blueprint blueprint(s);
            if (blueprint.id > 3) break;
            int res = blueprint.result();
            {
                std::lock_guard lock(mtx);
                std::cout << "result #" << blueprint.id << ": " << res << std::endl;
                total += blueprint.id * res;
            }
            
            //return 0;
        //});
    }
    for (auto &it : threads)
        it.join();
    std::cout << "total = " << total << std::endl;
    return 0;
}

