#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
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
#define int int64_t
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
void setmax(auto &x, const auto & y) {
    if (x < y) x = y;
}
void setmin(auto &x, const auto & y) {
    if (x > y) x = y;
}
class Timer {
    std::chrono::time_point<std::chrono::steady_clock> timePoint;
    size_t value;
public:
    void start() { timePoint = std::chrono::steady_clock::now(); }
    void finish() {
        auto curr = std::chrono::steady_clock::now();    
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(curr - timePoint);
        value = elapsed.count();
    }
    size_t operator()() const { return value; }
};
using ull = uint64_t;
const ull mod = (ull(1) << 61) - 1; // prime mod of hashing
std::mt19937 gen;
const int base = [](){
    std::uniform_int_distribution<int> dist((int)1.9e9, (int)2e9);
    int tmp = dist(gen);
    return tmp % 2 == 0 ? tmp - 1 : tmp;
}();
inline ull add(ull a, ull b) {
    // Calculate (a + b) % mod, 0 <= a < mod, 0 <= b < mod
    return (a += b) < mod ? a : a - mod;
}
    
inline ull sub(ull a, ull b) {
    // Calculate (a - b) % mod, 0 <= a < mod, 0 <= b < mod
    return (a -= b) < mod ? a : a + mod;
}

inline ull mul(ull a, ull b){
    // Calculate (a * b) % mod, 0 <= a < mod, 0 <= b < mod
    ull l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    ull l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
    ull ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret-1;
}

struct Figure {
    int64_t addToY{}, addToX{};
    std::map<int,std::set<int>> cntForY;
    uint64_t hash{0};
    bool operator==(const Figure & b) const {
        return cntForY == b.cntForY; // && hash == b.hash;
    }
    
    bool operator!=(const Figure & b) const {
        return !(*this == b);
    }
    
    Figure(const vpii& vec = {}, int64_t addToY_ = 0, int64_t addToX_ = 0)
        : addToY(addToY_), addToX(addToX_)
    {
        for (auto &it : vec)
            insert(it);
    }
    int bfs() const {
        watch("bfs");
        watch(cntForY);
        int startY = maxY() + 1 - addToY;
        std::vector<pii> q = {{startY, 0}};
        std::vector visited(startY + 1,
                            std::vector<bool>(7, false));
        visited[startY][0] = 1;
        watch(q);
        std::vector<int> minVisited(7, startY);
        for (int i = 0; i < isz(q); i++) {
            auto [y,x] = q[i];
            setmin(minVisited[x],y);
            watch(y,x);
            if (contains(y+addToY,x+addToX)) continue;
            for (int dy = -1; dy <= 0; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dy * dy + dx * dx == 1) {
                        int ny = y + dy;
                        int nx = x + dx;
                        if (ny < 0 || nx < 0 || nx > 6) continue;
                        watch(ny,nx);
                        if (!visited[ny][nx]) {
                            visited[ny][nx] = 1;
                            q.emplace_back(ny, nx);
                        }
                    }
                }
            }
        }
        watch(minVisited);
        return *std::min_element(all(minVisited));
    }
    void addX(int delta) {
        addToX += delta;
    }
    void addY(int delta) {
        addToY += delta;
    }
    void forEachPoint(const auto & func) const {
        for (const auto &[y, xx] : cntForY)
            for (const auto &x : xx)
                func(y + addToY, x + addToX);
    }
    void updateHash(auto val) {
        hash = add(mul(hash,base),val);
    }
    uint64_t calcHash() {
        hash = 0;
        forEachPoint([&](auto y, auto x){
            updateHash(y - addToY);
            updateHash(x - addToX);
        });
        return hash;
    }
    void insert(const Figure &other) {
        other.forEachPoint([&](auto y, auto x){
            insert(pii(y, x));
        });
        if (auto level = bfs()) {
            addToY += level;
            auto it = cntForY.find(level);
            std::map<int,std::set<int>> newMap;
            while (it != cntForY.end()) {
                newMap[it->first - level] = it->second;
                it++;
            }
            cntForY = newMap;
        }
    }
    void insert(pii p) {
        p.first -= addToY;
        p.second -= addToX;
        cntForY[p.first].insert(p.second);
        auto it = cntForY.find(p.first);
    }
    int64_t minY() const {
        return addToY + cntForY.begin()->first;
    }
    int64_t maxY() const {
        return addToY + cntForY.rbegin()->first;
    }
    bool contains(int y, int x) const {
        y -= addToY;
        x -= addToX;
        if (auto it = cntForY.find(y); it != cntForY.end()) {
            if (auto jt = it->second.find(x); jt != it->second.end()) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    bool intersects(const Figure &other) {
        bool flag = false;
        other.forEachPoint([&flag,this](auto y, auto x){
            if (x < 0 || x > 6) {
                flag = true;
            }
            if (this->contains(y,x))
                flag = true;
        });
        return flag;
    }
};
// ./a.exe 50455 
using vi = std::vector<int>;
void part1(const vi &steps) {
    std::vector<Figure> figures = {
        Figure({{0, 0},{0,1},{0,2},{0,3}}),
        Figure({{0, 1},{1,0},{1,1},{1,2},{2,1}}),
        Figure({{0, 0},{0,1},{0,2},{1,2},{2,2}}),
        Figure({{0, 0},{1,0},{2,0},{3,0}}),
        Figure({{0, 0},{1,0},{0,1},{1,1}})
    };
    Figure map({{0, 0},
                {0, 1},
                {0, 2},
                {0, 3},
                {0, 4},
                {0, 5},
                {0, 6}});
    
    std::string s; std::cin >> s;
    auto print = [](const Figure &a, const Figure &b){
        if(!debug) return;
        std::cout << std::endl;
        std::cout << std::endl;
        int minX = INT_MAX, minY = INT_MAX;
        int maxX = INT_MIN, maxY = INT_MIN;
        a.forEachPoint([&](auto y, auto x) {
            setmin(minX, x);
            setmin(minY, y);
            setmax(maxX, x);
            setmax(maxY, y);
        });
        b.forEachPoint([&](auto y, auto x) {
            setmin(minX, x);
            setmin(minY, y);
            setmax(maxX, x);
            setmax(maxY, y);
        });
        std::vector<std::string> ss(maxY+1-minY, std::string(maxX - minX + 1, '.'));
        a.forEachPoint([&](auto y, auto x) {
            if (y - minY < isz(ss))
                ss[y-minY][x-minX] = '#';
        });
        //ss.front() = "+" + std::string(7, '-') + "+";
        b.forEachPoint([&](auto y, auto x) {
            if (y - minY < isz(ss))
                ss[y-minY][x-minX] = '@';
        });
        std::reverse(all(ss));
        for (auto &t : ss)
            std::cout << t << std::endl;
    };
    using Key = std::tuple<int,int,uint64_t>;
    std::vector<std::pair<Key,int64_t>> keys;
    int pMove = 0, pFig = 0;
    bool wasFound = false;
    auto step = [&](int nSteps)
    {
        while (nSteps > 0)
        {
            // key = (pFig, pMove, map)
            auto key = std::make_tuple(pFig, pMove, map.calcHash());
            keys.emplace_back(key, map.maxY());
            for (int i = isz(keys)-2, period = 1;
                 i >= 0 && nSteps >= period;
                 i--, period++)
            {
                if (keys[i].first == key) {
                    auto deltaPeriod = keys.back().second - keys[i].second;
                    if (nSteps >= period) {
                        int div = nSteps / period;
                        nSteps -= period * div;
                        map.addY(deltaPeriod * div);
                    }
                    std::cout << "steps before period = " << isz(keys) - period << std::endl;
                    std::cout << " full period length = " << period << std::endl;
                    break;
                }
            }
            auto curr = figures[pFig];
            (++pFig)%=isz(figures);
            // находим самую высокую точку в диапазоне [0, 6] + прибавляем её
            curr.addY(map.maxY()+4);
            curr.addX(2);
            print(map,curr);
            while (true) {
                // двигаем вправо или влево:
                switch(s[pMove]) {
                    case '<': {
                        curr.addX(-1);
                        (++pMove)%=isz(s);
                        if (map.intersects(curr))
                            curr.addX(+1);
                        break;
                    }
                    case '>': {
                        curr.addX(+1);
                        (++pMove)%=isz(s);
                        if (map.intersects(curr))
                            curr.addX(-1);
                        break;
                    }
                    default: assert(false);
                };
                print(map,curr);
                curr.addY(-1);
                if (map.intersects(curr)) {
                    curr.addY(+1);
                    break;
                }
                print(map,curr);
            }
            map.insert(curr);
            nSteps--;
        }
    };
    Timer timer;
    std::vector<int> levels;
    std::vector<int> deltas;
    for (auto it : steps) {
        timer.start();
        std::cout << "steps   = " << it << std::endl;
        step(it);
        timer.finish();
        std::cout << "runtime = " << timer() << " ms" << std::endl;
        std::cout << "   maxY = " << map.maxY() << std::endl;
        std::cout << "  #rows = " << map.cntForY.size() << std::endl;
    }
}

int32_t main(int32_t argc, char *argv[]) {
//  1st task: ./a.exe 2022 < in.txt |& tee out-2.txt
//  2nd task: ./a.exe 1000000000000 < in.txt |& tee out-2.txt
    assert(argc == 2);
    const int nSteps = std::atoll(argv[1]);
    part1({nSteps});
}