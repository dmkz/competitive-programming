/*
    Problem: 451A. Game With Sticks
    
    Solution: implementation, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int n, m; std::cin >> n >> m; if (n > m) n = m;
    std::cout << (n % 2 == 1 ? "Akshat" : "Malvika");
    return 0;
}