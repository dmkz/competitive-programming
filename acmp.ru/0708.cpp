/*
    "Хомяки и кролики": динамическое программирование, O(N^3)
*/

#include <stdio.h>
#include <algorithm>
#include <vector>

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    
    std::vector<std::vector<int>> arr(1+nRows, std::vector<int>(nCols, 0));
    int sum = 0;
    for (auto& row : arr) {
        for (auto& it : row) {
            scanf("%d", &it);
            sum += it;
        }
    }
    
    int s1 = 0, s2 = 0;
    do {        
        // Жадное моделирование действий кролика:
        int maxj = nCols-1;
        for (int j = nCols-1; j >= 0; --j) {
            if (arr[0][j] > arr[0][maxj]) {
                maxj = j;
            }
        }
        s2 += arr[0][maxj]; 
        arr[0][maxj] = 0;
        
        for (int i = 1; i < nRows; ++i) {            
            int j = maxj;
            if (j + 1 < nCols && arr[i][j+1] >= arr[i][maxj]) {
                maxj = j+1;
            }
            if (arr[i][j] > arr[i][maxj]) {
                maxj = j;
            }
            if (j - 1 >= 0 && arr[i][j-1] > arr[i][maxj]) {
                maxj = j-1;
            }
            s2 += arr[i][maxj];
            arr[i][maxj] = 0;
        }
        
        // Инициализация массивов для двумерного ДП:
        std::vector<std::vector<int>> smax(1+nRows, std::vector<int>(nCols, -1));
        for (int j = 0; j < nCols; ++j) {
            smax.back()[j] = 0;
        }
        std::vector<std::vector<int>> from(1+nRows, std::vector<int>(nCols, -1));
        // ДП снизу-вверх:
        for (int i = nRows-1; i >= 0; --i) {
            for (int j = nCols-1; j >= 0; --j) {
                if (j+1 < nCols && smax[i][j] < smax[i+1][j+1] + arr[i][j]) {
                    smax[i][j] = smax[i+1][j+1] + arr[i][j];
                    from[i][j] = j+1;
                }
                
                if (smax[i][j] < smax[i+1][j] + arr[i][j]) {
                    smax[i][j] = smax[i+1][j] + arr[i][j];
                    from[i][j] = j;
                }
                
                if (j-1 >= 0 && smax[i][j] < smax[i+1][j-1] + arr[i][j]) {
                    smax[i][j] = smax[i+1][j-1] + arr[i][j];
                    from[i][j] = j-1;
                }
            }
        }
        
        // Моделирование действий хомяков:
        maxj = nCols-1;
        for (int j = nCols-1; j >= 0; --j) {
            if (smax[0][maxj] < smax[0][j]) {
                maxj = j;
            }
        }
        
        s1 += smax[0][maxj];
        
        for (int i = 0; i < nRows; ++i) {
            arr[i][maxj] = 0;
            maxj = from[i][maxj];
        }
        
    } while (s1+s2 < sum);
    printf("%d %d", s2, s1);
    return 0;
}