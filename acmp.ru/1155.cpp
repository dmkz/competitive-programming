#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <cassert>
 
typedef bool Item;
typedef std::vector<Item> Vector;
typedef std::vector<Vector> Matrix;
typedef std::vector<Matrix> Tensor;
 
int main() {
    int n, nRows, nCols;
    scanf("%d %d %d", &n, &nRows, &nCols);
     
    Matrix table(nRows*nCols, Vector(n));
    for (int i = 0; i < n; ++i) {
        for (int r = 0; r < nRows; ++r) {
            char buf[101];
            scanf("%100s", buf);
            for (int c = 0; c < nCols; ++c) {
                table[r*nCols+c][i] = (buf[c] == '*');
            }
        }
    }
     
    std::sort(table.begin(), table.end());
    table.erase(std::unique(table.begin(), table.end()), table.end());
     
    printf("%d", (int)table.size());
    return 0;
}