#pragma GCC optimize("Ofast")
#pragma GCC target("avx")
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
const int debug = 0;
// -----------------------------------------------------------------------------
namespace FastIO {
    struct Reader {
    private:
        FILE* file; std::vector<char> buffer; int pos; bool was;
        void read() {
            if (!buffer.empty()) {
                buffer.resize(fread(&buffer[0], 1, (int)buffer.size(), file)); pos = 0; 
            }
        }
    public:
        Reader(FILE* file_ = stdin, const int size_ = 1 << 16)
            : file(file_), buffer(size_, '\0'), pos(size_), was(true) { }
        operator bool() const { return was; }
        char getChar() {
            if (pos == (int)buffer.size()) { read(); }
            if (pos == (int)buffer.size()) { was = false; return EOF; } 
            else { was = true; return buffer[pos++]; }
        }
        std::string getStr() {
            char c = ' ';
            while (std::isspace(c)) { c = getChar(); }
            std::string answ;
            while (c != EOF && !std::isspace(c)) { answ.push_back(c); c = getChar(); }
            was = !answ.empty();
            return answ;
        }
        std::string getLine() {
            char c = '\n';
            while (c == '\n') { c = getChar(); }
            std::string answ;
            while (c != '\n' && c != EOF) { answ.push_back(c); c = getChar(); }
            was = !answ.empty();
            return answ;
        }
        template<typename T> T getInt() {
            char c = '?';
            while (!(c == '-' || ('0' <= c && c <= '9') || c == EOF)) { c = getChar(); }
            bool positive = true;
            if (c == '-') { positive = false; c = getChar(); }
            T answ(0);
            bool flag = false;
            while ('0' <= c && c <= '9') { flag = true; (answ *= 10) += (c - '0'); c = getChar(); }
            was = flag;
            return positive ? answ : -answ;
        }
        template<typename T> T getReal() {
            bool flag = false;
            char c = '?';
            while (!(c == '-' || ('0' <= c && c <= '9') || c == EOF)) { c = getChar(); }
            bool positive = (c != '-');
            if (c == '-') { c = getChar(); }
            long long first = 0;
            while ('0' <= c && c <= '9') { flag = true; (first *= 10) += (c - '0'); c = getChar(); }
            was = flag;
            if (c != '.') { return T(positive ? first : -first); }
            c = getChar();
            long long second = 0, pow = 1;
            while ('0' <= c && c <= '9') { (second *= 10) += (c - '0'); c = getChar(); pow *= 10; }
            T answ = first + (T)second / (T)pow;
            return positive ? answ : -answ;
        }
    };
    
    Reader& operator>>(Reader& reader, char& c) { return c = reader.getChar(), reader; }
    
    Reader& operator>>(Reader& reader, std::string& s) { return s = reader.getStr(), reader; }
    
    template<class T> typename std::enable_if<std::is_floating_point<T>::value, Reader&>::type
    operator>>(Reader& reader, T& t) { return t = reader.getReal<T>(), reader; }
    
    template<class T> typename std::enable_if<std::is_integral<T>::value, Reader&>::type
    operator>>(Reader& reader, T& t) { return t = reader.getInt<T>(), reader; }
    
    template<class T> Reader& operator>>(Reader& reader, std::vector<T>& vec) {
        for (auto &it : vec) { reader >> it; }
        return reader;
    }
    
    struct Writer {
    private:
        FILE* file; std::vector<char> buffer; int pos;
        int defaultPrecision, defaultWidth; char defaultFill;
    public:
        Writer(FILE* file_ = stdout, const int size_ = 1 << 16) 
            : file(file_), buffer(size_, '\0'), pos(0), defaultPrecision(6), defaultWidth(0), defaultFill(' ') { }
        ~Writer() { flush(); }
        void flush() { putChar(EOF); }
        void setprecision(int precision) { defaultPrecision = precision; }
        void setw(int width) { defaultWidth = width; }
        void setfill(char fill) { defaultFill = fill; }
        int getPrecision() const { return defaultPrecision; }
        int getWidth() const { return defaultWidth; }
        char getFill() const { return defaultFill; }
        void putChar(char c) {
            if (pos == (int)buffer.size() || c == EOF) { 
                fwrite(&buffer[0], 1, pos, file); pos = 0; 
            }
            if (c != EOF) { buffer[pos++] = c; }
        }
        void putStr(const std::string& s) { for (auto it : s) putChar(it); }
        template<typename T> void putInt(T value, int width = 0, char fill = ' ') {
            bool positive = !(value < 0);
            if (value < 0) { value = -value; }
            char buf[24]; int p = 0;
            do { buf[p++] = char(value % 10 + '0'); value /= 10; } while (value > 0);
            if (!positive) { buf[p++] = '-'; }
            while (p < width) buf[p++] = fill;
            while (p > 0) putChar(buf[--p]);
        }
        template<typename T> void putReal(T value, int precision = 6, int width = 0, char fill = ' ') {
            putInt((long long)value, width - precision - 1, fill);
            value = std::abs(value-(long long)value);
            if (precision == 0) { return; }
            putChar('.');
            #define PRINT_PART(cnt, pow) \
                while (precision >= cnt) { \
                    value *= pow; \
                    putInt((int)value, cnt, '0'); \
                    value -= (int)value; \
                    precision -= cnt; \
                }
            PRINT_PART(6,1000000)
            PRINT_PART(3,1000)
            PRINT_PART(1,10)
            #undef PRINT_PART
        }
    };
    
    Writer& operator<<(Writer& writer, const char c) { return writer.putChar(c), writer; }
    
    Writer& operator<<(Writer& writer, const std::string& s) { return writer.putStr(s), writer; }
    
    template<class T> typename std::enable_if<std::is_floating_point<T>::value, Writer&>::type
    operator<<(Writer& writer, const T& t) {
        writer.putReal(t, writer.getPrecision(), writer.getWidth(), writer.getFill());
        return writer; 
    }
    
    template<class T> typename std::enable_if<std::is_integral<T>::value, Writer&>::type
    operator<<(Writer& writer, const T& t) { 
        writer.putInt(t, writer.getWidth(), writer.getFill());
        return writer;
    }
}

int32_t main() {
    FastIO::Reader cin;
    FastIO::Writer cout;
    int nRows, nCols;
    cin >> nRows >> nCols;
    assert(3 <= nRows && nRows <= 2020);
    assert(3 <= nCols && nCols <= 2020);
    assert(9 <= nCols * nRows && nCols * nRows <= (int)4e6);
    // создаём битсеты, чтобы быстро пересекать множества
    // нам нужно находить первое различие. Это первая единица в ксоре:
    // Функция: (bitset1 ^ bitset2)._Find_first()
    std::vector<std::bitset<2020>> rowsDirect(nRows);
    auto rowsRevert = rowsDirect;
    std::vector<std::bitset<2020>> colsDirect(nCols);
    auto colsRevert = colsDirect;
    // читаем поле:
    for (int r = 0; r < nRows; r++) {
        for (int c = 0; c < nCols; c++) {
            int x; cin >> x;
            rowsDirect[r][c] = x;
            rowsRevert[r][nCols-1-c] = x;
            colsDirect[c][r] = x;
            colsRevert[c][nRows-1-r] = x;
        }
    }
    // находим ответ:
    using Tr = std::tuple<int,int,int>;
    auto answ = Tr{0,-1,-1};
    for (int r = 1; r + 1 < nRows; r++) {
        for (int c = 1; c + 1 < nCols; c++) {
            // пересекаем вниз и вправо:
            int right = ((rowsDirect[r] >> c) ^ (colsDirect[c] >> r))._Find_first();
            // пересекаем вверх и влево:
            int left = ((rowsRevert[r] >> (nCols-c-1)) ^ (colsRevert[c] >> (nRows-r-1)))._Find_first();
            // пересекаем вверх и вниз:
            int up = ((rowsDirect[r] >> c) ^ (rowsRevert[r] >> (nCols-c-1)))._Find_first();
            // обновляем ответ:
            int delta = std::min({up,left,right,c+1,r+1,nCols-c,nRows-r});
            std::remax(answ, Tr{delta,r,c});
        }
    }
    auto [len,r,c] = answ;
    r++,c++;
    cout << len-1 << ' ' << r << ' ' << c << "\n";
    return 0;
}