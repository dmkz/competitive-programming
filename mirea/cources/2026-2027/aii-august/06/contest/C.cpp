#include <bits/stdc++.h>
using namespace std;
using ll = long long;
void solve() {
    ll x0, y0, r;
    cin >> x0 >> y0 >> r;
    // переносим окружность в (0, 0), т.е. просто игнорируем координаты центра
    // далее идём вдоль левой полуплоскости и для каждого x находим границы столбца
    // [yMin+1, yMax-1], который целиком влезает в окружность. Прибавляем его высоту.
    // Используем два указателя, чтобы эффективно переходить от "x" к "(x-1)".
    ll yMax = 0, yMin = 0, answ = 0;
    for (ll x = -r; x < 0; x++) {
        while (x*x+yMax*yMax <= r*r) yMax++;
        while (x*x+yMin*yMin <= r*r) yMin--;
        answ += max<ll>(0, yMax - yMin - 2);
    }
    cout << answ * 2 << "\n";
}
main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
