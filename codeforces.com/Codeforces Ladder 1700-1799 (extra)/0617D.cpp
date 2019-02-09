/*
    Problem: 617D. Polyline
    
    Solution: constructive, geometry, brute force, O(n!)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

int solve(int x1, int y1, int x2, int y2, int x3, int y3) {
    if (x1 == x2 && x1 == x3) {
        return 1;
    }
    if (x1 == x2 && (y3 <= std::min(y1,y2) || std::max(y1,y2) <= y3)) {
        return 2;
    }
    return 3;
}

int solveMain(int x1, int y1, int x2, int y2, int x3, int y3) {
    return std::min(solve(x1,y1,x2,y2,x3,y3),solve(y1,x1,y2,x2,y3,x3));
}

int main() {
    int x1, y1, x2, y2, x3, y3;
    while (std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
        int res = solveMain(x1,y1,x2,y2,x3,y3);
        res = std::min(res, solveMain(x1,y1,x3,y3,x2,y2));
        res = std::min(res, solveMain(x2,y2,x1,y1,x3,y3));
        res = std::min(res, solveMain(x2,y2,x3,y3,x1,y1));
        res = std::min(res, solveMain(x3,y3,x1,y1,x2,y2));
        res = std::min(res, solveMain(x3,y3,x2,y2,x1,y1));
        std::cout << res << std::endl;
    }
    return 0;
}