#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using namespace std;
using ll = long long;
// функция находит список всех простых чисел <= NMAX:
vector<int> findPrimeNumbers(int NMAX) {
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
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    // читаем входные данные
    int q; ll L, R;
    cin >> q >> L >> R;
    // находим простые до миллиона:
    auto primes = findPrimeNumbers(1 << 20);
    // вычеркиваем числа на отрезке [L, R], которые делятся на простые:
    vector<bool> isPrime(R-L+1, 1);
    // вычеркнем 0 и 1:
    if (0 >= L) isPrime[0-L] = 0;
    if (1 >= L) isPrime[1-L] = 0;
    // вычеркнем все остальные составные числа на отрезке [L, R]:
    for (int p : primes) {
        // очень важно начать вычёркивать с 2 * p, то есть случайно не вычеркнуть само p.
        // оптимально начать p^2 и до конца с шагом p, но можно и с 2 * p:
        const ll low = max<ll>(p, (L + p - 1) / p);
        const ll high = R / p;
        for (ll i = low; i <= high; i++)
            isPrime[i * p - L] = 0;
    }
    // строим префиксные суммы:
    vector<ll> sums = {0};
    for (int i = 0; i < isz(isPrime); i++)
        sums.push_back(sums.back() + (isPrime[i] ? L + i : 0));
    // читаем запросы:
    vector<ll> left(q), right(q);
    for (auto &it : left) cin >> it;
    for (auto &it : right) cin >> it;
    // отвечаем на них:
    for (int i = 0; i < q; i++)
        cout << sums[right[i]+1 - L] - sums[left[i] - L] << ' ';
    cout << '\n';
}
