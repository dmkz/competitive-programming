#include <bits/stdc++.h>
using namespace std;
// предподсчёт всех простых чисел до корня из 10^9:
const int NMAX = (int)sqrt(1e9+100);
vector<int> primes;
void precalc() {
    // для разнообразия найдём все простые числа без решета Эратосфена: при проверке
    // очередного числа проверяем делится ли оно на уже найденные. Если не делится -> простое
    primes = {2,3,5,7};
    for (int x = 8; x <= NMAX; x++) {
        bool isPrime = true;
        for (int p : primes) {
            if (p * p > x) break;
            if (x % p == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) primes.push_back(x);
    }
}
// функция для факторизации заданного числа: находит список простых делителей числа
auto factor(int x) {
    vector<pair<int,int>> result; // пары (простое, его степень)
    for (int p : primes) {
        if (p * p > x) break; // факторизуем до корня. после корня делаем break
        if (x % p == 0) {
            result.push_back({p, 0});
            // делим пока делится
            do {
                x /= p;
                result.back().second++;
            } while (x % p == 0);
        }
    }
    // могло остаться простое больше корня:
    if (x > 1) result.push_back({x, 1});
    return result;
}
// функция для восстановления всех делителей, зная факторизацию:
auto divisors(const auto &primeDivisors) {
    vector<int> curr = {1};
    for (auto [p, k] : primeDivisors) {
        // у нас k+1 вариантов: взять p^i в делитель, 0 <= i <= k
        const int prevSize = (int)curr.size();
        // полуинтервал [0, prevSize-1) содержит все делители до рассмотрения p^k
        // мы должны умножить на p^i каждый из них, где 0 <= i <= k
        int mult = 1;
        for (int i = 1; i <= k; i++) {
            mult *= p;
            for (int j = 0; j < prevSize; j++)
                curr.push_back(curr[j] * mult);
        }
    }
    return curr;
}
void solve() {
    // читаем данные:
    int n; cin >> n;
    vector<int> a(n);
    for (auto &it : a) cin >> it;
    // факторизуем каждое число и для каждого делителя считаем сколько чисел оно делит:
    unordered_map<int, int> cnt; // обычный map<int,int> даёт TLE
    for (auto ai : a)
        for (auto d : divisors(factor(ai)))
            cnt[d]++;
    // находим максимальное число, которое делит два элемента массива:
    int answ = 1;
    for (const auto &[d,k] : cnt)
        if (k > 1)
            answ = max(answ, d);
    cout << answ << '\n';
}
main() {
    precalc(); // предподсчитываем все простые числа один раз
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
