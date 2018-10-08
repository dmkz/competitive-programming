/*
    Problem: 424B. Megacity
    
    Solution: geometry, sorting, O(n log(n))
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>
#include <cmath>

struct Point { 
    int x, y, k; 
    
    inline int r2() const {
        return x*x+y*y;
    }
};

int main() {
    int n, cur; std::cin >> n >> cur;
    std::deque<Point> pt;
    for (int i = 0; i < n; ++i) {
        int x, y, k; std::cin >> x >> y >> k;
        pt.push_back(Point{x,y,k});
    }
    std::stable_sort(pt.begin(), pt.end(), [](const Point& a, const Point& b) {
        return a.r2() < b.r2();
    });
    int r2 = 0;
    while (!pt.empty() && cur < 1000*1000) {
        cur += pt.front().k; 
        r2 = std::max(r2, pt.front().r2());
        pt.pop_front();
    }
    if (cur < 1000*1000) {
        std::cout << -1; return 0;
    }
    std::cout << std::fixed << std::setprecision(6) << std::sqrt(r2);
    return 0;
}