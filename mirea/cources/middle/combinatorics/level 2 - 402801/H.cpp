#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
#define int int64_t

using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;

// быстрое возведение в степень:
int binpow(int a, int n, int mod) {
    int res = 1 % mod;
    while (n > 0) {
        if (n % 2 == 1)
            res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

// Комбинаторика: факториалы, обратные к ним и биномиальные коэффициенты
const int NMAX = (int)2e6;
const int mod = (int)1e9+7;

int fact[NMAX], ifact[NMAX];

const int precalculated = [](){
    // считаем факториалы:
    fact[0] = 1;
    for (int i = 1; i < NMAX; i++)
        fact[i] = fact[i-1] * i % mod;
    // считаем обратные факториалы:
    ifact[NMAX-1] = binpow(fact[NMAX-1], mod-2, mod);
    for (int i = NMAX-2; i >= 0; i--) {
        ifact[i] = ifact[i+1] * (i+1) % mod;
    }
    return true;
}();

int C(int n, int k) {
    if (k < 0 || n < 0 || k > n) return 0;
    int answ = fact[n];
    (answ *= ifact[n-k]) %= mod;
    (answ *= ifact[k]) %= mod;
    return answ;
}

// предподсчитываем для каждого числа минимальный простой делитель
const vi firstDiv = [](){
    vi res(NMAX);
    for (int x = 2; x < NMAX; x++)
        if (!res[x]) {
            for (int y = x; y < NMAX; y += x)
                if (!res[y])
                    res[y] = x;
        }
    return res;
}();


vpii primeDivisors(int x) {
// раскладываем x на простые множители:
    vpii answ;
    while (x > 1) {
        int p = firstDiv[x];
        x /= p;
        if (!isz(answ) || answ.back().first != p)
            answ.emplace_back(p, 0);
        answ.back().second++;
    }
    return answ;
}

int getSumEvenC(int n) {
// C(n, 0) + C(n, 2) + C(n, 4) + ...
// 1             : 1
// 1 1           : 1
// 1 2 1         : 2
// 1 3 3 1       : 4
// 1 4 6 4 1     : 8
// 1 5 10 10 5 1 : 16
    if (n == 0) return 1;
    return binpow(2, n-1, mod);
}

int32_t main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int q; std::cin >> q;
    while (q--) {
        int m, n;
        std::cin >> m >> n;
        // решаем задачу для каждого простого множителя отдельно:
        int answ = 1;
        for (auto [p,k] : primeDivisors(m)) {
            // число способов разложить k элементов в n коробок:
            (answ *= C(n+k-1,k)) %= mod;
        }
        // и расставляем знаки - парами
        (answ *= getSumEvenC(n)) %= mod;
        std::cout << answ << "\n";
    }
    return 0;
}