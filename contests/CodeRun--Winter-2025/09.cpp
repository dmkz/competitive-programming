#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
const int NMAX = (int)1e6;
using vi = std::vector<int>;
using pii = std::pair<int,int>;
using vpii = std::vector<pii>;
template<typename T> T sqr(T x) { return x * x; }

// список всех простых чисел через решето эратосфена:
const vi primes = [](){
    std::vector<bool> sieve(NMAX+1, true);
    sieve[0] = sieve[1] = false;
    for (int i = 2; i * i <= NMAX; i++)
        if (sieve[i])
            for (int j = i * i; j <= NMAX; j += i)
                sieve[j] = false;
    vi res;
    for (int i = 2; i <= NMAX; i++)
        if (sieve[i])
            res.push_back(i);
    return res;
}();
// порядковый номер простого числа:
const vi indexOfPrime = [](){
    vi res(1+NMAX);
    for (int i = 0; i < isz(primes); i++)
        res[primes[i]] = i;
    return res;
}();
// факторизация числа:
vpii factor(int x) {
    vpii res;
    for (int i = 0; i < isz(primes) && sqr(primes[i]) <= x; i++)
        if (int p = primes[i]; x % p == 0) {
            int cnt = 1;
            x /= p;
            while (x % p == 0) x /= p, cnt++;
            res.emplace_back(p, cnt);
        }
    if (x > 1)
        res.emplace_back(x, 1);
    return res;
}

// модульная арифметика:
const int mod = (int)1e9+7;
int mul(int a, int b) { return int(a * 1LL * b % mod); }
void mulby(int &a, int b) { a = mul(a, b); }

// решение:
void solve() {
    // читаем данные
    int n, k; std::cin >> n >> k;
    vi a(k); for (auto &it : a) std::cin >> it;
    // для каждого простого заведём счётчик его степеней (в разложении S):
    vi powers(isz(primes), 0);
    // вычитаем степени, полученные из знаменателя:
    for (auto ai : a)
        for (const auto &[p, t] : factor(ai))
            powers[indexOfPrime[p]] -= t;
    // прибавляем степени, полученные из факториала:
    for (auto p : primes)
        for (int currPower = 1; currPower <= n / p; ) {
            currPower *= p;
            powers[indexOfPrime[p]] += n / currPower;
        }
    // считаем количество делителей:
    int answ = 1;
    for (int pw : powers)
        mulby(answ, pw+1);
    std::cout << answ << std::endl;
}

main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt = 1; //std::cin >> tt;
    while (tt --> 0) solve();
}
