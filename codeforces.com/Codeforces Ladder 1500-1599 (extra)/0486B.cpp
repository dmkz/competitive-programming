/*
    Problem: 486B. OR in Matrix
    
    Solution: constructive, O(n^3)
    
    Author: Dmitry Kozyrev, github: dmkz, e-mail: dmkozyrev@rambler.ru
*/

#include <iostream>
#include <vector>
struct Pair { int r, c; };
int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols, 1));
    std::vector<Pair> pairs[2];
    for (int r = 0; r < nRows; ++r) {
        for (int c = 0; c < nCols; ++c) {
            int value; scanf("%d", &value);
            pairs[value].push_back(Pair{r, c});
        }
    }
    for (auto& it : pairs[0]) {
        for (int c = 0; c < nCols; ++c) {
            arr[it.r][c] = 0;
        }
        for (int r = 0; r < nRows; ++r) {
            arr[r][it.c] = 0;
        }
    }
    for (auto& it : pairs[1]) {
        int value = 0;
        for (int c = 0; c < nCols; ++c) {
            value |= arr[it.r][c];
        }
        for (int r = 0; r < nRows; ++r) {
            value |= arr[r][it.c];
        }
        if (value == 0) {printf("NO"); return 0; }
    }
    printf("YES\n");
    for (auto& row : arr) {
        for (auto& it : row) {
            printf("%d ", it);
        }
        printf("\n");
    }
    return 0;
}