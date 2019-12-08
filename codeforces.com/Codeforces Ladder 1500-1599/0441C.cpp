/*
    Problem: 441C. Valera and Tubes
    Solution: constructive, implementation
*/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

struct Pair { int row, col; };

int main() {
    int nRows, nCols, k; 
    scanf("%d %d %d", &nRows, &nCols, &k);
    std::queue<Pair> queue;
    for (int row = 1; row <= nRows; ++row) {
        if (row % 2 == 1) {
            for (int col = 1; col <= nCols; ++col) {
                queue.push(Pair{row,col});
            }
        } else {
            for (int col = nCols; col >= 1; --col) {
                queue.push(Pair{row,col});
            }
        }
    }
    while (k > 1) {
        auto p1 = queue.front(); queue.pop();
        auto p2 = queue.front(); queue.pop();
        printf("2 %d %d %d %d\n", p1.row, p1.col, p2.row, p2.col);
        --k;
    }
    printf("%d", (int)queue.size());
    while (!queue.empty()) {
        printf(" %d %d", queue.front().row, queue.front().col);
        queue.pop();
    }
    return 0;
}