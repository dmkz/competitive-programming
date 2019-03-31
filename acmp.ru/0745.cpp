/*
    Задача: 745. Карта
    
    Решение: геометрия, двумерный тернарный поиск, O(log(1/EPS)^2)
    
    Автор: Дмитрий Козырев, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <bits/stdc++.h>
typedef long double ld;
int main() {
    std::cout << std::setprecision(6) << std::fixed;
    ld w, h, cx, cy, a, b;
    std::cin >> w >> h >> cx >> cy >> a >> b;
    a /= 100;
    b /= 100;
    auto calc = [&](ld x, ld y) {
        ld mx = x / w * a + cx;
        ld my = y / h * b + cy;
        return (mx - x) * (mx - x) + (my - y) * (my - y);
    };
    auto search_x = [&](ld y, ld& x) {
        ld x1 = -w, x2 = w;
        for (int i = 0; i < 100; ++i) {
            ld l = (6 * x1 + 5 * x2) / 11;
            ld r = (5 * x1 + 6 * x2) / 11;
            ld dl = calc(l, y);
            ld dr = calc(r, y);
            if (dl <= dr) { x2 = r; } 
            else { x1 = l; }
        }
        x = (x1+x2)/2;
        return calc(x,y);
    };
    auto search_y = [&](ld &x, ld &y) {
        ld y1 = -h, y2 = h;
        for (int i = 0; i < 100; ++i) {
            ld l = (6 * y1 + 5 * y2) / 11;
            ld r = (5 * y1 + 6 * y2) / 11;
            ld xl, dl, xr, dr;
            dl = search_x(l, xl);
            dr = search_x(r, xr);
            if (dl <= dr) { y2 = r; } 
            else { y1 = l; }
        }
        y = (y1+y2)/2;
        return search_x(y, x);
    };
    ld x, y;
    search_y(x, y);
    std::cout << x << ' ' << y << std::endl;
    return 0;
}