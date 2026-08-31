#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    // читаем данные:
    ll a, b, c, x, y, z;
    cin >> a >> b >> c >> x >> y >> z;
    // применим бинарный поиск по ответу: по размеру сета роллов
    // функция проверки заданного размера сета роллов:
    auto check = [&](ll n){
        ll na = n / a;
        if (na < x) return false; // первый не наелся
        ll nb = n / b - n / (a * b);
        if (nb < y) return false; // второй не наелся
        ll nc = n / c - n / (b * c) - n / (a * c) + n / (a * b * c);
        return (nc >= z); // наелся ли третий
    };
    // ищем ответ на полуинтервале (0, 10^{18}]:
    ll low = 0, high = (ll)1e18;
    while (high - low > 1) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid;
    }
    cout << high << '\n';
}
main() {
    int tt = 1; cin >> tt;
    while (tt --> 0) solve();
}
