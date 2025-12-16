#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
using pii = std::pair<int,int>;
using vi = std::vector<int>;
using vvi = std::vector<vi>;

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << '{';
    for (int i = 0; i < isz(v); i++) {
        if (i > 0) os << ",";
        os << v[i];
    }
    return os << '}';
}

struct DSU {
    vi par, sz;
    DSU(int n) : par(n), sz(n, 1)
    {
        for (int i = 0; i < n; i++)
            par[i] = i;
    }
    int getPar(int u) {
        return par[u] == u ? u : (par[u] = getPar(par[u]));
    }
    bool isConnected(int u, int v) {
        return getPar(u) == getPar(v);
    }
    void connect(int u, int v) {
        u = getPar(u), v = getPar(v);
        if (u == v) return;
        if (sz[u] < sz[v]) std::swap(u, v);
        sz[u] += sz[v];
        par[v] = u;
    }
};
// модульная арифметика:
const int mod = 998244353;
int &addto(int &a, int b) { return (a += b) >= mod ? (a -= mod) : a; }
int &subfrom(int &a, int b) { return (a -= b) < 0 ? (a += mod) : a; }
int mul(int a, int b) { return int(a * 1LL * b % mod); }
int sub(int a, int b) { return subfrom(a, b); }

// кол-во циклов если все ребра известны:
int numCycles(int n, const vi &a) {
    DSU dsu(n+1);
    for (int i = 1; i <= n; i++) {
        assert(a[i] != 0);
        dsu.connect(i, a[i]);
    }
    int res{};
    for (int i = 1; i <= n; i++)
        res += (dsu.par[i] == i);
    return res;
}

// Код для предподсчёта всех маленьких ответов:
template<bool debug = false>
int slow(int n, vi a, int l, int r) {
    static int lastN{-1};
    static vi lastA{};
    static vi count{};
    if (!(n == lastN && a == lastA)) {
        lastN = n, lastA = a;
        std::set<int> elems;
        for (int i = 1; i <= n; i++)
            elems.insert(i);
        vi pos;
        for (int i = 1; i < isz(a); i++)
            if (a[i] == 0) {
                pos.push_back(i);
            } else {
                elems.erase(a[i]);
            }
        vi perm(all(elems));
        count = {0};
        do {
            for (int i = 0; i < isz(pos); i++)
                a[pos[i]] = perm[i];
            int c = numCycles(n, a);
            while (c >= isz(count))
                count.push_back(0);
            addto(count[c], 1);
        } while (std::next_permutation(all(perm)));
        if (debug) {
            std::cout << "Num cycles: " << count << ", sum = ";        
        }
    }
    int answ{};
    for (int key = 0; key < isz(count); key++)
        if (l <= key && key <= r)
            addto(answ, count[key]);
    return answ;
}
// Результат предподсчёта (строки - кол-во незакрытых циклов,
// столбцы - требуемое кол-во циклов):
// n = 0: {1}, sum = 1
// n = 1: {0,    1}, sum = 1
// n = 2: {0,    1,     1}, sum = 2
// n = 3: {0,    2,     3,     1}, sum = 6
// n = 4: {0,    6,    11,     6,   1}, sum = 24
// n = 5: {0,   24,    50,    35,  10,     1}, sum = 120
// n = 6: {0,  120,   274,   225,  85,    15,   1}, sum = 720
// n = 7: {0,  720,  1764,  1624, 735,   175,  21,  1}, sum = 5040
// n = 8: {0, 5040, 13068, 13132, 6769, 1960, 322, 28, 1}, sum = 40320
// Формула: F(n, k) = F(n-1, k-1) + F(n-1, k) * (n-1)
// Предподсчитываем формулу + префикс-суммы:
const int NMAX = 3030;
const auto sf = [](){
    // предподсчёт значений функции f(n,k):
    std::vector<std::vector<int>> f(NMAX,{0});
    f[0] = {1};
    for (int n = 1; n < NMAX; n++) {
        f[n].resize(n+1, 1);
        for (int k = 1; k < n; k++)
            f[n][k] = int((f[n-1][k-1] + f[n-1][k] * (n-1LL)) % mod);
    }
    // префикс-суммы поверх массива:
    for (int n = 1; n < NMAX; n++)
        for (int k = 1; k < isz(f[n]); k++)
            addto(f[n][k], f[n][k-1]);
    return f;
}();
pii countGeneralCycles(int n, const vi &a) {
    DSU dsu(n+1);
    for (int i = 1; i <= n; i++)
        if (a[i] != 0)
            dsu.connect(i, a[i]);
    // получаем компоненты связности
    vvi items(1+n);
    vi edges(1+n);
    for (int i = 1; i <= n; i++) {
        int par = dsu.getPar(i);
        items[par].push_back(i);
        edges[par]+= (a[i]!=0);
    }
    int closed{}, opened{};
    for (int i = 1; i <= n; i++)
        if (dsu.par[i] == i) {
            if (isz(items[i]) > edges[i]) {
                opened++;
            } else {
                closed++;
            }
        }
    return {opened, closed};
}
int fast(int n, vi a, int l, int r) {
    // найти число ещё не закрытых циклов:
    auto [opened, closed] = countGeneralCycles(n, a);
    // есть уже closed циклов, которые не можем ни с кем соединять:
    l -= closed, r -= closed;
    if (r > opened) r = opened;
    if (r < l || r < 0) return 0;
    return sub(sf[opened][r], (l-1>=0?sf[opened][l-1]:0));
}
void stress() {
    for (int n = 1; n <= 10; n++) {
        vi a(n);
        for (int i = 1; i <= n; i++)
            a[i-1] = i;
        std::set<vi> examples;
        std::cout << "GENERATE " << n << std::endl;
        do {
            vi b(n+1, 0);
            for (int mask = 0; mask < (1 << n); mask++) {
                for (int i = 0; i < n; i++) {
                    if ((mask >> i) & 1) {
                        b[i+1] = a[i];
                    }
                }
                examples.insert(b);
            }
        } while (std::next_permutation(all(a)));
        std::cout << "TEST " << n << std::endl;
        for (const auto &aa : examples) {
            for (int l = 0; l <= n; l++) {
                for (int r = l; r <= n; r++) {
                    auto sl = slow(n, aa, l, r);
                    auto ft = fast(n, aa, l, r);
                    if (sl != ft) {
                        std::cout << "Wrong answer!" << std::endl;
                        std::cout << "n = " << n << ", a = {";
                        for (int i = 1; i <= n; i++) {
                            if (i > 1) std::cout << ",";
                            std::cout << a[i];
                        }
                        std::cout << "}" << std::endl;
                        std::cout << "l = " << l << ", r = " << r << std::endl;
                        std::cout << "sl = " << sl << std::endl;
                        std::cout << "ft = " << ft << std::endl;
                        std::exit(0);
                    }
                }
            }
        }
        std::cout << "n = " << n << ": OK" << std::endl;
    }
}
bool areAllDifferent(vi a) {
    const int n = isz(a);
    std::sort(all(a));
    a.erase(std::unique(all(a)), a.end());
    return isz(a) == n;
}
int sumN = 0, sumQ = 0;
int solve() {
    int n, q, l, r;
    std::cin >> n >> q >> l >> r;
    sumN += n, sumQ += q;
    //assert(sumN <= 3000);
    //assert(sumQ <= 3000);
    vi b(q), c(q), a(1+n);
    for (int i = 0; i < q; i++) std::cin >> b[i];
    for (int i = 0; i < q; i++) std::cin >> c[i];
    // все b и c должны быть различными
    if (!areAllDifferent(b) || !areAllDifferent(c))
        return 0;
    for (int i = 0; i < q; i++)
        a[b[i]] = c[i];
    return fast(n, a, l, r);
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0)
        std::cout << solve() << std::endl;
}
