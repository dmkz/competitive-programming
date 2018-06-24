#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

struct Point {
    int x, y;
    
    inline int norm2() const {
        return x * x + y * y;
    }
};

inline int cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

bool solve(int side, std::vector<Point> p) {
    
    std::vector<Point> positive, negative;
    
    for (auto& it : p) {
        it.x = 2 * it.x - side;
        it.y = 2 * it.y - side;
        if (it.x == 0 && it.y == 0) {
            return false;
        }
        if (it.x > 0 || (it.x == 0 && it.y > 0)) {
            positive.push_back(Point{it.x, it.y});
        } else {
            negative.push_back(Point{it.x, it.y});
        }
    }
    // Сортировка положительной половины и удаление повторяющихся углов:
    std::sort(positive.begin(), positive.end(), [](const Point& a, const Point& b) {
        return a.y * b.x < b.y * a.x || (a.y * b.x == b.y * a.x && a.norm2() < b.norm2());
    });
    
    positive.erase(std::unique(positive.begin(), positive.end(), [](const Point& a, const Point& b) {
        return a.y * b.x == b.y * a.x;
    }), positive.end());
    
    // Сортировка отрицательной половины и удаление повторяющихся углов:
    std::sort(negative.begin(), negative.end(), [](const Point& a, const Point& b) {
        return a.y * b.x < b.y * a.x || (a.y * b.x == b.y * a.x && a.norm2() < b.norm2());
    });
    
    negative.erase(std::unique(negative.begin(), negative.end(), [](const Point& a, const Point& b) {
        return a.y * b.x == b.y * a.x;
    }), negative.end());
    
    // Объединение двух половин точек:
    p.clear();
    p.insert(p.end(), positive.begin(), positive.end());
    p.insert(p.end(), negative.begin(), negative.end());
    
    if (p.size() == 1u) {
        return true;
    }
    
    const int n = p.size();
    
    p.push_back(p[0]);
    
    for (int i = 1; i <= n; ++i) {
        if (cross(p[i-1], p[i]) < 0) {
            return true;
        }
    }
    return false;
}

int main() {
    
    int side, n;
    scanf("%d %d", &side, &n);
    
    std::vector<Point> p;
    for (int i = 0; i < n; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        assert(0 < x && x < side);
        assert(0 < y && y < side);
        p.push_back(Point{x,y});
    }
    printf(solve(side, p) ? "YES\n" : "NO\n");
    
    return 0;
}