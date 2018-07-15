/*
    "Аттракцион": сортировка, конструктив, O(n^2*m + n*m^2)
*/

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cassert>

struct Triple {
    char type; int a, b;
};

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    
    std::vector<std::vector<int>> arr(nRows, std::vector<int>(nCols));
    
    int i1 = -1, j1 = -1;
    for (int i = 0; i < nRows; ++i) {
        for (int j = 0; j < nCols; ++j) {
            scanf("%d", &arr[i][j]);
            if (arr[i][j] == 1) {
                i1 = i;
                j1 = j;
            }
        }
    }
    assert(i1 >= 0 && j1 >= 0);
    
    std::vector<Triple> answer;
    
    // Сортировка столбцов:
    for (int j = 0; j < nCols; ++j) {
        int jmin = j;
        for (int k = j+1; k < nCols; ++k) {
            if (arr[i1][jmin] > arr[i1][k]) {
                jmin = k;
            }
        }
        if (jmin == j) {
            continue;
        }
        answer.push_back(Triple{'C', j+1, jmin+1});
        for (int i = 0; i < nRows; ++i) {
            std::swap(arr[i][jmin], arr[i][j]);
        }
    }
    
    // Сортировка строк:
    for (int i = 0; i < nRows; ++i) {
        int imin = i;
        for (int k = i+1; k < nRows; ++k) {
            if (arr[k][0] < arr[imin][0]) {
                imin = k;
            }
        }
        if (imin == i) {
            continue;
        }
        answer.push_back(Triple{'R', i+1, imin+1});
        for (int j = 0; j < nCols; ++j) {
            std::swap(arr[imin][j], arr[i][j]);
        }
    }
    
    // Вывод ответа:
    printf("%d\n", (int)answer.size());
    for (auto& t : answer) {
        printf("%c %d %d\n", t.type, t.a, t.b);
    }
    
    return 0;
}