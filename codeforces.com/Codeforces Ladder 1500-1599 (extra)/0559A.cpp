/*
    Problem: 559A. Gerald's Hexagon
    
    Solution: geometry, rotate, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <cmath>

typedef long double Real;

const Real PI = std::acos(-1.0L);

struct Point {

    Real x, y;
    
    Point(Real x_ = 0, Real y_ = 0) : x(x_), y(y_) { }
    
    Point operator+(const Point& p) const {
        return Point{x + p.x, y + p.y};
    }
    
    Point operator-(const Point& p) const {
        return Point{x - p.x, y - p.y};
    }

    Point operator*(Real v) const {
        return Point{x * v, y * v};
    }
    
    Point operator/(Real v) const {
        return Point{x / v, y / v};
    }
    
    Point rotate(Real angle) const {
        return Point {
            std::cos(angle) * x - std::sin(angle) * y,
            std::sin(angle) * x + std::cos(angle) * y
        };
    }
    
};

Real det(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    Real s = 0;
    Point p(0, 0), v(1, 0);
    for (int i = 0; i < 6; ++i) {
        int side; std::cin >> side;
        auto next = p + v * side;
        s += det(p, next);
        p = next;
        v = v.rotate(PI / 3);
    }
    s = std::abs(s) / 2.0;
    int cnt = (int)std::round(4 * s / std::sqrt(3.0L));
    std::cout << cnt;
    return 0;
}