#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols));
    for (auto& row : arr) {
        int nZeros = 0;
        for (auto& it : row) {
            scanf("%d", &it);
            nZeros += (it == 0);
        }
        if (nZeros == 0) {
            printf("Impossible");
            return 0;
        }
    }
    
    std::vector<int> used(nRows, false), answer;
    int nUsed = 0;
    while (nUsed < nRows) {
        int max = 0, max_j = -1;
        for (int j = 0; j < nCols; ++j) {
            int count = 0;
            for (int i = 0; i < nRows; ++i) {
                if (used[i] || arr[i][j] == 1) continue;
                ++count;
            }
            if (count > max) {
                max = count;
                max_j = j;
            }
        }
        assert(max_j != -1);
        const int j = max_j;
        answer.push_back(j+1);
        for (int i = 0; i < nRows; ++i) {
            if (used[i] || arr[i][j] == 1) continue;
            used[i] = true;
            ++nUsed;
        }
    }
    printf("%d\n", (int)answer.size());
    for (auto& it : answer) {
        printf("%d ", it);
    }
    return 0;
}