/*
    Problem: 493D. Vasya and Chess
    Solution: constructive, math, games, O(1)
*/
#include <iostream>

int main() {
    int n; std::cin >> n;
    if (n % 2 == 0) {
        std::cout << "white\n1 2";
    } else {
        std::cout << "black";
    }
    return 0;
}