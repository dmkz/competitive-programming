// tags: math, physics, geometry, O(1)
#include <bits/stdc++.h>
using namespace std;
using ld = long double;
// Высота - парабола (от времени)
// y(t) = A*t^2+B*t+C
// y(0) = 0 => A*0^2+B*0+C=0 => C = 0
// Скорость - производная от y(t):
// y'(t) = 2*A*t+B
// Пусть знаем начальную скорость V0 и угол alpha, тогда:
// V0x = V0 * sin(alpha) (проекция скорости на ось Oy)
// V0y = V0 * cos(alpha) (проекция скорости на ось Ox)
// y'(0) = V0y => B = V0y
// Производная от скорости - ускорение:
// y''(t) = 2 * A
// Оно равно -g [м/с^2]. Минус, т.к. направлено вниз
// => 2 * A = -g => A = -g / 2
// Получаем следующие уравнения:
// y(t) = (-g/2)*t^2+(V0*sin(alpha))*t
// x(t) = V0x * t = V0*cos(alpha)*t
// Из условия, знаем x(t) и y(t) при t = t2. Давайте найдём углы и V0:
// 1) V0*sin(alpha)*t = y+(g/2)*t^2
// 2) V0*cos(alpha)*t = x
// Поделив одно на другое, получим: alpha = atan((y+(g/2)*t2^2)/x)
// Выразим t через alpha из (2) и подставим в (1):
// t = x / (V0 * cos(alpha))
// x * tg(alpha) = y+(g/2)*(x^2/(V0^2*cos^2(alpha)))
// Знаем: tg(a)^2=sin^2/cos^2=(1-cos^2)/cos^2=1/cos^2-1=> 1/cos^2=tg(a)^2+1
// x * tg(alpha) = y+(g/2)*(x^2/V0^2)*(tg(a)^2+1)
// Теперь это квадратное уравнение относительно tg(a)
// A = (g/2)*(x^2/V0^2), B = -x, C = y + A
// Так как уже знаем один корень, можно использовать теорему Виета далее
const ld g = 9.81;
ld solve(int x, int y, int t2) {
// знаем один угол
    ld alpha2 = atan((y+(g/2)*t2*t2)/x);
// теперь можно найти скорость V0:
    ld V0 = x / (cos(alpha2)*t2);
    ld A = (g/2)*(x*x/(V0*V0));
    ld B = -x;
    ld sum_of_roots = B / (-A);
    ld alpha1 = atan(sum_of_roots - tan(alpha2));
    ld t1 = x / (V0 * cos(alpha1));
    return t1;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed << setprecision(4);
    int tt; cin >> tt;
    while (tt--) {
        int x, y, t2;
        cin >> x >> y >> t2;
        cout << solve(x,y,t2) << '\n';
    }
}