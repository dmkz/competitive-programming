#include <stdio.h>
#include <string> 
#include <cassert>

void put(const std::string& s) {
    for (auto c : s) {
        if (c == 'u') {
            printf("UP\n");
        } else if (c == 'd') {
            printf("DOWN\n");
        } else if (c == 'r') {
            printf("RIGHT\n");
        } else if (c == 'l') {
            printf("LEFT\n");
        } else {
            throw 1;
        }
    }
}

int main() {
    int nRows, nCols;
    scanf("%d %d", &nRows, &nCols);
    if (nCols == 1 && nRows == 1) {
        return 0;
    }
    if (nCols == 1 && nRows == 2) {
        put("du");
        return 0;
    }
    if (nRows == 1 || nCols == 1) {
        printf("no solution");
        return 0;
    }
    assert(nCols >= 2 && nRows >= 2);
    int row = 0, col = 0;
    while (col+1 < nCols) {
        assert(row == 0);
        while (row < nRows-1) {
            // r d l r d l 
            put("rdl");
            ++row;
        }
        put("urdl");
        while (row > 0) {
            put("u");
            --row;
        }
        put("r");
        ++col;
    }
    assert(col == nCols-1 && row == 0);
    return 0;
}