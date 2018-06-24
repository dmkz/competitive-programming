#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long double ld;

struct Point {
    int x, y;
    
    static Point read() {
        int x, y;
        scanf("%d %d", &x, &y);
        return Point{x,y};
    }
    
    inline int norm2() const {
        return x * x + y * y;
    }
    
    inline ld angle() const {
        return std::atan2(ld(y), ld(x));
    }
};

inline int cross(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

int main() {
    int xc, yc; double R;
    scanf("%d %d %lf", &xc, &yc, &R);
    int n;
    scanf("%d", &n);
    
    std::vector<Point> points;
    
    while (n--) {
        auto p = Point::read();
        p.x -= xc;
        p.y -= yc;
        if (p.x*p.x+p.y*p.y > R*R) {
            continue;
        }
        points.push_back(p);
    }
    
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.angle() < b.angle() || (a.angle() == b.angle() && a.norm2() < b.norm2());
    });
    
    n = points.size();
    
    if (n <= 1) {
        printf("%d", n);
        return 0;
    }
    
    int l = 0, r = 0, answ = 1;
    while (l < n) {
        while ((r+1) % n != l && cross(points[l], points[(r+1) % n]) >= 0) {
            (++r) %= n;
        }
        answ = std::max(answ, r < l ? r+n-l+1 : r-l+1);
        ++l;
    }
    printf("%d", answ);
    return 0;
}