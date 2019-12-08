/*
    Problem: 322B. Ciel and Flowers
    Solution: combinatorics, math
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int a, b, c; std::cin >> a >> b >> c;
    int res = a / 3 + b / 3 + c / 3;
    if (a > 0 && b > 0 && c > 0) {
        res = std::max(res, (a-1) / 3 + (b - 1) / 3 + (c - 1) / 3 + 1);
    }
    if (a > 1 && b > 1 && c > 1) {
        res = std::max(res, (a-2) / 3 + (b - 2) / 3 + (c - 2) / 3 + 2);
    }
    std::cout << res;
    return 0;
}