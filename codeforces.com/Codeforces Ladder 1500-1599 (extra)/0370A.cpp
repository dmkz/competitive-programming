/*
    Problem: 370A. Rook, Bishop and King
    
    Solution: implementation, math, O(1)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>

int main() {
    int r1, c1, r2, c2;
    std::cin >> r1 >> c1 >> r2 >> c2;
    if (r1 == r2 && c1 == c2) {
        std::cout << "0 0 0"; return 0;
    }
    if (r1 > r2) std::swap(r1, r2);
    if (c1 > c2) std::swap(c1, c2);
    if (r1 == r2 || c1 == c2) {
        std::cout << "1 ";
    } else {
        std::cout << "2 ";
    }
    if ((r1+c1)%2 != (r2+c2)%2) {
        std::cout << "0 ";
    } else if (r1+c1 == r2 + c2 || r1-c1 == r2-c2) {
        std::cout << "1 ";
    } else {
        std::cout << "2 ";
    }
    int dr = r2-r1;
    int dc = c2-c1;
    std::cout << std::max(dr,dc);
    return 0;
}