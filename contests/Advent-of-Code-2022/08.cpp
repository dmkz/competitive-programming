#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
// ---- ---- ---- ---- ---- ---- DEBUG LIBRARY ---- ---- ---- ---- ---- ----
const int debug = 1;
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
using vi = std::vector<int>;
using vvi = std::vector<vi>;
vi s2v(auto s) {
    vi answ;
    for (auto it : s)
        answ.push_back(it-'0');
    return answ;
}

int task1(const vvi &a) {
    int n = isz(a), m = isz(a[0]), answ{};
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            bool ok = false;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr * dr + dc * dc == 1) {
                        int nr = r+dr, nc = c+dc;
                        bool visible = true;
                        while (0 <= nr && nr < n && 0 <= nc && nc < m) {
                            visible &= (a[nr][nc] < a[r][c]);
                            nr += dr;
                            nc += dc;
                        }
                        watch(r,c,dr,dc,visible);
                        ok |= visible;
                    }
                }
            }
            answ += ok;
        }
    }
    return answ;
}
int task2(const vvi &a) {
    int n = isz(a), m = isz(a[0]), answ{};
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int curr = 1;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    if (dr * dr + dc * dc == 1) {
                        int nr = r+dr, nc = c+dc, currDir = 0;
                        while (0 <= nr && nr < n && 0 <= nc && nc < m &&
                               a[nr][nc] < a[r][c]) currDir++, nr += dr, nc += dc;
                        if (0 <= nr && nr < n && 0 <= nc && nc < m)
                            currDir++;
                        curr *= currDir;
                        watch(r,c,dr,dc,currDir);
                    }
                }
            }
            if (answ < curr) answ = curr;
        }
    }
    return answ;
}
int main() {
    std::string s;
    vvi a;
    while(std::cin >> s) {
        a.push_back(s2v(s));
    }
    std::cout << task2(a) << std::endl;
}