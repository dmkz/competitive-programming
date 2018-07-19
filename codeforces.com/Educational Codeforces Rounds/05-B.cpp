/*
    Problem: 616B. Dinner with Emma
    
    Solution: games, greedy, minimal, maximal, O(n*m)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int nRows, nCols; std::cin >> nRows >> nCols;
    std::vector<std::vector<int>> map(nRows, std::vector<int>(nCols));
    std::vector<int> min_in_row(nRows);
    for (int row = 0; row < nRows; ++row) {
        for (int col = 0; col < nCols; ++col) {
            std::cin >> map[row][col];
        }
        min_in_row[row] = *min_element(map[row].begin(), map[row].end());
    }
    
    std::cout << *max_element(min_in_row.begin(), min_in_row.end()) << std::endl;
    
    return 0;
}