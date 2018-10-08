/*
    Problem: 334B. Eight Point Sets
    
    Solution: sorting, unique, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>

struct Point {
    int x, y;
};

inline bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int main() {
    std::vector<int> x(8), y(8);
    std::vector<Point> p(8);
    for (int i = 0; i < 8; ++i) {
        std::cin >> x[i] >> y[i];
        p[i] = Point{x[i], y[i]};
    }
    std::sort(p.begin(), p.end());
    std::sort(x.begin(), x.end());
    std::sort(y.begin(), y.end());
    x.erase(std::unique(x.begin(), x.end()), x.end());
    y.erase(std::unique(y.begin(), y.end()), y.end());
    if (x.size() != 3u || y.size() != 3u) {
        std::cout << "ugly"; return 0;
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 && j == 1) continue;
            if (!std::binary_search(p.begin(), p.end(), Point{x[i], y[j]})) {
                std::cout << "ugly"; return 0;
            }
        }
    }
    std::cout << "respectable";
    return 0;
}