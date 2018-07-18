/*
    Problem: 598C. Nearest vectors
    
    Solution: sorting, polar angle, geometry, O(n log(n))
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>

typedef long double ld;

const ld PI = std::acos(ld(-1));

struct Point {
    int x, y, id;
    ld angle;
    
    Point(int x, int y, int id) : x(x), y(y), id(id), angle(std::atan2(ld(y), ld(x))) { }
};

ld min_angle(const Point & a, const Point & b) {
    ld diff = std::abs(a.angle - b.angle);
    return std::min(diff, 2 * PI - diff);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n; std::cin >> n;
    
    std::vector<Point> points;
    
    for (int i = 0; i < n; ++i) {
        int x, y; 
        std::cin >> x >> y; 
        points.push_back(Point(x, y, i+1));
    }
    
    std::sort(points.begin(), points.end(), [](const Point& a, const Point & b) {
        return a.angle < b.angle; 
    });
    
    int min_i, min_j;
    ld min_angle = 1e9;
    for (int i = 0; i < n; ++i) {
        const Point & a = points[i];
        const Point & b = points[(i+1) % n];
        ld angle = ::min_angle(a, b);
        if (min_angle > angle) {
            min_i = a.id;
            min_j = b.id;
            min_angle = angle;
        }
    }
    assert(1 <= min_i && min_i <= n && 1 <= min_j && min_j <= n);
    std::cout << min_i << " " << min_j;
    
    return 0;
}