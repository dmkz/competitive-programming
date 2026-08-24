#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем данные:
    ll n, m; cin >> n >> m;
    // находим их НОД: он содержит все общие простые делители
    ll g = gcd(n, m);
    // рассмотрим НОД как пересечение множества делителей. сокращаем наши числа так:
    // пока пересечение простых делителей не пусто, делим на это пересечение
    // таким образом, факторизация здесь не нужна
    for (ll common; (common = gcd(n, g)) > 1; n /= common);
    for (ll common; (common = gcd(m, g)) > 1; m /= common);
    // выводим ответ (через пробел, потому что так тоже можно):
    if (n > m) cout << "Nikita ";
    else if (n < m) cout << "Misha ";
    else cout << "Friendship ";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
