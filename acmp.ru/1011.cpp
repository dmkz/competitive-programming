/*
    Задача: 1011. Треугольник и окружности
    
    Решение: геометрия, точка, вектор, вращение, прямая, треугольник, окружность, O(1)
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

typedef long double Real;

const Real PI = std::acos(Real(-1));

struct Point {
    Real x, y;
    
    static Point read() {
        Real x_, y_;
        std::cin >> x_ >> y_;
        return Point{x_, y_};
    }
    
    inline Real norm() const {
        return std::sqrt(x * x + y * y);
    }
    
    inline Point operator-(const Point& other) const {
        return Point{x-other.x, y-other.y};
    }
    
    inline Point operator+(const Point& other) const {
        return Point{x+other.x, y+other.y};
    }
    
    inline Point operator/(const Real q) const {
        return Point{x / q, y / q};
    }
    
    inline Point rot(const Real angle) const {
        return Point {
            std::cos(angle) * x - std::sin(angle) * y,
            std::sin(angle) * x + std::cos(angle) * y
        };
    }
};

inline Real det(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {

    Real A, B, C;

    Line(const Point& a, const Point& b) {
        // -(b.y-a.y)*(x-a.x) + (b.x-a.x)*(y - a.y) = 0
        A = a.y - b.y;
        B = b.x - a.x;
        C = -(a.x * A + a.y * B);
        assert(std::abs(A * a.x + B * a.y+C) <= 1e-14);
        assert(std::abs(A * b.x + B * b.y+C) <= 1e-14);
    }
    
    inline Point intersect(const Line& L) const {
        auto q = det(Point{ A, B}, Point{ L.A, L.B});
        auto a = det(Point{-C, B}, Point{-L.C, L.B});
        auto b = det(Point{ A,-C}, Point{ L.A,-L.C});
        return Point{a / q, b / q};
    }
    
    inline Real value(const Point& p) const {
        return A * p.x + B * p.y + C;
    }
};

inline Real dist(const Point& p, const Line& L) {
    return std::abs(L.value(p)) / Point{L.A, L.B}.norm();
}

inline Real dist(const Point& a, const Point& b) {
    return (a-b).norm();
}

int main() {
    Point A = Point::read();
    Point B = Point::read();
    Point C = Point::read();
    std::string query;
    std::cin >> query;
    if (query == "In") {
        auto v1 = (B-A);
        auto v2 = (C-A);
        v1 = v1 / v1.norm();
        v2 = v2 / v2.norm();
        Line L1(A, A+(v1+v2)/2);
        v1 = A-B;
        v2 = C-B;
        v1 = v1 / v1.norm();
        v2 = v2 / v2.norm();
        Line L2(B, B+(v1+v2)/2);
        auto Center = L1.intersect(L2);
        auto Radius = dist(Center, Line(A, B));
        std::cout << std::fixed << std::setprecision(3) << Center.x << ' ' << Center.y << ' ' << Radius;
    } else {
        Point M1 = (A+B)/2;
        Point M2 = (B+C)/2;
        Line L1(M1, M1 + (B-A).rot(PI/2));
        Line L2(M2, M2 + (C-B).rot(PI/2));
        auto Center = L1.intersect(L2);
        auto Radius = dist(Center, A);
        std::cout << std::fixed << std::setprecision(3) << Center.x << ' ' << Center.y << ' ' << Radius;
    }
    return 0;
}