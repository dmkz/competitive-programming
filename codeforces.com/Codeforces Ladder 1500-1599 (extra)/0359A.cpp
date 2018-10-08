/*
    Problem: 359A. Table
    
    Solution: constructive, greedy, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>

int main() {
    int R, C; std::cin >> R >> C;
    for (int r = 1; r <= R; ++r) {
        for (int c = 1; c <= C; ++c) {
            int v; std::cin >> v;
            if (v == 0) continue; 
            if (c == 1 || c == C || r == R || r == 1) {
                std::cout << 2; return 0;
            }
        }
    }
    std::cout << 4;
    return 0;
}