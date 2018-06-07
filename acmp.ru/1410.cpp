#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

typedef long double Real;

int main() {
    Real x1, y1, x2, y2, k;
    std::cin >> x1 >> y1 >> x2 >> y2 >> k;
    assert(!(x1 == x2 && y1 == y2));   
    // Находим середину отрезка AB:
    Real xc = (x1+x2)/2, yc = (y1+y2) / 2;
    // Находим направляющий вектор:
    Real dx = x2-x1;
    Real dy = y2-y1;
    dx *= k;
    dy *= k;
    std::swap(dx, dy);
    dx *= -1;
    // Находим точки C и D:
    Real x3 = xc + dx;
    Real y3 = yc + dy;
    Real x4 = xc - dx;
    Real y4 = yc - dy;
    // (x3, y3) делаем точкой, удовлетворяющей условию:
    if (y4 > y3 || (std::abs(y4 - y3) < 1e-4 && x4 < x3)) {
        std::swap(x3, x4);
        std::swap(y3, y4);        
    }
    // Выводим (x3, y3):
    std::cout << std::setprecision(4) << std::fixed << x3 << ' ';
    std::cout << std::setprecision(4) << std::fixed << y3 << ' ';
    return 0;
}