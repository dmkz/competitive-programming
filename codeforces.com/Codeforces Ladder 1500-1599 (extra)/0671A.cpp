/*
    Problem: 671A. Recycling Bottles
    
    Solution: math, geometry, dynamic programming, O(n)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>

typedef long double Real;

struct Point {
    int x, y;
    
    static Point read() {
        int x_, y_;
        scanf("%d %d", &x_, &y_);
        return Point{x_, y_};
    }
    
    Real dist(const Point& p) const {
        Real dx = x-p.x, dy = y-p.y;
        return std::sqrt(dx*dx+dy*dy);
    }
};

Real fast(Point a, Point b, Point c, const std::vector<Point>& pt) {
    const int n = (int)pt.size();
    Real total = 0;
    for (int i = 0; i < n; ++i) {
        total += pt[i].dist(c);
    }
    Real answ = 1e18L;
    for (int i = 0; i < n; ++i) {
        Real temp = pt[i].dist(a) - pt[i].dist(c) + 2 * total;
        answ = std::min(answ, temp);
    }
    for (int i = 0; i < n; ++i) {
        Real temp = pt[i].dist(b) - pt[i].dist(c) + 2 * total;
        answ = std::min(answ, temp);
    }
    std::vector<Real> pref(1+n, 1e18L), suff(1+n, 1e18L);
    for (int i = 0; i < n; ++i) {
        pref[i+1] = std::min(pref[i],pt[i].dist(b)-pt[i].dist(c));
    }
    for (int i = n-1; i >= 0; --i) {
        suff[i] = std::min(suff[i+1],pt[i].dist(b)-pt[i].dist(c));
    }
    for (int i = 0; i < n; ++i) {
        Real temp = pt[i].dist(a) - pt[i].dist(c) + 2 * total + std::min(pref[i], suff[i+1]);
        answ = std::min(answ, temp);
    }
    return answ;
}

int main() {
    // Input:
    Point a = Point::read(), b = Point::read(), c = Point::read();
    int n; scanf("%d", &n);
    std::vector<Point> pt;
    for (int i = 0; i < n; ++i) {
        pt.push_back(Point::read());
    }
    // Output:
    printf("%0.6Lf\n", fast(a,b,c,pt));
    return 0;
}