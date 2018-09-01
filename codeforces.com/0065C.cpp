/*
    Problem: 65C. Harry Potter and the Golden Snitch
    
    Solution: binary search, geometry, O(n log(MAX))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <vector>
#include <cmath>

typedef long double Real;

struct Point {

    Real x, y, z;
    
    Point(Real x_ = 0, Real y_ = 0, Real z_ = 0) : x(x_), y(y_), z(z_) { }
    
    static Point read() {
        int x_, y_, z_;
        scanf("%d %d %d", &x_, &y_, &z_);
        return Point(x_, y_, z_);
    }
    
    Point& operator*=(const Real v) {
        return x*=v, y*=v, z*=v, *this;
    }
    
    Point& operator-=(const Point& p) {
        return x-=p.x, y-=p.y, z-=p.z, *this;
    }
    
    Point& operator+=(const Point& p) {
        return x+=p.x, y+=p.y, z+=p.z, *this;
    }
    
    Point operator*(const Real v) { return Point(*this) *= v; }
    Point operator+(const Point& p) { return Point(*this) += p; }
    Point operator-(const Point& p) { return Point(*this) -= p; }
    
    Real norm() const {
        return std::sqrt(x*x+y*y+z*z);
    }
};

bool solve(Point curr, Point next, Point pos, Real v1, Real v2, Real delta, Real& time, Point& answ) {
    if ((next-curr).norm() / v1 < (next-pos).norm() / v2 - delta) {
        return false;
    }
    auto v = next-curr;
    Real low = 0, high = 1;
    for (int i = 0; i < 100; ++i) {
        Real mid = (low + high) / 2;
        if ((v * mid).norm() / v1 < (curr + v * mid - pos).norm() / v2 - delta) {
            low = mid;
        } else {
            high = mid;
        }
    }
    time = (curr + v * high - pos).norm() / v2;
    answ = curr + v * high;
    return true;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Point> pt;
    for (int i = 0; i <= n; ++i) {
        pt.push_back(Point::read());
    }
    Real v1, v2;
    scanf("%Lf %Lf", &v2, &v1);
    auto pos = Point::read();
    Real delta = 0, time;
    Point answ; bool flag = false;
    for (int i = 0; i < n; ++i) {
        if (solve(pt[i], pt[i+1], pos, v1, v2, delta, time, answ)) {
            flag = true;
            break;
        } else {
            delta += (pt[i+1] - pt[i]).norm() / v1;
        }
    }
    if (!flag) {
        printf("NO"); return 0;
    }
    printf("YES\n");
    printf("%0.6Lf\n", time);
    printf("%0.6Lf %0.6Lf %0.6Lf", answ.x, answ.y, answ.z);
    return 0;
}