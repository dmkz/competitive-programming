/*
    Problem: 270A. Fancy Fence
    Solution: geometry, math, implementation
*/
#include <iostream>

int main() {
    int n; std::cin >> n;
    while (n--) {
        int a; std::cin >> a;
        std::cout << (360 % (180-a) == 0 ? "YES" : "NO") << '\n';
    }
    return 0;
}