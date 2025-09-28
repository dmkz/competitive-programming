#include <bits/stdc++.h>
#define isz(x) (int)(x).size()
using ll = long long;
/*
    Изначально предполагалось решение, в котором нужно использовать обычную
    факторизацию (идти до корня из x и искать делители), но когда контест
    начался, то выяснилось, что одно число 10^{15} не то же самое, что
    1000 чисел порядка 10^{12}. Причём самые каверзные тесты:
    1) все 1000 чисел - простые;
    2) все 1000 чисел - квадраты простых чисел.
    Поэтому решение, удовлетворяющее ограничениям, следующее:
    - Найдём все простые числа до sqrt(10^{15}) решетом эратосфена
    - При факторизации будем использовать только найденные простые числа
    - Не забываем идти до sqrt(x) при факторизации
    
    Оценка асимптотики:
    1) все простые находятся за ~~линейное время O(sqrt(10^15))
    2) факторизация одного числа выполняется за O(sqrt(x) / log(sqrt(x))),
       так как на отрезке от 2 до n простых чисел примерно n / log(n)
*/

const auto primes = []() {
    // решето Эратосфена для поиска простых чисел
    std::vector<bool> isComposite((ll)(sqrt(1e15L)+10));
    for (int i = 2; i * i <= isz(isComposite); i++)
        if (!isComposite[i])
            for (int j = i * i; j <= isz(isComposite); j+=i)
                isComposite[j] = true;
    std::vector<int> result;
    for (int x = 2; x < isz(isComposite); x++)
        if (!isComposite[x])
            result.push_back(x);
    return result;
}();

void solve() {
    ll x; std::cin >> x;
    std::vector<ll> answ;
    for (int p : primes) {
        // выход если вышли за пределы sqrt(x):
        if (p * 1LL * p > x)
            break;
        // делим на p пока делится:
        while (x > 1 && x % p == 0) {
            answ.push_back(p);
            x /= p;
        }
    }
    if (x > 1)
        answ.push_back(x);
    assert(std::is_sorted(answ.begin(), answ.end()));
    std::cout << answ.size() << "\n";
    for (auto pi : answ)
        std::cout << pi << ' ';
    std::cout << '\n';
}
main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int tt; std::cin >> tt;
    while (tt --> 0) solve();
}
