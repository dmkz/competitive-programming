/*
    Задача: 714. Кольцевая автодорога
    
    Решение: тернарный поиск, геометрия, окружность, срединный перпендикуляр, O(log(MAX))
    
    Автор: Дмитрий Козырев, https://github.com/dmkz , dmkozyrev@rambler.ru
*/


#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <tuple>
#include <iostream>
#include <iomanip>
#include <cassert>

typedef long double Real;

const Real PI = std::acos(Real(-1.0));

const Real EPS = 1e-14;

bool equal(Real a, Real b) {
    return std::abs(a-b) <= std::max(Real(1), std::abs(a) + std::abs(b)) * EPS;
}

struct Vector {
    Real x, y;
    
    Vector(Real x_ = 0, Real y_ = 0) : x(x_), y(y_) { }
    
    Vector operator-() const { return Vector(-x, -y); }
    Vector operator+(const Vector& p) const { return Vector(x+p.x, y+p.y); }
    Vector operator-(const Vector& p) const { return Vector(x-p.x, y-p.y); }
    Vector operator*(const Real val) const { return Vector(x*val, y*val); }
    Vector operator/(const Real val) const { return Vector(x/val, y/val); }
    Real scal(const Vector& b) const { return x * b.x + y * b.y; }
    Real cross(const Vector& b) const { return x * b.y - y * b.x; }
    Real norm() const { return std::sqrt(scal(*this)); }
    
    Vector rotate(const Real angle) const {
        return Vector(
            x * std::cos(angle) - y * std::sin(angle),
            x * std::sin(angle) + y * std::cos(angle)
        );
    }
    
    static Vector read() { int x, y; scanf("%d %d", &x, &y); return Vector(x,y); }
};
typedef Vector Point;

struct Line {
    // p' = p + v * t
    Point p, v;
    
    Line(const Point& a, const Point& b) : p(a), v(b-a) { v = v / v.norm(); }
    
    Point get_point(Real t) const { return p + v * t; }
    
    bool contains(const Point& p_) const {
        return equal((p_ - p).cross(v), 0);
    }
    
    int intersect(const Line& L, Point& p_) const {
        auto q = v.cross(L.v);
        if (equal(q, 0)) {
            return contains(L.p) ? 2 : 0;
        }
        p_ = get_point((L.p - p).cross(L.v) / q);
        return 1;
    }
};

Line bisector(const Point& a, const Point& b) {
    return Line((a+b)/2, (a+b)/2+(b-a).rotate(PI/2));
}

struct Circle {

    Point c; Real r;
    
    Circle(const Point& c_, Real r_) : c(c_), r(r_) { }

};

bool operator<(const Circle& a, const Circle& b) {
    bool eq_r = equal(a.r, b.r);
    bool eq_x = equal(a.c.x, b.c.x);
    bool eq_y = equal(a.c.y, b.c.y);
    return (!eq_r && a.r < b.r) || (eq_r && ((!eq_x && a.c.x < b.c.x) || (eq_x && (!eq_y && a.c.y < b.c.y))));
}

int main() {
    std::vector<Point> pt;
    for (int i = 0; i < 4; ++i) {
        pt.push_back(Point::read());
    }
    
    std::vector<Line> bisectors;
    for (int i = 0; i < 4; ++i) {
        for (int j = i+1; j < 4; ++j) {
            bisectors.push_back(bisector(pt[i], pt[j]));
        }
    }
    
    bool infinity = false;
    std::set<Circle> set;
    
    for (int i = 0; i < (int)bisectors.size(); ++i) {
        for (int j = i+1; j < (int)bisectors.size(); ++j) {
            const auto& L1 = bisectors[i];
            const auto& L2 = bisectors[j];                        
            Point p;
            int code = L1.intersect(L2, p);
            
            if (code == 0) {
                continue;
            } else if (code == 2) {
                // using ternary search by optimal position on bisector:
                auto f = [&](const Real t) {
                    Real dist = 0;
                    for (int k = 0; k < 4; ++k) {
                        dist += (L1.get_point(t) - pt[k]).norm();
                    }
                    return dist / 4;
                };
                Real a = -1e9, b = 1e9;
                while (b - a >= EPS / 2) {
                    Real x1 = a + (b-a) / 3;
                    Real x2 = b - (b-a) / 3;
                    if (f(x1) < f(x2)) {
                        b = x2;
                    } else {
                        a = x1;
                    }
                }
                p = L1.get_point((a+b)/2);
            }
            
            auto f = [&](const Real value) {
                Real max = -1e9, min = +1e9;
                for (int k = 0; k < 4; ++k) {
                    Real dist = std::abs(value - (p-pt[k]).norm());
                    max = std::max(max, dist);
                    min = std::min(min, dist);
                }
                return max-min;
            };
            // Ternary search by optimal radius:
            Real low  = 1e9, high = -1e9;
            for (int k = 0; k < 4; ++k) {
                low  = std::min( low, (p-pt[k]).norm());
                high = std::max(high, (p-pt[k]).norm());
            }
            while (high - low >= EPS / 2) {
                Real x1 = low  + (high - low) / 3;
                Real x2 = high - (high - low) / 3;
                if (f(x1) < f(x2)) {
                    high = x2;
                } else {
                    low  = x1;
                }
            }
            Real radius = (equal(f(0), 0)) ? (infinity = true, 0) : (low+high) / 2;
            set.insert(Circle(p, radius));
        }
    }
    if (infinity) {
        printf("Infinity\n");
    } else {
        printf("%d\n", (int)set.size());
    }
    assert(set.size() >= 1u);
    auto ans = *set.begin();
    std::cout << std::fixed << std::setprecision(5) << ans.c.x << ' ' << ans.c.y << ' ' << ans.r << '\n';
    return 0;
}