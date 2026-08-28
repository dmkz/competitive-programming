#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acosl(-1);
void solve() {
    // читаем данные:
    int x0, y0, xv, yv, xp, yp;
    cin >> x0 >> y0 >> xv >> yv >> xp >> yp;
    // переносим окружность в начало координат:
    xv -= x0, yv -= y0;
    xp -= x0, yp -= y0;
    // считаем полярный угол для Васи и Пети:
    ld a1 = atan2l(yv, xv);
    ld a2 = atan2l(yp, xp);
    // считаем минимальный угол между ними:
    if (a1 < a2) swap(a1, a2);
    ld minAngle = min(a1 - a2, a2 - a1 + 2 * pi);
    // находим ответ: делим длину дуги пополам, так как они двигаются навстречу друг другу
    ld R = hypot(xv, yv); // радиус окружности
    cout << R * minAngle / 2 << endl; // длина дуги
}
main() {
    cout << fixed << setprecision(12);
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt; cin >> tt;
    while (tt --> 0) solve();
}
