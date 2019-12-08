/*
    Problem: 268C. Beautiful Sets of Points
    Solution: geometry, constructive
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int main() {
    
    int nRows, nCols;
    std::cin >> nCols >> nRows;
    
    int n = std::min(nRows, nCols);
    
    std::cout << n+1 << '\n';
    for (int x = n; x >= 0; --x) {
        std::cout << x << ' ' << n - x << '\n';
    }
    
    return 0;
}