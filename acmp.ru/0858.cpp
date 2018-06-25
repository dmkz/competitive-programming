#include <iostream>
#include <iomanip>
#include <cmath>

typedef long double Real;

struct Point {
    Real x, y;
};

Point operator-(const Point& a, const Point& b) {
    return Point{a.x - b.x, a.y - b.y};
}

Real cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    int a, b, c;
    
    static Line read() {
        int a, b, c;
        std::cin >> a >> b >> c;
        return Line{a,b,c};
    }
    
    Point intersect(const Line& other) const {
        const int a1 = a, b1 = b, c1 = c, a2 = other.a, b2 = other.b, c2 = other.c;
        // a1 * x + b1 * y = c1
        // a2 * x + b2 * y = c2
        const auto x = Real(c1 * b2 - c2 * b1) / (a2 * b1 - a1 * b2);
        const auto y = Real(a2 * c1 - a1 * c2) / (a2 * b1 - a1 * b2);
        return Point{x,y};
    }
};

int main() {
    auto l1 = Line::read(), l2 = Line::read(), l3 = Line::read();
    auto A = l1.intersect(l2), B = l1.intersect(l3), C = l2.intersect(l3);
    std::cout << std::fixed << std::setprecision(3) << std::abs(cross(B-A,C-A)) / 2;
    return 0;
}