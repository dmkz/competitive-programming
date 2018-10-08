/*
    Problem: 471A. MUH and Sticks
    
    Solution: implementation, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    static int count[10];
    for (int i = 0; i < 6; ++i) {
        int v; std::cin >> v; count[v]++;
    }
    int p4 = -1;
    for (int i = 1; i <= 9; ++i) {
        if (count[i] == 5) {
            std::cout << "Bear"; return 0;
        }
        if (count[i] == 6) {
            std::cout << "Elephant"; return 0;
        }
        if (count[i] == 4) {
            p4 = i;
        }
    }
    if (p4 == -1) { std::cout << "Alien"; return 0; }
    for (int i = 1; i <= 9; ++i) {
        if (count[i] == 2) {
            std::cout << "Elephant"; return 0;
        }
        if (count[i] == 1) {
            std::cout << "Bear"; return 0;
        }
    }
    throw 1;
}