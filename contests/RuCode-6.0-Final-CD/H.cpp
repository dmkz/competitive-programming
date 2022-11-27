//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx,avx2,fma")
#include <bits/stdc++.h>

#define all(x) std::begin(x), std::end(x)
#define isz(x) (int)std::size(x)

// ---- ---- ---- ---- ---- ---- DEBUG LIBRARY ---- ---- ---- ---- ---- ----
const int debug = 0;
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

#define int ll
using ll = long long;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
void setmin(auto &x, const auto & y) {
    if (y < x) x = y;
}
using vvi = std::vector<vi>;
const vvi distTable = [](){
    vvi d(7,vi(7));
    d[1][2] = 2;
    d[1][3] = 3;
    d[1][4] = 1;
    d[1][5] = 5;
    d[1][6] = 5;
    d[2][3] = 5;
    d[2][4] = 3;
    d[2][5] = 3;
    d[2][6] = 5;
    d[3][4] = 2;
    d[3][5] = 4;
    d[3][6] = 2;
    d[4][5] = 6;
    d[4][6] = 4;
    d[5][6] = 2;
    for (int i = 1; i < isz(d); i++)
        for (int j = 1; j < i; j++)
            d[i][j] = d[j][i];
    return d;
}();

int getDist(int u, int v) {
    std::cout << "? " << u << ' ' << v << std::endl;
    int res/* = distTable[u][v]*/; std::cin >> res;
    return res;
}

vi ask(int from, int n) {
    vi dist(n+1);
    dist[from] = 0;
    for (int u = 1; u <= n; u++) {
        if (u != from) {
            dist[u] = getDist(from,u);
        }
    }
    return dist;
}

int32_t main() {
    int n, p, q;
    std::cin >> n >> p >> q;
    auto distFromP = ask(p,n);
    auto distFromQ = ask(q,n);
    std::vector<pii> cand = {{0,p}};
    for (int u = 1; u <= n; u++) {
        if (u == p || u == q) continue;
        if (distFromP[u] + distFromQ[u] == distFromQ[p]) {
            cand.push_back(pii(distFromP[u],u));
        }
    }
    cand.push_back(pii(distFromQ[p],q));
    std::sort(all(cand));
    watch(cand);
    int i = 0;
    std::vector<int> answ = {p};
    while (answ.back() != q) {
        int j, k;
        for (j = i; j < isz(cand) && cand[i].first == cand[j].first; j++);
        bool was = 0;
        watch(i,cand[i]);
        for (k = j; k < isz(cand); k++) {
            const auto [du, u] = cand[i];
            const auto [dv, v] = cand[k];
            int duv = getDist(u, v);
            watch(k,cand[k]);
            //watch(du,u);
            watch(u, dv,v, duv);
            watch(distFromQ[v]);
            watch(distFromQ[u]);
            if (duv + distFromQ[v] == distFromQ[u]) {
                i = k;
                answ.push_back(v);
                watch(answ);
                watch(i);
                was = 1;
                break;
            }
        }
        assert(was);
        //if(!was)break;
    }
    std::cout << "!";
    for (auto it : answ) std::cout << ' ' << it;
    std::cout << std::endl;
}