#include <bits/stdc++.h>
#define int int64_t

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
const int NMAX = 100100;
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

using pii = std::pair<int,int>;
using vpii = std::vector<pii>;

vpii primeDivisors(int x) {
// раскладываем x на простые множители:
    vpii answ;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            int powI = 0;
            while (x % i == 0) x /= i, powI++;
            answ.emplace_back(i, powI);
        }
    }
    if (x > 1) answ.emplace_back(x, 1);
    return answ;
}

int32_t main() {
    int n, m;
    std::cin >> n >> m;
    // решаем задачу для каждого простого множителя отдельно:
    int answ = 1;
    for (auto [p,k] : primeDivisors(m)) {
        // число способов разложить k элементов в n коробок:
        (answ *= C(n+k-1,k)) %= mod;
    }
    std::cout << answ << std::endl;
    return 0;
}