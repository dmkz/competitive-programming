/*
    Problem: 650A. Watchmen
    
    Solution: geometry, math, map, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <map>

struct Point {
    
    int x, y;
    
};

inline bool operator<(const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int main() {
    int n; std::cin >> n;
    std::vector<Point> pt(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> pt[i].x >> pt[i].y;
    }
    std::map<int,int> cnt_x, cnt_y;
    std::map<Point,int> cnt_p;
    for (auto p : pt) {
        cnt_x[p.x]++;
        cnt_y[p.y]++;
        cnt_p[p]++;
    }
    int64_t answ = 0;
    for (auto p : pt) {
        cnt_x[p.x]--;
        cnt_y[p.y]--;
        cnt_p[p]--;
        answ += cnt_x[p.x] + cnt_y[p.y] - cnt_p[p];
    }
    std::cout << answ;
    return 0;
}