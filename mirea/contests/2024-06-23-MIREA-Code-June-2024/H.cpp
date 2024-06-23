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
} // namespace SparseTable
} // namespace algos
#endif // __SPARSETABLE_HPP__

// Я решал через бинарный поиск и SparseTable, но можно и без них,
// если умеете использовать монотонный стек

// Сначала нужно выполнить все циклические сдвиги, а потом только удалять элементы
// Нам нужно найти минимальный возможный первый элемент. После того, как мы его
// поставим самым первым, то мы уже не имеем права делать циклические сдвиги, иначе
// наш лучший первый элемент перестанет быть первым.

// Вместо n сдвигов вправо мы могли сделать (n-1) удалений а потом 1 сдвиг. Иногда
// это выгодно (смотрите пример в условии на 20 элементов)

vi solveWithoutRotations(vi a, int k, int freeRemoves)
{
// a - сдвинутый массив, k - кол-во операций удаления, которые остались
// freeRemoves -- сколько элементов можем удалить бесплатно (замена сдвигов на удаления)
// элементы с индексами [1, 1 + freeRemoves - 1] можем удалять бесплатно
// элемент с индексом 0 стоит на своём месте
    int fp = 1 + freeRemoves; // первый платно удаляемый элемент

// добавляем элемент 0 в конец, чтобы было выгодно удалять элементы на суффиксе
// (если остались ещё дейтствия, мы можем удалять суффикс, чтобы стало 
// лексикографически меньше)
// пример: [1, 2] -> удаляем 2 -> [1] - лексикографически меньше чем [1, 2]

// Строим Sparse Table чтобы искать следующий минимум. Здесь можно использовать
// монотонный стек вместо это, что является проще и меньше памяти жрёт
    a.push_back(0);
    using namespace algos::SparseTable;
    SparseTable<int, Min<int>> st;
    st.build(a);
// начинаем удалять. т.к. удаления из вектора дорогие, мы будем запоминать, какие
// элементы удалены, а какие нет, и потом разом всё удалим
    vi del(isz(a)+1);
    int p = 1;
    while (p < isz(a))
    {
        // удалить можем 0 элементов, останется a[p]
        // 1 элемент, останется a[p+1]
        // 2 элемента, останется a[p+2]
        // k элементов, останется a[p+k]
        // надо выбрать минимум на отрезке [p ... p+k]
        // и поставить его пораньше за счёт удалений, чтобы стало
        // лексикографически меньше
        
        // запускаем бинпоиск чтобы найти следующий минимум на отрезке [p ... p+k]
        int right = std::max(fp+k, p+k);
        const int mn = st(p, right); // значение минимума
        // ищем его позицию (можно было предподсчитать)
        int low = p-1, high = right+1;
        bool was = 0;
        while (high - low > 1) {
            int mid = (low + high) / 2;
            was = 1;
            if (st(p, mid) == mn)
                high = mid;
            else
                low = mid;
        }
        if (!was)
            break;
        // нашли позицию минимума, его позиция равна high, все элементы от p до high
        // удаляются
        del[p]++;
        del[high]--;
        // останется элемент high. Вот сколько мы удалили:
        int removed = high - p;
        // вычесть бесплатные удаления:
        int L = std::max(p, 1);
        int R = std::min(fp-1, high - 1);
        int len = std::max(0, R - L + 1);
        // пересчитываем сколько платных удалений было:
        removed -= len;
        if (removed < 0)
            removed = 0;
        // уменьшаем кол-во доступных операций
        k -= removed;
        // переходим к следующему минимуму
        p = high + 1;
    }
    // удаляем элементы которые запомнили что нужно удалить
    for (int i = 1; i < isz(del); i++)
        del[i] += del[i-1];
    vi answ;
    for (int i = 0; i < isz(a); i++)
        if (del[i] == 0)
            answ << a[i];
    // удаляем нолик, который добавили в самом начале
    if (isz(answ) > 0 && answ.back() == 0)
        answ--;
    // выводим ответ
    return answ;
}
int main() {
    int tt; std::cin >> tt;
    while (tt --> 0) {
        // читаем данные
        int n, k;
        std::cin >> n >> k;
        vi a(n);
        std::cin >> a;
        // будем выбирать минимум из двух вариантов:
        // 1) вариант 'b' --- не используем сдвиги, только удаления
        // 2) вариант 'c' --- используем сдвиги, никаких удалений
        vi b = a, c = a;
        int bops = k, cops = k, freeSuffix = 0;
        // находим позиции элементов
        vi pos(n+1);
        for (int i = 0; i < n; i++)
            pos[a[i]] = i;
        // определяем, какой элемент мы можем поставить на первое место
        for (int first = 1; first <= n; first++) {
            int left = pos[first]; // вариант 1 - удаляем префикс
            int right = n - left; // вариант 2 - двигаем минимум циклически
            if (std::min(left, right) <= k) {
                // можно поставить этот элемент первым
                if (left <= k) {
                    // удаляем
                    b = a;
                    b.erase(b.begin(), b.begin()+left);
                    bops = k - left;
                }
                if (right <= k) {
                    // двигаем
                    // вот тут мы можем какие-то элементы бесплатно удалять
                    c = a;
                    std::rotate(c.begin(), c.begin()+left, c.end());
                    cops = k - right;
                    freeSuffix = right - 1;
                }
                break;
            }
        }
        // выбираем минимум из двух вариантов:
        b = solveWithoutRotations(b, bops, 0);
        c = solveWithoutRotations(c, cops, freeSuffix);
        if (b < a)
            a = b;
        if (c < a)
            a = c;
        for (auto it : a)
            std::cout << it << ' ';
        std::cout << '\n';
    }
}
