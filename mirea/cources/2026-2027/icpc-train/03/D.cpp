#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
// модульная арифметика:
const int mod = 998244353;
int mul(int a, int b) { return int((a * 1LL * b) % mod); }
int add(int a, int b) { return (a + b) % mod; }
int sub(int a, int b) { return ((a - b) % mod + mod) % mod; }
// быстрое возведение числа a в степень n:
int binpow(int a, int64_t n) {
    int res = 1;
    while (n > 0) {
        if (n % 2 == 1) res = mul(res, a);
        a = mul(a, a);
        n /= 2;
    }
    return res;
}
int sumgeom(int a, int64_t n) {
    // нужно посчитать 1 + a + a^2 + ... + a^{n-1} без делений
    if (n == 1) return 1;
    if (n == 2) return add(1, a);
    // n - число слагаемых. если оно чётно, то их можно разделить на слагаемые с чётными и нечётными
    // степенями, вынести a из второй скобки, и сгруппировать слагаемые:
    // 1 + a + a^2 + ... + a^{n-1} = (1 + a^2 + ...) + a * (1 + a^2 + ...) = (1 + a) * (1 + a^2 + ...)
    // количество слагаемых (значение n) уменьшается в два раза
    if (n % 2 == 0) return mul(add(1, a), sumgeom(mul(a,a),n/2));
    // иначе просто делаем количество слагаемых чётным, отделяя один множитель a:
    // 1 + a + a^2 + a^3 + ... = 1 + a * (1 + a + a^2 + ...)
    return add(1, mul(a, sumgeom(a, n-1)));
}
// решение задачи:
void solve() {
    // вероятность того, что i-я плитка (в 0-индексации) будет перекрашена в противоположный цвет:
    // p(i) = 1 - i^2 / n^2 - (n-i-1)^2 / n^2
    // это из-за того, что границы l и r выбираются равновероятно и независимо, то есть, нас устроит
    // только два исхода: когда обе границы левее i или обе границы правее i
    // вероятность того, что она будет иметь такой же цвет:
    // q(i) = 1 - p(i) = i^2 / n^2 + (n-i-1)^2 / n^2
    // математическое ожидание значения за одну операцию:
    // val[i] = p(i) * (1 - a[i]) + q(i) * a[i] => val[i] = p(i) + (q(i) - p(i)) * a[i]
    // то же самое: val[i] = p(i) + (1 - 2*p(i))*a[i] = K[i] * a[i] + B[i] <- линейная функция
    // за вторую операцию:
    // K[i]^2 * a[i] + K[i] * B[i] + B[i]
    // за третью операцию:
    // K[i]^3 * a[i] + B[i] * (1 + K[i] + K[i]^2)
    // теперь что будет через k ходов? за k-ю операцию:
    // K[i]^k * a[i] + B[i] * (1 + K[i] + ... + K[i]^(k-1)) = K[i]^k * a[i] + B[i] * (K[i]^k-1)/(K[i] - 1)
    // но лучше считать сумму геометрической прогрессии без деления - так надёжнее
    int n; int64_t k; cin >> n >> k;
    string s; cin >> s;
    int answ = 0;
    for (int i = 0; i < n; i++) {
        int ai = (s[i] - '0');
        // q(i) = i^2 / n^2 + (n-i-1)^2 / n^2
        int qi = mul(add(mul(i, i), mul(n-i-1,n-i-1)), binpow(mul(n,n),mod-2));
        // p(i) = 1 - q(i):
        int pi = sub(1, qi);
        // k(i) = 1 - 2*p(i)
        int ki = sub(1, mul(2, pi));
        // b(i) = p(i)
        int val = add(mul(binpow(ki, k), ai), mul(pi, sumgeom(ki, k)));
        answ = add(answ, val);
    }
    cout << answ << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int tt = 1; //cin >> tt;
    while (tt --> 0) solve();
    return 0;
}