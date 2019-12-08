/*
    Problem: 257C. View Angle
    Solution: geometry, sorting, brute force, math
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <cmath>

typedef long double Real;

const Real PI = std::acos(Real(-1.0));

struct Point {
    int x, y;
    
    static Point read() {
        int x_, y_;
        std::cin >> x_ >> y_;
        return Point{x_,y_};
    }
    
    inline Real angle() const {
        return std::atan2(Real(y), Real(x));
    }
    
    inline int norm2() const {
        return x*x+y*y;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    std::vector<Point> pt;
    for (int i = 0; i < n; ++i) {
        pt.push_back(Point::read());
    }
    std::sort(pt.begin(), pt.end(), [](const Point& a, const Point& b) {
        auto angle1 = a.angle();
        auto angle2 = b.angle();
        return angle1 < angle2 || (angle1 == angle2 && a.norm2() < b.norm2());
    });
    
    pt.erase(std::unique(pt.begin(), pt.end(), [](const Point& a, const Point& b) {
        return a.angle() == b.angle();
    }), pt.end());
    
    if (pt.size() == 1u) {
        std::cout << 0;
        return 0;
    }
    
    n = (int)pt.size();
    Real answ = 2*PI;
    for (int i = 0; i < n; ++i) {
        Real angle = pt[(i-1+n)%n].angle() - pt[i].angle();
        if (angle <= 0) angle += 2 * PI;
        answ = std::min(answ, angle);
    }
    std::cout << std::fixed << std::setprecision(6) << answ / PI * 180;
    return 0;
}