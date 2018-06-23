/*
    Пересечение двух равнобедренных треугольников со сторонами, параллельными осям координат за O(log(n)).
    
    Асимптотика O(n log(n))
*/

#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cassert>

struct Triangle {
    int x, y, side;
    
    inline bool in(const int px, const int py) const {
        return px >= x && py >= y && py+px <= x+side+y;
    }
    
    static Triangle read() {
        int x, y, s;
        scanf("%d %d %d", &x, &y, &s);
        return Triangle{2*x, 2*y, 2*s};
    }
};

bool intersect(Triangle a, Triangle b, Triangle& c) {
    int x = std::max(a.x, b.x);
    int y = std::max(a.y, b.y);
    if (!a.in(x,y) || !b.in(x,y)) {
        c = Triangle{x,y,0};
        return false;
    }
    int low = 0, high = 1e9;
    while (high-low > 1) {
        int mid = (low+high) / 2;
        if (!a.in(x+mid,y) || !a.in(x,y+mid) || !b.in(x+mid,y) || !b.in(x,y+mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }
    c = Triangle{x, y, low};
    return true;
}

int main() {
    int n;
    scanf("%d", &n);
    
    auto tr = Triangle::read();
    while (--n) {
        intersect(tr, Triangle::read(), tr);
    }
    printf("%0.3f", tr.side * tr.side / 8.0);
    
    return 0;
}