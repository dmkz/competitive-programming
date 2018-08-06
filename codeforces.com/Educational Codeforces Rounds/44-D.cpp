/*
    Problem: 1016D. Vasya And The Matrix
    
    Solution: constructive algorithm, math, O(n*m)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>

int main() {
    int nRows, nCols;
    std::cin >> nRows >> nCols;
    
    std::vector<int> rows(nRows), cols(nCols);
    int xor1 = 0, xor2 = 0;
    for (auto& it : rows) {
        std::cin >> it;
        xor1 ^= it;
    }
    for (auto& it : cols) {
        std::cin >> it;
        xor2 ^= it;
    }
    if (xor1 != xor2) {
        std::cout << "NO";
        return 0;
    }
    std::vector<std::vector<int>> answ(nRows, std::vector<int>(nCols));
    for (int i = 1; i < nCols; ++i) {
        answ[0][i] = cols[i];
        xor1 ^= cols[i];
    }
    for (int i = 1; i < nRows; ++i) {
        answ[i][0] = rows[i];
        xor1 ^= rows[i];
    }
    answ[0][0] = xor1;
    std::cout << "YES\n";
    for (auto& row : answ) {
        for (auto& it : row) {
            std::cout << it << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}