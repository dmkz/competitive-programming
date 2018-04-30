#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>

typedef long double Real;

struct Point {
    Real x, y;
    
    Point(Real x = 0, Real y = 0) : x(x), y(y) { }
    
    static Point read() {
        int x, y;
        scanf("%d %d", &x, &y);
        return Point(x, y);
    }
    
    Real dist(const Point& other) const {
        Real dx = x - other.x;
        Real dy = y - other.y;
        return std::sqrt(dx*dx+dy*dy);
    }
};

Real dist(Point s, const std::vector<Point>& points) {
    Real sum = 0;
    for (auto it : points) {
        sum += it.dist(s);
    }
    return sum;
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Point> points(n);
    
    for (auto &it : points) it = Point::read();
    
    Real L = std::min(points[0].x, points[1].x);
    Real R = std::max(points[0].x, points[1].x);
    Real dist_L = dist({L, 0}, points);
    Real dist_R = dist({R, 0}, points);
    
    const Real EPS = 1e-8;
    while (R - L > EPS) {
        Real l = (6 * L + 5 * R) / 11;
        Real r = (5 * L + 6 * R) / 11;
        Real dist_l = dist({l, 0}, points);
        Real dist_r = dist({r, 0}, points);
        if (dist_l < dist_r) {
            R = r;
            dist_R = dist_r;
        } else {
            L = l;
            dist_L = dist_l;
        } 
    }
    std::cout << std::fixed << std::setprecision(8) << (L+R)/2 << std::endl;
    return 0;
}