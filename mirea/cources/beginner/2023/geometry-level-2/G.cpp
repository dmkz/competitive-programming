#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld pi = acosl(ld(-1));
int main() {
    cout << fixed << setprecision(12);
    ld x1, y1, r1;
    ld x2, y2, r2;
    cin >> x1 >> y1 >> r1;
    cin >> x2 >> y2 >> r2;
    ld dx = x2 - x1;
    ld dy = y2 - y1;
    // не пересекаются:
    if (dx * dx + dy * dy >= (r1 + r2) * (r1 + r2)) {
        // расстояние между центрами превосходит сумму радиусов
        // (сравниваются квадраты расстояний, чтобы не потерять точность)
        // тогда ответ равен 0
        cout << 0 << endl;
        return 0;
    }
    // одна вложена в другую:
    // d + minR < maxR
    if (r1 > r2)
        swap(x1,x2), swap(y1,y2), swap(r1,r2);
    // теперь r1 <= r2
    ld d = hypot(dx,dy);
    if (d + r1 <= r2) {
        cout << pi * r1 * r1 << endl;
        return 0;
    }
    // общий случай:
    ld alpha = acosl((r1*r1-r2*r2-d*d)/(-2*r2*d));
    ld beta  = acosl((r2*r2-r1*r1-d*d)/(-2*r1*d));
    ld result = r1 * r1 * beta;
    result += r2 * r2 * alpha;
    result -= r1 * r1 * sinl(2*beta)/2;
    result -= r2 * r2 * sinl(2*alpha)/2;
    cout << result << endl;
}
