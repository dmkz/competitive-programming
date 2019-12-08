/*
    Problem: 116A. Tram
    Solution: implementation
*/
#include <iostream>
#include <algorithm>

int main() {
    int n; std::cin >> n;
    int max = 0, cur = 0;
    while (n--) {
        int a, b; std::cin >> a >> b;
        cur = cur - a + b;
        max = std::max(max, cur);
    }
    std::cout << max;
    return 0;
}