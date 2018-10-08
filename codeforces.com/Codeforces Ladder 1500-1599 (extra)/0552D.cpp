/*
    Problem: 552D. Vanya and Triangles
    
    Solution: geometry, math, gcd, triangles, O(n^2*log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <map>
#include <vector>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

struct Point {
    int x, y;
};

bool operator<(const Point& a, const Point& b) {
    return a.y * b.x < a.x * b.y || (a.y * b.x == a.x * b.y && a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y);
}

int main() {
    int n; scanf("%d", &n);
    std::vector<Point> pt(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &pt[i].x, &pt[i].y);
    }
    int answ = 0;
    for (int i = 0; i < n; ++i) {
        std::map<Point, int> collinear;
        for (int j = i+1; j < n; ++j) {
            Point p{pt[j].x-pt[i].x, pt[j].y-pt[i].y};
            if (p.x < 0 || (p.x == 0 && p.y < 0)) {
                p.x = -p.x;
                p.y = -p.y;
            }
            int g = gcd(std::abs(p.y), std::abs(p.x));
            p.y /= g;
            p.x /= g;
            answ += j - i - 1 - collinear[p];
            collinear[p]++;
        }
    }
    printf("%d\n", answ);
    return 0;
}