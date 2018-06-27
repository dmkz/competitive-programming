/*
    "Вирусы - 2": графы, заливка, компоненты связности, O(n*m)
*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>

const int WALL  = -1;
const int EMPTY = 0;

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    
    std::vector<std::vector<int>> map(1+nRows+1, std::vector<int>(1+nCols+1, EMPTY));
    for (int i = 1; i <= nCols; ++i) {
        map[0][i] = map[nRows+1][i] = WALL;
    }
    for (int i = 1; i <= nRows; ++i) {
        map[i][0] = map[i][nCols+1] = WALL;
    }
    int q;
    scanf("%d", &q);
    while (q--) {
        int r, c;
        scanf("%d %d", &r, &c);
        map[r][c] = WALL;
    }
    
    int nParts = 0;
    for (int r = 1; r <= nRows; ++r) {
        for (int c = 1; c <= nCols; ++c) {
            if (map[r][c] == EMPTY) {
                std::function<void(int,int)> visit = [&](const int r, const int c) {
                    for (int dr = -1; dr <= 1; ++dr) {
                        for (int dc = -1; dc <= 1; ++dc) {
                            if (dr * dr + dc * dc == 1 && map[r+dr][c+dc] == EMPTY) {
                                map[r+dr][c+dc] = nParts;
                                visit(r+dr, c+dc);
                            }
                        }
                    }
                };
                ++nParts;
                visit(r, c);
            }
        }
    }
    printf("%d", nParts);
    
    return 0;
}