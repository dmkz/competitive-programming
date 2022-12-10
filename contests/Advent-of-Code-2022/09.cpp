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
template<typename A, typename B> bool operator >(const A& a, const B& b) { return b < a; }
template<typename A, typename B> bool operator<=(const A& a, const B& b) { return !(a > b); }
template<typename A, typename B> bool operator>=(const A& a, const B& b) { return !(a < b); }
template<typename A, typename B> bool operator!=(const A& a, const B& b) { return a < b || b < a; }
template<typename A, typename B> bool operator==(const A& a, const B& b) { return !(a != b); }
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
const int debug = 0;
// -----------------------------------------------------------------------------
void task1() {
    pii head, tail, prevHead;
    std::set<pii> visited = {tail};
    char dir; int cnt;
    while(std::cin >> dir >> cnt) {
        while(cnt--) {
            prevHead = head;
            switch(dir) {
                case 'R': head.second++; break;
                case 'L': head.second--; break;
                case 'U': head.first--; break;
                case 'D': head.first++; break;
                default: assert(false);
            };
            bool neighbour = false;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    auto[r,c]=tail;
                    r+=dr;
                    c+=dc;
                    if(pii(r,c) == head) {
                        neighbour = true;
                        break;
                    }
                }
            }
            if(!neighbour) {
                visited.insert(tail = prevHead);
            }
        }
    }
    std::cout << isz(visited) << std::endl;
}

void paint(const auto &rope, int minRow, int minCol, int maxRow, int maxCol) {
    std::vector a(maxRow - minRow + 1, std::string(maxCol - minCol + 1, '.'));
    int deltaRow = -minRow, deltaCol = -minCol;
    for (int i = 0; i < isz(rope); i++) {
        auto [r,c] = rope[i];
        r += deltaRow;
        c += deltaCol;
        if (a[r][c] == '.') {
            a[r][c] = (i == 0 ? 'H' : char('0'+i));
        }
    }
    std::cout << std::string(maxCol - minCol + 1, '-') << std::endl;
    for (auto &s : a)
        std::cout << s << std::endl;
    std::cout << std::string(maxCol - minCol + 1, '-') << std::endl;
}

auto getBounders(const auto &moves) {
    int row{}, col{};
    int maxRow{}, maxCol{}, minRow{},minCol{};
    for (auto [dir,cnt] : moves) {
        switch(dir) {
            case 'R': col+=cnt; break;
            case 'L': col-=cnt; break;
            case 'U': row-=cnt; break;
            case 'D': row+=cnt; break;
            default: assert(false);
        };
        std::remax(maxRow,row);
        std::remax(maxCol,col);
        std::remin(minRow,row);
        std::remin(minCol,col);
    }
    return std::make_tuple(minRow,minCol,maxRow,maxCol);
}

int dist(pii from, pii to) {
    auto [r1,c1]=from;
    auto [r2,c2]=to;
    return std::abs(r1-r2) + std::abs(c1-c2);
}

void task2() {
    std::vector<pii> rope(10);
    std::set<pii> visited = {rope[0]};
    std::vector<std::pair<char,int>> moves;
    {
        char dir; int cnt;
        while(std::cin >> dir >> cnt) {
            moves.emplace_back(dir,cnt);
        }
    }
    auto [minRow,minCol,maxRow,maxCol] = getBounders(moves);
    for (auto [dir,cnt] : moves) {
        while(cnt--) {
            for (int i = 1; i < 10; i++) {
                // move head:
                if (i == 1) {
                    auto &head = rope[i-1];
                    switch(dir) {
                        case 'R': head.second++; break;
                        case 'L': head.second--; break;
                        case 'U': head.first--; break;
                        case 'D': head.first++; break;
                        default: assert(false);
                    };
                }
                // rope[i-1] is already moved
                bool neighbour = false;
                auto nearest = std::make_pair(10, pii{});
                for (int dr = -1; dr <= 1; dr++) {
                    for (int dc = -1; dc <= 1; dc++) {
                        auto[r,c] = rope[i];
                        r+=dr;
                        c+=dc;
                        auto pos = pii(r,c);
                        if(pos == rope[i-1]) {
                            neighbour = true;
                        }
                        int delta = dist(pos, rope[i-1]);
                        std::remin(nearest, std::make_pair(delta,pos));
                    }
                }
                if(!neighbour) {
                    rope[i] = nearest.second;
                } else {
                    break;
                }
            }
            visited.insert(rope.back());
            //paint(rope,minRow,minCol,maxRow,maxCol);
        }
    }
    std::cout << isz(visited) << std::endl;
}
int main() {
    task2();
}