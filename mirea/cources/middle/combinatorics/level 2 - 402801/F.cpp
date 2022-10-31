#include <bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define isz(x) (int)(x).size()
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
const int NMAX = 300300;
const int mod = 998244353;

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

int32_t main() {
    int n; std::cin >> n;
    std::vector<int> a(2*n);
    for (auto &it : a) std::cin >> it;
    std::sort(all(a));
    /*
    // Исследование:
    int64_t answ = 0;
    std::map<std::string, int> count;
    int64_t sumOne = 0, cntSums = 0;
    for (int mask = 0; mask < (1 << isz(a)); mask++) {
        if (__builtin_popcount(mask) != n) continue;
        std::vector<int> p, q;
        for (int i = 0; i < isz(a); i++) {
            if ((mask >> i) & 1) {
                p.push_back(a[i]);
            } else {
                q.push_back(a[i]);
            }
        }
        std::sort(all(p));
        std::sort(all(q), std::greater<>());
        auto x = p;
        auto y = q;
        assert(isz(p) == n);
        assert(isz(q) == n);
        // x отсортирован по возрастанию
        // y отсортирован по убыванию
        // x0 <= x1 <= x2 <= ... <= xi <= ... <=
        // x0 <= x1 <= x2 <= ... <= xi <= ... <=
        int64_t curr = 0;
        for (int i = 0; i < n; i++) {
            if (x[i] >= y[i]) {
                count[std::to_string(x[i]) + " - " + std::to_string(y[i])]++;
            } else {
                count[std::to_string(y[i]) + " - " + std::to_string(x[i])]++;
            }
            curr += std::abs(x[i] - y[i]);
        }
        answ += curr;
        //std::cout << "curr = " << curr << std::endl;
        sumOne = curr;
        cntSums++;
    }
    answ %= mod;
    if (answ < 0) answ += mod;
    std::cout << answ << std::endl;
    std::cout << "sumOne = " << sumOne << std::endl;
    std::cout << "cntSums = " << cntSums << std::endl;
    std::cout << "Items:";
    for (auto it : a) std::cout << ' ' << it;
    std::cout << std::endl;
    std::map<int, std::vector<std::string>> byCnt;
    for (const auto &[what,cnt] : count) {
        std::cout << what << " " << cnt << std::endl;
        byCnt[cnt].push_back(what);
    }
    for (const auto &[cnt, vec] : byCnt) {
        assert(cnt % 2 == 0);
        std::cout << "cnt = " << cnt / 2 << std::endl;
        for (auto &it : vec) {
            std::cout << "\t" << it << std::endl;
        }
    }
    */
    /*
        Результаты исследования:
        1. Суммы модулей для каждого разбиения равны между собой
        2. Количество разбиений C(2*n, n)
        Решение: берём сумму одного разбиения и умножаем её на C(2*n, n)
    */
    int64_t sum = 0;
    for (int i = 0, j = 2 * n - 1; i < n; i++, j--) {
        sum += a[j] - a[i];
    }
    sum %= mod;
    if (sum < 0) sum += mod;
    std::cout << sum*C(2*n,n)%mod << std::endl;
    return 0;
}