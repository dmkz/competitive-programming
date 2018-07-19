/*
    Problem: 600D. Number of Parallelograms
    
    Solution: geometry, math, O(n^2 log(n))
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <map>

struct Point {
    int x, y;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0); std::cerr.tie(0);
    
    int n;
    std::cin >> n;
    
    std::vector<Point> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i].x >> p[i].y;
    }
    std::map<std::pair<int,int>,int> count;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            int dx = p[j].x - p[i].x;
            int dy = p[j].y - p[i].y;
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }
            count[std::make_pair(dx,dy)]++;
        }
    }
    long long answ = 0;
    for (auto& it : count) {
        answ += it.second * (it.second-1) / 2;
    }
    assert(answ % 2 == 0);
    std::cout << answ / 2;
    return 0;
}