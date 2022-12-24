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
const int debug = 0;
// -----------------------------------------------------------------------------
using vs = std::vector<std::string>;
const int up = 0, down = 2, left = 1, right = 3;
using pii = std::pair<int, int>;
using vpii = std::vector<pii>;
const std::vector<pii> steps = {{-1,0},{0,-1},{+1,0},{0,+1}};
int main() {
    //const int limit = 10;
    const int limit = 10000;
    std::string s;
    std::vector<vs> arr(1);
    std::set<int> cols;
    while(std::getline(std::cin, s)) {
        while (isz(s) && std::isspace(s.back())) s.pop_back();
        arr.back().push_back(s);
        cols << isz(s);
    }
    watch("readed");
    const int nCols = *cols.begin();    
    const int nRows = isz(arr[0]);
    vpii wL,wR,wU,wD;
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            if (arr[0][r][c] == '<')      { wL << pii(r,c); arr[0][r][c] = '#'; }
            else if (arr[0][r][c] == '>') { wR << pii(r,c); arr[0][r][c] = '#'; }
            else if (arr[0][r][c] == '^') { wU << pii(r,c); arr[0][r][c] = '#'; }
            else if (arr[0][r][c] == 'v') { wD << pii(r,c); arr[0][r][c] = '#'; }
            else if (!(arr[0][r][c] == '.' || arr[0][r][c] == '#')) {
                std::cout << "unknown char at " << r << "  " << c << ": " << arr[0][r][c] << std::endl;
            }
        }
    }
    watch(wU);
    watch(wL);
    watch(wD);
    watch(wR);
    pii start = {0, (int)arr[0][0].find('.')};
    pii finish = {nRows-1, (int)arr[0].back().find('.')};
    int t = 0;
    for (int round = 0; round < 3; round++, std::swap(start,finish))
    {
        vpii curr={{start}}, next;
        for (; !std::binary_search(all(curr),finish) && t < limit; t++) {
            auto paint = [&](){
                if (!debug) return;
                std::cout << std::string(40,'-') << std::endl;
                std::cout << "situation at time = " << t+1 << std::endl;
                watch(wU);
                watch(wL);
                watch(wD);
                watch(wR);
                auto a = arr.back();
                for (const auto &[r,c] : wU) a[r][c] = '^';
                for (const auto &[r,c] : wD) a[r][c] = 'v';
                for (const auto &[r,c] : wL) a[r][c] = '<';
                for (const auto &[r,c] : wR) a[r][c] = '>';
                for (const auto &[r,c] : curr) a[r][c] = 'X';
                for (auto &it : a) std::cout << it << '\n';
            };
            // modeling map of next winds
            // copy arr from previous second:
            arr.push_back(arr.back());
            // remove old winds, which are painted as walls:
            for (auto winds : {&wU,&wL,&wD,&wR}) {
                for (const auto &[r,c] : *winds) {
                    arr.back()[r][c] = '.';
                }
            }
            // move all winds:
            int currDir = up;
            for (auto winds : {&wU,&wL,&wD,&wR}) {
                for (auto &[r,c] : *winds) {
                    int nr = r + steps[currDir].first;
                    int nc = c + steps[currDir].second;
                    if (arr.back()[nr][nc] == '#') {
                        int oppositeDir = (currDir+2)%4;
                        do {
                            nr += steps[oppositeDir].first;
                            nc += steps[oppositeDir].second;
                        } while (arr.back()[nr][nc] == '.');
                        r = nr + steps[currDir].first;
                        c = nc + steps[currDir].second;
                    } else {
                        r = nr;
                        c = nc;
                    }
                }
                currDir++;
            }
            // paint winds as walls:
            for (auto winds : {&wU,&wL,&wD,&wR}) {
                for (const auto &[r,c] : *winds) {
                    arr.back()[r][c] = '#';
                }
            }
            // see all positions at current second
            for (const auto &[r, c] : curr) {
                // move:
                for (int dir = 0; dir < 4; dir++) {
                    const int nr = r + steps[dir].first;
                    const int nc = c + steps[dir].second;
                    if (nr < 0 || nr >= nRows) continue;
                    if (nc < 0 || nc >= nCols) continue;
                    if (arr.back()[nr][nc] == '#') continue;
                    next.push_back({nr, nc});
                }
                // stay here:
                if (arr.back()[r][c] == '.') {
                    next.push_back({r,c});
                }
            }
            curr = next;
            next.clear();
            std::sort(all(curr));
            std::reuniq(curr);
            paint();
        }
        std::cout << "round #" << round << " have been finished at t = " << t << std::endl;
    }
}

