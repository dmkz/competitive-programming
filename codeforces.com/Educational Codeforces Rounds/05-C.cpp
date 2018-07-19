/*
    Problem: 616C. The Labyrinth
    
    Solution: graphs, DFS, components, O(n*m)
    
    Author: Dmitry Kozyrev, https://github.com/dmkz , dmkozyrev@rambler.ru
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <set>
#include <cassert>

const int WALL  = -2;
const int EMPTY = -1;

int main() {
    int nRows, nCols; std::cin >> nRows >> nCols;
    std::vector<std::vector<int>> color(1+nRows+1, std::vector<int>(1+nCols+1, WALL));
    for (int row = 1; row <= nRows; ++row) {
        char buf[1001]; scanf("%1000s", buf);
        for (int col = 1; col <= nCols; ++col) {
            char c = buf[col-1];
            color[row][col] = c == '*' ? WALL : EMPTY;
        }
    }
    std::vector<int> colorCount;
    int nColors = 0;
    for (int row = 1; row <= nRows; ++row) {
        for (int col = 1; col <= nCols; ++col) {
            if (color[row][col] == EMPTY) {
                std::function<void(int,int,int)> visit = [&](int row, int col, int c) {
                    color[row][col] = c;    
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr * dr + dc * dc == 1) {
                                if (color[row+dr][col+dc] == EMPTY) {
                                    color[row+dr][col+dc] = c;
                                    colorCount[c]++;
                                    visit(row+dr, col+dc, c);
                                }
                            }
                        }
                    }
                };
                colorCount.push_back(1);
                visit(row, col, nColors++);
            }
        }
    }
    
    for (int row = 1; row <= nRows; ++row) {
        for (int col = 1; col <= nCols; ++col) {
            if (color[row][col] == WALL) {
                int sum = 1;
                std::set<int> answ;
                if (color[row-1][col] != WALL) answ.insert(color[row-1][col]);
                if (color[row+1][col] != WALL) answ.insert(color[row+1][col]);
                if (color[row][col-1] != WALL) answ.insert(color[row][col-1]);
                if (color[row][col+1] != WALL) answ.insert(color[row][col+1]);
                for (auto& it : answ) {
                    sum += colorCount[it];
                }
                printf("%d", sum % 10);
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
    
    return 0;
}