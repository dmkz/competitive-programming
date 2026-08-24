#include <bits/stdc++.h>
using namespace std;
// модульная арифметика:
const int mod = 998244353;
int sub(int a, int b) {
    return (a - b + mod) % mod;
}
int add(int a, int b) {
    return (a + b) % mod;
}
int mul(int a, int b) {
    return int(a * 1LL * b % mod);
}
// быстрое возведение в степень:
int binpow(int a, int64_t n) {
    int r = 1;
    while (n > 0) {
        if (n % 2 == 1)
            r = mul(r, a);
        a = mul(a, a);
        n >>= 1;
    }
    return r;
}
// сумма геометрической прогрессии:
int geom(int a, int64_t n) {
// 1 + a + ... + a^n = (a^{n+1} - 1) / (a - 1)
    if (n == 0) return 1;
    int p = sub(binpow(a, n+1), 1);
    int q = binpow(sub(a, 1), mod-2);
    return mul(p, q);
}
// функция находит список всех простых чисел <= NMAX:
vector<int> findPrimeNumbers(int NMAX) {
    if (NMAX < 2) NMAX = 2; // передан слишком маленький NMAX
    // строим решето Эратосфена за O(n log(log(n))):
    vector<bool> isPrime(NMAX+1, 1);
    isPrime[0] = isPrime[1] = 0;
    for (int i = 2; i * i <= NMAX; i++)
        if (isPrime[i])
            for (int j = i * i; j <= NMAX; j += i)
                isPrime[j] = 0;
    // возвращаем результат:
    vector<int> primes;
    for (int i = 2; i <= NMAX; i++)
        if (isPrime[i])
            primes.push_back(i);
    return primes;
}
// формула Лежандра считает, сколько раз n! делится на простое p
int64_t Legendre(int n, int p) {
    int64_t result = 0;
    while (n > 0) {
        n /= p;
        result += n;
    }
    return result;
}
// решение задачи:
void solve() {
    // читаем входные данные
    int n, m, k, r;
    cin >> n >> m >> k >> r;
    // находим простые числа до max(n, m):
    auto primes = findPrimeNumbers(max(n,m));
    // раскладываем каждый из факториалов на простые множители по формуле Лежандра
    int answ = 1;
    for (int p : primes) {
        // считаем степень вхождения p в число C(n,k) = n!/k!/(n-k)!:
        auto countInN = Legendre(n, p);
        countInN -= Legendre(k, p);
        countInN -= Legendre(n-k, p);
        // считаем степень вхождения p в число C(m,r) = m!/r!/(m-r)!:
        auto countInM = Legendre(m, p);
        countInM -= Legendre(r, p);
        countInM -= Legendre(m-r, p);
        // обновляем сумму делителей:
        answ = mul(answ, geom(p, min(countInN, countInM)));
    }
    cout << answ << '\n';
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
