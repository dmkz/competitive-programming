/*
    Problem: 590B. Chip 'n Dale Rescue Rangers
    
    Solution: binary search, geometry, O(log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <algorithm>
#include <cmath>

typedef long double Real;

struct Point {
    Real x, y;
    
    Point(Real x_ = 0, Real y_ = 0) : x(x_), y(y_) { }
    
    static Point read() {
        int x_, y_;
        scanf("%d %d", &x_, &y_);
        return Point(x_, y_);
    }
    
    Point& operator*=(const Real value) {
        x *= value, y *= value;
        return *this;
    }
    
    Point operator*(const Real value) const {
        return Point(*this) *= value;
    }
    
    Point& operator-=(const Point& p) {
        x -= p.x, y -= p.y;
        return *this;
    }
    
    Point operator-(const Point& p) {
        return Point(*this) -= p;
    }
    
    Point& operator+=(const Point& p) {
        x += p.x, y += p.y;
        return *this;
    }
    
    Point operator+(const Point& p) {
        return Point(*this) += p;
    }
    
    Real norm() const {
        return std::sqrt(x * x + y * y);
    }
};

int main() {
    auto f = Point::read(), s = Point::read();
    Real vmax, t;
    scanf("%Lf %Lf", &vmax, &t);
    auto v1 = Point::read(), v2 = Point::read();
    Real low = 0, high = 1e12;
    for (int i = 0; i < 100; ++i) {
        Real time = (low + high) / 2;
        auto temp = s - (f + v1 * std::min(time, t) + v2 * std::max(Real(0), time - t));
        if (temp.norm() <= time * vmax) {
            high = time;
        } else low = time;
    }
    printf("%0.6Lf", high);
    return 0;
}