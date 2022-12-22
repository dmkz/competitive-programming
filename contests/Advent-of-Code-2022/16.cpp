//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>
#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)
const auto ready = [](){
    std::ios_base::sync_with_stdio(0); std::cin.tie(0);
    std::cout << std::fixed << std::setprecision(12);
    return 1;
}();
// ---- ---- ---- ---- ---- ---- DEBUG LIBRARY ---- ---- ---- ---- ---- ----
#define watch(...) debug && std::cout << "{" << #__VA_ARGS__ << "} = " \
    << std::make_tuple(__VA_ARGS__) << std::endl

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
using vs = std::vector<std::string>;
std::string trim(std::string s) {
    for (int i = 2; i > 0; i--) {
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        std::reverse(all(s));
    }
    return s;
}
vs split(std::string s, char c) {
    vs res{1,""};
    for (int i = 0; i < isz(s); i++) {
        if (s[i] == c) {
            res.push_back("");
        } else {
            res.back() += s[i];
        }
    }
    return res;
}
bool keepAfter(std::string &s, std::string t) {
    int p = s.find(t);
    if (p != s.npos) {
        s = s.substr(p+isz(t));
        return true;
    } return false;
}

void part1() {
    std::string s;
    int nV{}, nE{};
    std::map<std::string, int> vertRate;
    std::map<std::string, int> vertId;
    std::map<std::string, vs> vertNext;
    while(std::getline(std::cin, s)) {
        s = trim(s);
        assert(keepAfter(s, "Valve "));
        std::string curr = s.substr(0, 2);
        assert(keepAfter(s, "rate="));
        int rate; sscanf(s.c_str(), "%d", &rate);
        if(!keepAfter(s, "valves ")) {
            assert(keepAfter(s, "valve "));
        }
        vs vecNext = split(s, ',');
        for (auto &it : vecNext) {
            it = trim(it);
        }
        vertRate[curr] = rate;
        vertNext[curr] = vecNext;
        vertId[curr] = nV++;
        nE += isz(vecNext);
        watch(curr, rate, vecNext);
    }
    vpii edges;
    vvi adj(nV);
    vi nonZeros = {vertId["AA"]};
    vi rate(nV);
    for (const auto &[u,r] : vertRate) {
        rate[vertId[u]] = r;
    }
    for (const auto &[u, next] : vertNext) {
        for (const auto &v : next) {
            edges.emplace_back(vertId[u], vertId[v]);
            adj[vertId[u]].push_back(vertId[v]);
        }
        if(vertRate[u] != 0)
            nonZeros.push_back(vertId[u]);
    }
    const int INF = (int)1e9;
    vvi dist(nV, vi(nV, INF));
    for (int s = 0; s < nV; s++) {
        vi visited(nV, false);
        vi queue = {s};
        visited[s] = 1;
        dist[s][s] = 0;
        for (int i = 0; i < isz(queue); i++) {
            for (int v : adj[queue[i]]) {
                if (!visited[v]) {
                    visited[v] = 1;
                    dist[s][v] = dist[s][queue[i]] + 1;
                    queue.push_back(v);
                }
            }
        }
    }
    for (int u : nonZeros) {
        for (int v : nonZeros) {
            std::cout << std::setw(4) << dist[u][v];
        }
        std::cout << std::endl;
    }
    vi have(isz(nonZeros));
    have[0] = 1;
    auto pointsNow = [&](){
        int sum = 0;
        for (int i = 0; i < isz(nonZeros); i++) {
            assert(0 <= i && i < isz(have));
            if (have[i]) {
                int u = nonZeros[i];
                assert(0 <= u && u < isz(rate));
                sum += rate[u];
            }
        }
        return sum;
    };
    std::map<std::tuple<int,vi,int>,int> cache;
    std::function<int(int,int)> dfs = [&](int currTime, int u) {
        // перебираем, какую вершину посетим следующей
        const auto key = std::make_tuple(currTime, have, u);
        auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }
        const int points = pointsNow();
        int res = currTime * points;
        for (int i = 0; i < isz(nonZeros); i++) {
            if (!have[i]) {
                const int v = nonZeros[i];
                const int delta = dist[u][v] + 1;
                int nextTime = currTime - delta;
                if (nextTime >= 0) {
                    have[i] = 1;
                    int nextRes = points * delta
                                + dfs(nextTime, v);
                    std::remax(res, nextRes);
                    have[i] = 0;
                }
            }
        }
        return cache[key] = res;
    };
    std::cout << dfs(30, nonZeros[0]) << std::endl;
}

template<typename A, typename B>
struct Closer {
    A a; B b;
    Closer(const A &open_, const B &close_) : a(open_), b(close_)
    {
        a();
    }
    ~Closer() {
        b();
    }
};

void part2() {
    std::string s;
    int nV{}, nE{};
    std::map<std::string, int> vertRate;
    std::map<std::string, int> vertId;
    std::map<std::string, vs> vertNext;
    while(std::getline(std::cin, s)) {
        s = trim(s);
        assert(keepAfter(s, "Valve "));
        std::string curr = s.substr(0, 2);
        assert(keepAfter(s, "rate="));
        int rate; sscanf(s.c_str(), "%d", &rate);
        if(!keepAfter(s, "valves ")) {
            assert(keepAfter(s, "valve "));
        }
        vs vecNext = split(s, ',');
        for (auto &it : vecNext) {
            it = trim(it);
        }
        vertRate[curr] = rate;
        vertNext[curr] = vecNext;
        vertId[curr] = nV++;
        nE += isz(vecNext);
        watch(curr, rate, vecNext);
    }
    vpii edges;
    vvi adj(nV);
    vi rate(nV);
    for (const auto &[u,r] : vertRate) {
        rate[vertId[u]] = r;
    }
    for (const auto &[u, next] : vertNext) {
        for (const auto &v : next) {
            edges.emplace_back(vertId[u], vertId[v]);
            adj[vertId[u]].push_back(vertId[v]);
        }
    }
    const int INF = (int)1e9;
    vvi dist(nV, vi(nV, INF));
    for (int s = 0; s < nV; s++) {
        vi visited(nV, false);
        vi queue = {s};
        visited[s] = 1;
        dist[s][s] = 0;
        for (int i = 0; i < isz(queue); i++) {
            for (int v : adj[queue[i]]) {
                if (!visited[v]) {
                    visited[v] = 1;
                    dist[s][v] = dist[s][queue[i]] + 1;
                    queue.push_back(v);
                }
            }
        }
    }
    vi have(nV);
    have[vertId["AA"]] = 1;
    auto pointsNow = [&](){
        int sum = 0;
        for (int i = 0; i < nV; i++) {
            assert(0 <= i && i < isz(have));
            if (have[i]) {
                assert(0 <= i && i < isz(rate));
                sum += rate[i];
            }
        }
        return sum;
    };
    //std::map<std::tuple<int,ll,int,int>,int> cache;
    //std::map<std::tuple<ll,int,int>,int> cache;
    //std::map<ll,int> cache;
    
    //std::map<ll,int> cache;
    std::map<int, std::string> id2name;
    for (const auto &[s,id] : vertId) {
        id2name[id] = s;
    }
    auto vec2mask = [&](const auto & vec) {
        ll res = 0;
        int p = 0;
        for (int i = 0; i < isz(vec); i++) {
            if (rate[i] > 0 && vec[i]) res |= (1LL << p);
            if (rate[i] > 0) p++;
        }
        return res;
    };
    int nonZero = 0;
    for (int i = 0; i < nV; i++) {
        if (rate[i] > 0) nonZero++;
    }
    const int pwNonZero = (1 << nonZero);
    std::vector<int16_t> cache(64*64*32LL*pwNonZero, -1);
    auto getKey = [&](int t, const vi &have, int u1, int u2) {
        //return std::make_tuple(t, vec2mask(have), u1, u2);
        return ((t*pwNonZero+vec2mask(have))*64+u1)*64+u2;
        /*ll res = t;
        res *= 32;
        res |= vec2mask(have);
        res *= pwNonZero;
        res |= u1;
        res *= 64;
        res |= u2;
        return res;*/
    };
    int64_t calls = 0;
    std::function<int(int,int,int)> dfs = [&](int currTime, int u1, int u2) -> int {
        // перебираем, какую вершину посетим следующей
        const auto key = getKey(currTime, have, u1, u2);
        /*auto it = cache.find(key);
        if (it != cache.end()) {
            return it->second;
        }*/
        if (cache[key] != -1) return cache[key];
        calls++;
        if (calls % (1 << 20) == 0) {
            std::cout << "calls = " << calls << std::endl;
        }
        int res = 0;
        if (currTime > 0) {
            const int points = pointsNow();
            // перебираем, что делаем мы:
            for (int i = 0; i <= isz(adj[u1]); i++) {
                for (int j = 0; j <= isz(adj[u2]); j++) {
                    if (i == isz(adj[u1]) && rate[u1] > 0 && !have[u1]) {
                        // мы открываем вентиль
                        Closer closer([&have,u1](){have[u1]=1;},
                                      [&have,u1](){have[u1]=0;});
                        if (j == isz(adj[u2]) && rate[u2] > 0 && !have[u2]) {
                            // слон открывает вентиль
                            Closer closer([&have,u2](){have[u2]=1;},
                                          [&have,u2](){have[u2]=0;});
                            int nextRes = points + dfs(currTime-1, u1, u2);
                            std::remax(res, nextRes);
                        } else {
                            if (j >= isz(adj[u2])) continue;
                            // слон перемещается
                            int u2next = adj[u2][j];
                            int nextRes = points + dfs(currTime-1, u1, u2next);
                            std::remax(res, nextRes);
                        }
                    } else {
                        if (i >= isz(adj[u1])) continue;
                        // мы перемещаемся
                        int u1next = adj[u1][i];
                        if (j == isz(adj[u2]) && rate[u2] > 0 && !have[u2]) {
                            // слон открывает вентиль
                            Closer closer([&have,u2](){have[u2]=1;},
                                          [&have,u2](){have[u2]=0;});
                            int nextRes = points + dfs(currTime-1, u1next, u2);
                            std::remax(res, nextRes);
                        } else {
                            if (j >= isz(adj[u2])) continue;
                            // слон перемещается
                            int u2next = adj[u2][j];
                            int nextRes = points + dfs(currTime-1, u1next, u2next);
                            std::remax(res, nextRes);
                        }
                    }
                }
            }
        }
        //watch(currTime, id2name[u1], id2name[u2]);
        cache[key] = res;
        return res;
    };
    std::cout << pointsNow() << std::endl;
    std::cout << dfs(26, vertId["AA"], vertId["AA"]) << std::endl;
}

int main() {
    part2();
}