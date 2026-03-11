// геометрия, плошадь сектора, пересечение двух кругов
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const ld pi = acos(-1.0L);
main() {
    cout << fixed << setprecision(12);
    ll x1, y1, r1, x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    ll dx = x1 - x2, dy = y1 - y2;
    // если слишком далеко, то пересечения нет:
    if (dx * dx + dy * dy >= (r1 + r2) * (r1 + r2)) {
        cout << "0\n";
        return 0;
    }
    if (r1 < r2) {
        swap(x1, x2);
        swap(y1, y2);
        swap(r1, r2);
    }
    // если один круг вложен в другой:
    // dist + r2 <= r1 => dist <= r1 - r2
    if (dx * dx + dy * dy <= (r1 - r2) * (r1 - r2)) {
        cout << pi * r2 * r2 << "\n";
        return 0;
    }
    ld d = sqrtl(dx * dx + dy * dy);
    // находим углы из теоремы косинусов:
    // r2^2 = r1^2 + d^2 - 2*r1*d*cos(a1)
    ld a1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
    ld a2 = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
    // находим высоты:
    ld h1 = r1 * cos(a1);
    ld h2 = r2 * cos(a2);
    // находим площадь секторов:
    ld s1 = a1 * r1 * r1;
    ld s2 = a2 * r2 * r2;
    // находим площадь треугольников:
    ld t1 = h1 * r1 * sinl(a1);
    ld t2 = h2 * r2 * sinl(a2);
    // выводим ответ:
    cout << s1 + s2 - t1 - t2 << endl;
}
