/*
    "Задача Пифагора": геометрия, наибольшая площадь треугольника, O(1)
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <cassert>

typedef long double Real;

const Real PI = std::acos(Real(-1));

Real solve(Real a, Real b, Real c) {
    auto minAngle = std::acos((b*b+c*c-a*a)/(2*b*c));
    if (minAngle >= PI / 4) {
        return c * c / 4;
    } else if (c * std::cos(minAngle) >= b) {
        return b * b * std::tan(minAngle) / 2;
    } else {
        return c * std::sin(minAngle) * c * std::cos(minAngle) / 2;
    }
}

int main() {
    Real a, b, c;
    std::cin >> a >> b >> c;
    if (a > b) std::swap(a, b);
    if (a > c) std::swap(a, c);
    if (b > c) std::swap(b, c);
    assert(a <= b && b <= c);
    std::cout << std::fixed << std::setprecision(6) << solve(a, b, c);
    return 0;
}